"""Compila el port de TMC desde el código fuente (Linux/macOS).

No se incluye en el AppImage: el código del juego se clona y se compila
en el equipo del usuario, y los binarios se copian a la carpeta de instalación.
"""
import logging
import os
import shutil
import stat
import subprocess
import sys
import threading
from pathlib import Path
from typing import Callable, Optional

log = logging.getLogger("compiler")

REPO_URL = "https://github.com/ReyPixel-1/ReyPixelCap.git"
XMAKE_INSTALL_CMD = "curl -fsSL https://xmake.io/shget.text | bash"
TARGETS = ("tmc_pc", "asset_extractor")


class CompileError(Exception):
    pass


def _clean_env() -> dict:
    """Entorno limpio para los procesos hijos.

    PyInstaller/AppImage modifican LD_LIBRARY_PATH y eso rompe git, gcc y xmake.
    """
    env = os.environ.copy()
    if "LD_LIBRARY_PATH_ORIG" in env:
        env["LD_LIBRARY_PATH"] = env.pop("LD_LIBRARY_PATH_ORIG")
    elif getattr(sys, "frozen", False):
        env.pop("LD_LIBRARY_PATH", None)
    extra = [Path.home() / ".local" / "bin", Path.home() / ".xmake" / "bin"]
    env["PATH"] = os.pathsep.join([str(p) for p in extra] + [env.get("PATH", "")])
    return env


class Compiler:
    def __init__(
        self,
        work_dir: str,
        on_log: Callable[[str], None],
        on_progress: Optional[Callable[[int, str], None]] = None,
    ):
        self.work_dir = Path(work_dir)
        self.src = self.work_dir / "tmc-src"
        self.on_log = on_log
        self.on_progress = on_progress or (lambda pct, msg: None)
        self.env = _clean_env()
        self._cancel = threading.Event()
        self._proc: Optional[subprocess.Popen] = None

    # ── control ──────────────────────────────────────────────────────────
    def cancel(self):
        self._cancel.set()
        if self._proc and self._proc.poll() is None:
            self._proc.terminate()

    def _which(self, name: str) -> Optional[str]:
        return shutil.which(name, path=self.env["PATH"])

    def _run(self, cmd, cwd=None, shell=False):
        shown = cmd if shell else " ".join(cmd)
        self.on_log(f"$ {shown}")
        log.info("run: %s", shown)
        self._proc = subprocess.Popen(
            cmd, cwd=cwd, env=self.env, shell=shell,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, bufsize=1, errors="replace",
        )
        for line in self._proc.stdout:
            self.on_log(line.rstrip())
        rc = self._proc.wait()
        if self._cancel.is_set():
            raise CompileError("Compilación cancelada.")
        if rc != 0:
            raise CompileError(f"El comando falló (código {rc}): {shown}")

    # ── pasos ────────────────────────────────────────────────────────────
    def _preflight(self):
        missing = [t for t in ("git", "gcc", "g++", "make", "curl") if not self._which(t)]
        if missing:
            raise CompileError(
                "Faltan herramientas: " + ", ".join(missing) + "\n"
                "Instálalas con:\n"
                "  sudo apt install -y build-essential git curl cmake pkg-config"
            )

    def _ensure_xmake(self):
        if self._which("xmake"):
            return
        self.on_log("xmake no está instalado. Instalándolo...")
        self._run(XMAKE_INSTALL_CMD, shell=True)
        self.env = _clean_env()  # refresca PATH
        if not self._which("xmake"):
            raise CompileError("No se pudo instalar xmake. Instálalo desde https://xmake.io")

    def _fetch_source(self):
        self.work_dir.mkdir(parents=True, exist_ok=True)
        local_source = Path.home() / "tmc-fuente"

        if local_source.is_dir():
            if not (self.src / ".git").exists():
                self.on_log("Preparando repositorio de compilación...")
                self._run([
                    "git", "clone", "--depth", "1", REPO_URL, str(self.src)
                ])

            self.on_log("Integrando los cambios locales del proyecto...")
            ignored = shutil.ignore_patterns(
                ".git", "build", "dist", "*.bak*", "spoilers",
                "state_eu_*.bin", "__pycache__", ".venv"
            )
            shutil.copytree(
                local_source, self.src,
                dirs_exist_ok=True, ignore=ignored
            )
            self.on_log("Código local integrado correctamente.")
        elif (self.src / ".git").exists():
            self.on_log("Actualizando código fuente...")
            self._run(["git", "pull", "--ff-only"], cwd=str(self.src))
        else:
            self.on_log("Descargando código fuente...")
            self._run([
                "git", "clone", "--depth", "1", REPO_URL, str(self.src)
            ])

    def _build(self):
        for target in TARGETS:
            self.on_log(f"Compilando {target} (la primera vez tarda bastante)...")
            self._run(["xmake", "build", "-y", target], cwd=str(self.src))

    def _find(self, name: str) -> Optional[Path]:
        found = [p for p in (self.src / "build").rglob(name) if p.is_file()]
        return max(found, key=lambda p: p.stat().st_mtime) if found else None

    def _install(self, install_dir: Path):
        install_dir.mkdir(parents=True, exist_ok=True)
        for name in TARGETS:
            src = self._find(name)
            if not src:
                raise CompileError(f"Compiló, pero no encuentro {name} en {self.src / 'build'}")
            dst = install_dir / name
            shutil.copy2(src, dst)
            dst.chmod(dst.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
            self.on_log(f"Copiado: {dst}")
            # librerías compartidas junto al binario (si las hubiera)
            for lib in src.parent.glob("*.so*"):
                shutil.copy2(lib, install_dir / lib.name)

    # ── API pública ──────────────────────────────────────────────────────
    def build(self, install_dir: str):
        steps = [
            (5, "Comprobando herramientas", self._preflight),
            (15, "Preparando xmake", self._ensure_xmake),
            (30, "Descargando código", self._fetch_source),
            (90, "Compilando", self._build),
            (98, "Copiando binarios", lambda: self._install(Path(install_dir))),
        ]
        for pct, msg, fn in steps:
            self.on_progress(pct, msg)
            fn()
        self.on_progress(100, "Compilación completa")
        self.on_log("Compilación completa. Ahora usa 'Extract Assets' y luego 'Launch'.")

    def build_async(self, install_dir: str, on_done: Callable[[Optional[Exception]], None]):
        """Compila en un hilo aparte. on_done(None) si salió bien, o on_done(error)."""
        def worker():
            try:
                self.build(install_dir)
                on_done(None)
            except Exception as e:  # noqa: BLE001
                log.exception("Fallo al compilar")
                on_done(e)
        threading.Thread(target=worker, daemon=True).start()



# ── limpieza ─────────────────────────────────────────────────────────────
_APP_ITEMS = (
    "tmc_pc", "tmc_pc.exe", "asset_extractor", "asset_extractor.exe",
    "assets", "assets_src", "rom_data", "sounds.json",
    "baserom.gba", "baserom_eu.gba", "baserom_jp.gba",
)
_APP_GLOBS = ("*.so", "*.so.*", "bugreport_*")
_SAVE_GLOBS = ("*.sav", "*.randomizer", "*.softslots", "state_*.bin", "config.json")


def _rm(p: Path):
    if p.is_symlink() or p.is_file():
        p.unlink()
    elif p.is_dir():
        shutil.rmtree(p)


def clean_install(install_dir: str, work_dir: str, remove_saves: bool = False):
    """Borra lo generado por la compilación. Devuelve la lista de rutas eliminadas.

    Solo borra elementos con nombre conocido dentro de install_dir, nunca la
    carpeta completa. La ROM original del usuario no se toca.
    """
    removed = []

    src = Path(work_dir) / "tmc-src"
    if src.exists():
        _rm(src)
        removed.append(str(src))

    d = Path(install_dir) if install_dir else None
    if d and d.is_dir():
        targets = [d / n for n in _APP_ITEMS]
        for g in _APP_GLOBS:
            targets += list(d.glob(g))
        if remove_saves:
            for g in _SAVE_GLOBS:
                targets += list(d.glob(g))
        for t in targets:
            if t.exists() or t.is_symlink():
                _rm(t)
                removed.append(str(t))
        try:
            if d.resolve() != Path.home().resolve():
                d.rmdir()  # solo funciona si quedó vacía
                removed.append(str(d))
        except OSError:
            pass
    return removed


if __name__ == "__main__":
    # Prueba desde terminal, sin interfaz:  python -m app.compiler ~/TMC-juego
    dest = sys.argv[1] if len(sys.argv) > 1 else str(Path.home() / "TMC-juego")
    c = Compiler(Path.home() / ".AutoTMC", on_log=print, on_progress=lambda p, m: print(f"[{p}%] {m}"))
    try:
        c.build(dest)
    except CompileError as e:
        print("ERROR:", e)
        sys.exit(1)
