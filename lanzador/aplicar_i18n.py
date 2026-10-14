import re, sys
from pathlib import Path

port = Path("port")
menu = port / "port_imgui_menu.cpp"
cfg_h = port / "port_runtime_config.h"
cfg_c = port / "port_runtime_config.cpp"
hdr = port / "port_menu_i18n.h"

if not menu.exists():
    sys.exit("Ejecútalo dentro de ~/tmc-fuente (no encuentro port/port_imgui_menu.cpp)")
if "port_menu_i18n.h" in menu.read_text(encoding="utf-8"):
    sys.exit("Ya está aplicado. Para rehacerlo: git checkout -- port/ && rm -f port/port_menu_i18n.h")

def uno(s, viejo, nuevo, donde):
    if s.count(viejo) != 1:
        sys.exit(f"[{donde}] no encontré (o está duplicado): {viejo!r}")
    return s.replace(viejo, nuevo)

cambios = {}

# 1) Configuración
h = cfg_h.read_text(encoding="utf-8")
h = uno(h, "void Port_Config_SetRibbonEnabled(bool on);",
    "void Port_Config_SetRibbonEnabled(bool on);\n"
    "/* Menu language (F8 menu only): false = English, true = Spanish. */\n"
    "bool Port_Config_GetMenuLangEs(void);\n"
    "void Port_Config_SetMenuLangEs(bool on);", "config.h")
cambios[cfg_h] = h

c = cfg_c.read_text(encoding="utf-8")
c = uno(c, "bool sRibbonCfg = true;", "bool sMenuLangEs = false;\nbool sRibbonCfg = true;", "config.cpp var")
c = uno(c, '{ "ribbon_mode", &sRibbonCfg, true },',
    '{ "ribbon_mode", &sRibbonCfg, true },\n    { "menu_lang_es", &sMenuLangEs, false },', "config.cpp tabla")
c = uno(c, 'extern "C" bool Port_Config_GetMenuHintSeen(void) {',
    'extern "C" bool Port_Config_GetMenuLangEs(void) {\n    return sMenuLangEs;\n}\n'
    'extern "C" void Port_Config_SetMenuLangEs(bool on) {\n    sMenuLangEs = on;\n'
    '    sConfigJson["menu_lang_es"] = on;\n    SaveConfig();\n}\n'
    'extern "C" bool Port_Config_GetMenuHintSeen(void) {', "config.cpp funcs")
cambios[cfg_c] = c

# 2) Reemplazar ImGui:: por I18n:: en el menú y las pestañas
pat = re.compile(r"ImGui::(Button|SmallButton|Checkbox|BeginTabItem|SeparatorText|"
                 r"TextUnformatted|TextDisabled|TextColored|TextWrapped|Text|CollapsingHeader)\(")
archivos = [menu] + sorted(port.glob("port_imgui_*_tab.inc"))
total = 0
for f in archivos:
    s = f.read_text(encoding="utf-8")
    s, n = pat.subn(lambda m: "I18n::" + m.group(1) + "(", s)
    total += n
    cambios[f] = s

# 3) Include y selector en el menú
m = cambios[menu]
m = uno(m, '#include "port_runtime_config.h"',
        '#include "port_menu_i18n.h"\n#include "port_runtime_config.h"', "menu include")
m = uno(m, 'if (I18n::Checkbox("Ribbon mode (uncheck for classic menu)", &useRibbon)) {',
    '{\n'
    '            bool langEs = Port_Config_GetMenuLangEs();\n'
    '            if (ImGui::Checkbox("Espa\\xc3\\xb1ol (menu language / idioma del men\\xc3\\xba)", &langEs)) {\n'
    '                Port_Config_SetMenuLangEs(langEs);\n'
    '            }\n'
    '        }\n'
    '        if (I18n::Checkbox("Ribbon mode (uncheck for classic menu)", &useRibbon)) {', "menu selector")
cambios[menu] = m

# 4) Cabecera con el diccionario
HEADER = r'''#pragma once
/* Menu i18n: English <-> Spanish for the F8 ImGui menu (menu only, not the game text). */
#include <imgui.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include "port_runtime_config.h"

namespace I18n {

inline const std::unordered_map<std::string, const char*>& Dict() {
    static const std::unordered_map<std::string, const char*> d = {
        /* Tabs */
        { "Items", "Objetos" }, { "Display", "Pantalla" }, { "Saves", "Partidas" },
        { "Profiles", "Perfiles" }, { "Equip", "Equipo" }, { "Controls", "Controles" },
        { "Warp", "Viaje" }, { "Entities", "Entes" }, { "Flags", "Banderas" },
        { "Memory", "Memoria" }, { "Randomizer", "Aleatorio" }, { "Audio", "Audio" },
        { "Accessibility", "Accesib." }, { "Reborn", "Reborn" }, { "Practice", "Pr\xc3\xa1" "ctica" },
        { "Map Editor", "Editor mapa" }, { "Achievements", "Logros" },
        /* Items tab */
        { "Stats & Unlocks", "Estad\xc3\xad" "sticas" },
        { "Recovery & Cheats", "Recuperaci\xc3\xb3n y trucos" },
        { "Unlock all items", "Desbloquear objetos" },
        { "Max hearts", "Vida m\xc3\xa1x." },
        { "Heal", "Curar" },
        { "999 rupees", "999 rupias" },
        { "999 shells", "999 conchas" },
        { "All kinstones fused", "Todas las kinstones" },
        { "All figurines (130)", "Figuras (130)" },
        { "Figurines 100% (marks beaten)", "Figuras 100%" },
        { "Per-item toggle", "Objeto por objeto" },
        { "Counts & capacities", "Cantidades" },
        { "Bottle contents", "Botellas" },
        { "Dungeon items (any dungeon)", "Objetos de mazmorra" },
        { "Charm / Picolyte", "Amuleto / Picolito" },
        { "Jump to current", "Ir al actual" },
        { "Small keys", "Llaves peque\xc3\xb1" "as" },
        { "Big Key", "Llave maestra" },
        { "Compass", "Br\xc3\xbajula" },
        { "Map", "Mapa" },
        { "Sword", "Espada" }, { "Weapons", "Armas" }, { "Gear", "Equipo" },
        { "Bottles", "Botellas" }, { "Elements", "Elementos" }, { "Upgrades", "Mejoras" },
        { "Quest", "Misi\xc3\xb3n" }, { "Sword Techniques", "T\xc3\xa9" "cnicas de espada" },
        /* Display tab */
        { "Window scale", "Escala ventana" }, { "Target FPS", "FPS objetivo" },
        { "Internal scale", "Escala interna" }, { "Aspect ratio", "Relaci\xc3\xb3n aspecto" },
        { "Renderer", "Renderizador" }, { "Background", "Fondo" },
        { "CRT filter", "Filtro CRT" }, { "Shader preset", "Preset shader" },
        { "Rescan", "Buscar" }, { "Fullscreen", "Pantalla completa" },
        { "Hide cursor in fullscreen", "Ocultar cursor" },
        { "GBA colour correction", "Correcci\xc3\xb3n color GBA" },
        { "LCD persistence", "Persistencia LCD" },
        { "Hold to advance text", "Mantener para avanzar texto" },
        { "Ribbon mode (uncheck for classic menu)", "Modo cinta (desmarcar = men\xc3\xba cl\xc3\xa1sico)" },
        /* Controls tab */
        { "Keyboard shortcuts", "Atajos de teclado" },
        { "Roll attack macro", "Macro ataque rodante" },
        { "Reset all to defaults", "Restablecer todo" },
        { "Set", "Fijar" }, { "Add", "A\xc3\xb1" "adir" },
    };
    return d;
}

/* Translate a label. Keeps the "##id" suffix so ImGui widget IDs stay valid. */
inline const char* T(const char* s) {
    if (!s || !Port_Config_GetMenuLangEs()) return s;
    const char* hash = std::strstr(s, "##");
    if (!hash) {
        auto it = Dict().find(s);
        return it != Dict().end() ? it->second : s;
    }
    auto it = Dict().find(std::string(s, (size_t)(hash - s)));
    if (it == Dict().end()) return s;
    static thread_local char ring[8][256];
    static thread_local int idx = 0;
    char* out = ring[idx++ & 7];
    std::snprintf(out, 256, "%s%s", it->second, hash);
    return out;
}

inline bool Button(const char* l, const ImVec2& size = ImVec2(0, 0)) { return ImGui::Button(T(l), size); }
inline bool SmallButton(const char* l) { return ImGui::SmallButton(T(l)); }
inline bool Checkbox(const char* l, bool* v) { return ImGui::Checkbox(T(l), v); }
inline bool BeginTabItem(const char* l, bool* p = nullptr, ImGuiTabItemFlags f = 0) {
    return ImGui::BeginTabItem(T(l), p, f);
}
inline void SeparatorText(const char* l) { ImGui::SeparatorText(T(l)); }
inline bool CollapsingHeader(const char* l, ImGuiTreeNodeFlags f = 0) {
    return ImGui::CollapsingHeader(T(l), f);
}
inline bool CollapsingHeader(const char* l, bool* vis, ImGuiTreeNodeFlags f = 0) {
    return ImGui::CollapsingHeader(T(l), vis, f);
}
inline void TextUnformatted(const char* t, const char* end = nullptr) {
    ImGui::TextUnformatted(end ? t : T(t), end);
}
inline void Text(const char* fmt, ...) {
    va_list a; va_start(a, fmt); ImGui::TextV(T(fmt), a); va_end(a);
}
inline void TextDisabled(const char* fmt, ...) {
    va_list a; va_start(a, fmt); ImGui::TextDisabledV(T(fmt), a); va_end(a);
}
inline void TextWrapped(const char* fmt, ...) {
    va_list a; va_start(a, fmt); ImGui::TextWrappedV(T(fmt), a); va_end(a);
}
inline void TextColored(const ImVec4& col, const char* fmt, ...) {
    va_list a; va_start(a, fmt); ImGui::TextColoredV(col, T(fmt), a); va_end(a);
}

} // namespace I18n
'''

for f, s in cambios.items():
    f.write_text(s, encoding="utf-8")
hdr.write_text(HEADER, encoding="utf-8")
print(f"OK: {total} llamadas cambiadas en {len(archivos)} archivos.")
print("Creado: port/port_menu_i18n.h")
