#!/usr/bin/env bash
ICON_SRC="${ICON_SRC:-packaging/icon.png}"
APPDIR="AutoTMC.AppDir"
OUT="AutoTMC-x86_64.AppImage"

fallo() { echo; echo "ERROR: $1"; exit 1; }

cd "$(dirname "$(readlink -f "$0")")/.."
[ -f main.py ] || fallo "No estoy en la carpeta del proyecto (falta main.py)."
[ -f "$ICON_SRC" ] || fallo "No encuentro el icono: $ICON_SRC"

echo ">> 1/5 Instalando dependencias del sistema..."
sudo apt update
sudo apt install -y python3 python3-venv python3-pip python3-tk git wget libfuse2 \
  || sudo apt install -y python3 python3-venv python3-pip python3-tk git wget libfuse2t64 \
  || fallo "No se pudieron instalar las dependencias."

echo ">> 2/5 Preparando entorno Python..."
python3 -m venv .venv || fallo "No se pudo crear el entorno virtual."
source .venv/bin/activate
pip install --upgrade pip
pip install -r requirements.txt pyinstaller pillow || fallo "Fallo instalando paquetes de Python."

echo ">> 3/5 Compilando el binario..."
rm -rf build dist AutoTMC-Linux *.spec
pyinstaller --onefile --windowed --name="AutoTMC-Linux" \
  --hidden-import=customtkinter --collect-all customtkinter \
  --distpath="." main.py || fallo "PyInstaller falló."
[ -f AutoTMC-Linux ] || fallo "No se generó AutoTMC-Linux."

echo ">> 4/5 Armando el AppDir con tu icono..."
rm -rf "$APPDIR"
mkdir -p "$APPDIR/usr/bin"
cp AutoTMC-Linux "$APPDIR/usr/bin/"
chmod +x "$APPDIR/usr/bin/AutoTMC-Linux"

python3 - <<EOF
from PIL import Image
img = Image.open("$ICON_SRC").convert("RGBA")
w, h = img.size
lado = max(w, h)
lienzo = Image.new("RGBA", (lado, lado), (0, 0, 0, 0))
lienzo.paste(img, ((lado - w) // 2, (lado - h) // 2))
lienzo.resize((256, 256), Image.LANCZOS).save("$APPDIR/autotmc.png")
EOF

cat > "$APPDIR/autotmc.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=AutoTMC
Comment=Lanzador de AutoTMC
Exec=AutoTMC-Linux
Icon=autotmc
Categories=Utility;
Terminal=false
EOF

cat > "$APPDIR/AppRun" <<'EOF'
#!/bin/sh
HERE="$(dirname "$(readlink -f "$0")")"
exec "$HERE/usr/bin/AutoTMC-Linux" "$@"
EOF
chmod +x "$APPDIR/AppRun"

echo ">> 5/5 Generando el AppImage..."
if [ ! -f appimagetool ]; then
  wget -O appimagetool \
    https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage \
    || fallo "No se pudo descargar appimagetool."
  chmod +x appimagetool
fi
ARCH=x86_64 ./appimagetool --appimage-extract-and-run "$APPDIR" "$OUT" \
  || fallo "appimagetool falló."
chmod +x "$OUT"

echo
echo "LISTO: $(pwd)/$OUT"
