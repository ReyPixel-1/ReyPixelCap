"""Diálogos nativos en Linux (zenity), con respaldo a los de Tk.

Mantiene la misma interfaz que tkinter.messagebox / tkinter.filedialog, así
el resto del código no cambia. Si zenity no existe o falla, usa los de Tk.
"""
import html
import os
import shutil
import subprocess
import sys
import tkinter.filedialog as _tk_filedialog
import tkinter.messagebox as _tk_messagebox
from pathlib import Path


def _env() -> dict:
    """Entorno limpio: PyInstaller/AppImage alteran LD_LIBRARY_PATH y rompen zenity."""
    env = os.environ.copy()
    if "LD_LIBRARY_PATH_ORIG" in env:
        env["LD_LIBRARY_PATH"] = env.pop("LD_LIBRARY_PATH_ORIG")
    elif getattr(sys, "frozen", False):
        env.pop("LD_LIBRARY_PATH", None)
    return env


def _available() -> bool:
    return sys.platform.startswith("linux") and shutil.which("zenity") is not None


def _zenity(args):
    """Devuelve (código, salida). Código None si zenity no pudo ejecutarse."""
    try:
        p = subprocess.run(
            ["zenity", *args], capture_output=True, text=True, env=_env()
        )
        return p.returncode, p.stdout.strip()
    except Exception:
        return None, ""


# ── mensajes ─────────────────────────────────────────────────────────────
def _message(kind, title, message, fallback, **kw):
    """kind: info | warning | error | question. Devuelve True si pulsó Sí/Aceptar."""
    if _available():
        rc, _ = _zenity([
            f"--{kind}", f"--title={title}",
            f"--text={html.escape(str(message))}", "--width=440",
        ])
        if rc in (0, 1):
            return rc == 0
    return fallback(title, message, **kw)


def showinfo(title=None, message=None, **kw):
    _message("info", title or "", message, _tk_messagebox.showinfo, **kw)
    return "ok"


def showwarning(title=None, message=None, **kw):
    _message("warning", title or "", message, _tk_messagebox.showwarning, **kw)
    return "ok"


def showerror(title=None, message=None, **kw):
    _message("error", title or "", message, _tk_messagebox.showerror, **kw)
    return "ok"


def askyesno(title=None, message=None, **kw):
    return bool(_message("question", title or "", message, _tk_messagebox.askyesno, **kw))


def askokcancel(title=None, message=None, **kw):
    return bool(_message("question", title or "", message, _tk_messagebox.askokcancel, **kw))


# ── selector de archivos ─────────────────────────────────────────────────
def _start_path(kw) -> str:
    base = kw.get("initialdir") or str(Path.home())
    return os.path.join(str(base), kw.get("initialfile") or "")


def askopenfilename(**kw):
    if _available():
        args = ["--file-selection", f"--title={kw.get('title') or 'Select file'}",
                f"--filename={_start_path(kw)}"]
        for label, pats in kw.get("filetypes") or []:
            pats = pats.split() if isinstance(pats, str) else list(pats)
            if pats == ["*"] or pats == ["*.*"]:
                continue
            pats += [p.upper() for p in pats if p.startswith("*.") and p.upper() not in pats]
            args.append(f"--file-filter={label} | {' '.join(pats)}")
        args.append("--file-filter=Todos los archivos | *")
        rc, out = _zenity(args)
        if rc == 0:
            return out
        if rc == 1:
            return ""
    return _tk_filedialog.askopenfilename(**kw)


def askdirectory(**kw):
    if _available():
        rc, out = _zenity([
            "--file-selection", "--directory",
            f"--title={kw.get('title') or 'Select folder'}",
            f"--filename={_start_path(kw)}",
        ])
        if rc == 0:
            return out
        if rc == 1:
            return ""
    return _tk_filedialog.askdirectory(**kw)


class _Proxy:
    """Expone las funciones nuevas y delega todo lo demás en el módulo de Tk."""
    def __init__(self, base, overrides):
        self._base = base
        for k, v in overrides.items():
            setattr(self, k, v)

    def __getattr__(self, name):
        return getattr(self._base, name)


messagebox = _Proxy(_tk_messagebox, {
    "showinfo": showinfo, "showwarning": showwarning, "showerror": showerror,
    "askyesno": askyesno, "askokcancel": askokcancel,
})
filedialog = _Proxy(_tk_filedialog, {
    "askopenfilename": askopenfilename, "askdirectory": askdirectory,
})
