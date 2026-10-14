#pragma once
/* Menu i18n: English <-> Spanish for the F8 ImGui menu (menu only, not the game text). */
#include <imgui.h>
#include <cstdarg>
#include <cctype>
#include <cstdlib>
#include <unordered_set>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <utility>
#include "port_runtime_config.h"

namespace I18n {

inline const std::unordered_map<std::string, const char*>& Dict() {
    static const std::unordered_map<std::string, const char*> d = {
        { "Items", "Objetos" },
        { "Display", "Pantalla" },
        { "Saves", "Partidas" },
        { "Profiles", "Perfiles" },
        { "Equip", "Equipo" },
        { "Controls", "Controles" },
        { "Warp", "Viaje" },
        { "Entities", "Entes" },
        { "Flags", "Banderas" },
        { "Memory", "Memoria" },
        { "Randomizer", "Aleatorio" },
        { "Accessibility", "Accesibilidad" },
        { "Practice", "Pr\303\241ctica" },
        { "Map Editor", "Editor mapa" },
        { "Achievements", "Logros" },
        { "Stats & Unlocks", "Estad\303\255sticas" },
        { "Recovery & Cheats", "Recuperaci\303\263n y trucos" },
        { "Unlock all items", "Desbloquear objetos" },
        { "Max hearts", "Vida m\303\241x." },
        { "Heal", "Curar" },
        { "999 rupees", "999 rupias" },
        { "999 shells", "999 conchas" },
        { "All kinstones fused", "Todas las kinstones" },
        { "All figurines (130)", "Figuras (130)" },
        { "Figurines 100% (marks beaten)", "Figuras 100%" },
        { "Per-item toggle", "Objeto por objeto" },
        { "Counts & capacities", "Cantidades" },
        { "Bottle contents", "Contenido botellas" },
        { "Dungeon items (any dungeon)", "Objetos de mazmorra" },
        { "Charm / Picolyte", "Amuleto / Picolito" },
        { "Jump to current", "Ir al actual" },
        { "Small keys", "Llaves peque\303\261as" },
        { "Big Key", "Llave maestra" },
        { "Compass", "Br\303\272jula" },
        { "Map", "Mapa" },
        { "Sword", "Espada" },
        { "Weapons", "Armas" },
        { "Gear", "Equipamiento" },
        { "Bottles", "Botellas" },
        { "Elements", "Elementos" },
        { "Upgrades", "Mejoras" },
        { "Quest", "Misi\303\263n" },
        { "Sword Techniques", "T\303\251cnicas de espada" },
        { "3D camera angle", "\303\201ngulo c\303\241mara 3D" },
        { "3D tile ahead", "Casilla 3D al frente" },
        { "3D view (experimental)", "Vista 3D (experimental)" },
        { "3D wall height", "Altura muros 3D" },
        { "Aspect ratio", "Relaci\303\263n de aspecto" },
        { "Background", "Fondo" },
        { "Block", "Bloque" },
        { "Floor", "Suelo" },
        { "Prop", "Objeto" },
        { "(CPU fallback)", "(respaldo CPU)" },
        { "CRT filter", "Filtro CRT" },
        { "Decouple game speed", "Separar velocidad" },
        { "Filter", "Filtro" },
        { "Fullscreen", "Pantalla completa" },
        { "GBA colour correction", "Correcci\303\263n de color GBA" },
        { "GLES raster (exp.)", "Raster GLES (exp.)" },
        { "(GPU backend required)", "(requiere GPU)" },
        { "GPU rasterizer", "Rasterizador GPU" },
        { "Hide cursor in fullscreen", "Ocultar cursor" },
        { "Hold to advance text", "Mantener para avanzar texto" },
        { "Internal scale", "Escala interna" },
        { "Label", "Etiqueta" },
        { "LCD persistence", "Persistencia LCD" },
        { "Persistence strength", "Intensidad" },
        { "(needs GPU backend)", "(requiere GPU)" },
        { "(none)", "(ninguno)" },
        { "(often slower than CPU)", "(suele ser m\303\241s lento)" },
        { "Preset load FAILED", "Error al cargar preset" },
        { "Preset loaded", "Preset cargado" },
        { "Renderer", "Renderizador" },
        { "(restart)", "(reiniciar)" },
        { "Rescan", "Buscar" },
        { "Shader preset", "Preset shader" },
        { "Shader preset off", "Shader desactivado" },
        { "Shader preset: %s", "Preset shader: %s" },
        { "Show FPS counter", "Mostrar FPS" },
        { "Target FPS", "FPS objetivo" },
        { "Value", "Valor" },
        { "(SPIR-V backend required)", "(requiere SPIR-V)" },
        { "Widescreen disabled", "Panor\303\241mico desactivado" },
        { "Widescreen enabled", "Panor\303\241mico activado" },
        { "Widescreen (WIP)", "Panor\303\241mico (en desarrollo)" },
        { "Window scale", "Escala de ventana" },
        { "%d tiles (area 0x%02X)", "%d casillas (\303\241rea 0x%02X)" },
        { "(%zu found)", "(%zu encontrados)" },
        { "  active: %s", "  activo: %s" },
        { "active: ...", "activo: ..." },
        { "Console-Parity mode requires the original screen width. Turn it off to enable widescreen.", "El modo Console-Parity exige el ancho original. Desact\303\255valo para usar panor\303\241mico." },
        { "Prop = standing cutout of the outlined object.", "Objeto = recorte de pie del objeto resaltado." },
        { "Ribbon mode (uncheck for classic menu)", "Modo cinta (desmarcar = men\303\272 cl\303\241sico)" },
        { "A button (action)", "Bot\303\263n A (acci\303\263n)" },
        { "Action", "Acci\303\263n" },
        { "Add", "A\303\261adir" },
        { "B button (sword)", "Bot\303\263n B (espada)" },
        { "Bindings", "Asignaciones" },
        { "Bindings reset", "Asignaciones restablecidas" },
        { "Button size", "Tama\303\261o botones" },
        { "Cancel", "Cancelar" },
        { "Capture a bug report (screenshot + save + state)", "Capturar reporte de error (captura + partida + estado)" },
        { "Capture binding", "Capturar asignaci\303\263n" },
        { "Clear", "Borrar" },
        { "Cycle the display filter / smoothing", "Cambiar filtro / suavizado" },
        { "D-pad", "Cruceta" },
        { "D-pad Down", "Cruceta abajo" },
        { "D-pad Left", "Cruceta izq." },
        { "D-pad Right", "Cruceta der." },
        { "D-pad Up", "Cruceta arriba" },
        { "Esc cancels.", "Esc cancela." },
        { "Fast-forward", "Avance r\303\241pido" },
        { "Joystick (floating)", "Joystick (flotante)" },
        { "Key", "Tecla" },
        { "Keyboard shortcuts", "Atajos de teclado" },
        { "L (item slot 1)", "L (objeto 1)" },
        { "R (item slot 2)", "R (objeto 2)" },
        { "Load save-state slot 1-4  (Shift+Fn = save to slot)", "Cargar estado 1-4  (Shift+Fn = guardar)" },
        { "Movement", "Movimiento" },
        { "Open / close this settings menu (gamepad: Select+Start)", "Abrir / cerrar este men\303\272 (mando: Select+Start)" },
        { "Overlay opacity", "Opacidad" },
        { "Practice: pause / frame-advance while paused", "Pr\303\241ctica: pausa / avanzar fotograma" },
        { "Practice: reset timer / record split", "Pr\303\241ctica: reiniciar cron\303\263metro / marcar parcial" },
        { "Practice: set / reload practice point", "Pr\303\241ctica: fijar / recargar punto" },
        { "Press a key or controller button for:", "Pulsa una tecla o bot\303\263n para:" },
        { "Quicksave / quickload", "Guardado / carga r\303\241pida" },
        { "Reset all to defaults", "Restablecer todo" },
        { "Roll attack (D / R3)", "Rodar (D / R3)" },
        { "Roll attack macro", "Macro ataque rodante" },
        { "Save-states (F1-F6) are disabled in Console-Parity mode.", "Los estados (F1-F6) est\303\241n desactivados en modo Console-Parity." },
        { "Set", "Fijar" },
        { "Soft slot L2", "Ranura L2" },
        { "Soft slot R2", "Ranura R2" },
        { "Soft slot X", "Ranura X" },
        { "Soft slot Y", "Ranura Y" },
        { "Speak nearby points of interest  (Shift: next, Ctrl: orient)", "Leer puntos de inter\303\251s cercanos  (Shift: siguiente, Ctrl: orientar)" },
        { "Start (pause)", "Start (pausa)" },
        { "Tab (hold)", "Tab (mantener)" },
        { "The R button glows green when it has an action (talk, read, lift...).", "El bot\303\263n R brilla en verde cuando tiene acci\303\263n (hablar, leer, levantar...)." },
        { "Toggle fullscreen", "Pantalla completa" },
        { "Toggle text-to-speech", "Activar lectura de voz" },
        { "Touch controls", "Controles t\303\241ctiles" },
        { "(unbound)", "(sin asignar)" },
        { "Actions", "Acciones" },
        { "Auto-save", "Autoguard." },
        { "Auto-save on area change", "Autoguardar al cambiar de zona" },
        { "Console-Parity mode (legit-run integrity)", "Modo Console-Parity (integridad)" },
        { "(empty)", "(vac\303\255o)" },
        { "Interval (s)", "Intervalo (s)" },
        { "Leave OFF for practice/casual play.", "D\303\251jalo apagado para pr\303\241ctica o juego casual." },
        { "Load", "Cargar" },
        { "Loaded", "Cargado" },
        { "Quick", "R\303\241pido" },
        { "Quit to Title (no save)", "Salir al t\303\255tulo (sin guardar)" },
        { "Save", "Guardar" },
        { "Save & Quit to Title", "Guardar y salir al t\303\255tulo" },
        { "Saved", "Guardado" },
        { "Save-states disabled while Console-Parity is ON.", "Estados desactivados con Console-Parity activo." },
        { "Slot", "Ranura" },
        { "Slot %d", "Ranura %d" },
        { "Timestamp", "Fecha y hora" },
        { "+ Save current as new profile", "+ Guardar actual como perfil nuevo" },
        { "Activate", "Activar" },
        { "Active profile: %s", "Perfil activo: %s" },
        { "Cannot switch profiles: current save could not be written", "No se puede cambiar: no se pudo escribir la partida actual" },
        { "Confirm delete", "Confirmar borrado" },
        { "Delete", "Borrar" },
        { "Delete refused (active / bad name)", "Borrado rechazado (activo / nombre inv\303\241lido)" },
        { "Delete %s?", "\302\277Borrar %s?" },
        { "No free profile slots (1-99)", "No hay ranuras de perfil libres (1-99)" },
        { "Profile activated - go to title to load", "Perfil activado: ve al t\303\255tulo para cargar" },
        { "Profile deleted", "Perfil borrado" },
        { "Profile File", "Archivo de perfil" },
        { "Profile renamed", "Perfil renombrado" },
        { "Rename", "Renombrar" },
        { "Rename refused (clash / bad name / default)", "Renombrado rechazado (conflicto / nombre inv\303\241lido / predeterminado)" },
        { "Save failed", "Error al guardar" },
        { "Saved current as %s", "Guardado actual como %s" },
        { "Status", "Estado" },
        { "Assigned Item", "Objeto asignado" },
        { "Cycle", "Cambiar" },
        /* I18N_EXTRA_APPLIED */
        { "Rupees", "Rupias" },
        { "Mysterious Shells", "Conchas misteriosas" },
        { "Health (eighths)", "Salud (octavos)" },
        { "Heart pieces", "Piezas de coraz\303\263n" },
        { "Bombs", "Bombas" },
        { "Arrows", "Flechas" },
        { "Wallet tier", "Nivel de cartera" },
        { "Bomb-bag tier", "Nivel bolsa bombas" },
        { "Quiver tier", "Nivel carcaj" },
        { "Bottle %d", "Botella %d" },
        { "Dungeon", "Mazmorra" },
        { "Dungeon %d%s", "Mazmorra %d%s" },
        { "(not owned \342\200\224 pick to grant)", "(no lo tienes: elige para darlo)" },
        { "Charm frames", "Fotogramas amuleto" },
        { "Picolyte frames", "Fotogramas picolito" },
        { "Charm type", "Tipo de amuleto" },
        { "Picolyte type", "Tipo de picolito" },
        { "Apply", "Aplicar" },
        { "%s: inactive", "%s: inactivo" },
        { "%s frames", "%s fotogramas" },
        { "%s active: id %d, %d frames (%.1fs left)", "%s activo: id %d, %d fotogramas (%.1fs restantes)" },
        { "(unassigned)", "(sin asignar)" },
        { "Master volume", "Volumen general" },
        { "GBA-accurate audio", "Audio fiel a la GBA" },
        { "Stereo width", "Ancho est\303\251reo" },
        { "Reverb", "Reverberaci\303\263n" },
        { "Mute Ezlo voice", "Silenciar voz de Ezlo" },
        { "Mute all NPC voice", "Silenciar voz de NPC" },
        { "Mute low-health beep", "Silenciar pitido de vida baja" },
        { "Text-to-speech reads important UI labels aloud (focused buttons, dialogs, errors). Toggle off at any time. Default off; settings persist across launches.", "La lectura de voz lee en voz alta las etiquetas importantes (botones, di\303\241logos, errores). Desact\303\255vala cuando quieras. Apagada por defecto; los ajustes se conservan." },
        { "Backend", "Motor" },
        { "Enable TTS", "Activar voz" },
        { "Rate", "Velocidad" },
        { "Pitch", "Tono" },
        { "Volume", "Volumen" },
        { "Voice", "Voz" },
        { "Language", "Idioma" },
        { "Voice IDs vary by backend (espeak: 'en+f2', say: 'Samantha', SAPI: 'Microsoft David').", "Las voces dependen del motor (espeak: 'es', say: 'Monica', SAPI: 'Microsoft Helena')." },
        { "Test voice", "Probar voz" },
        { "Stop", "Parar" },
        { "Read focus", "Leer foco" },
        { "Scan surroundings (F10)", "Escanear entorno (F10)" },
        { "Cycle (Shift+F10)", "Siguiente (Shift+F10)" },
        { "Look around (Ctrl+F10)", "Mirar alrededor (Ctrl+F10)" },
        { "Passive cues", "Se\303\261ales pasivas" },
        { "Footsteps", "Pasos" },
        { "Hazards", "Peligros" },
        { "Enemy radar", "Radar de enemigos" },
        { "Walls", "Muros" },
        { "Quality-of-life features ported from Minish Cap Reborn (GPL-3.0); see THIRD-PARTY-LICENSES.md. Toggles persist until tmc_pc closes.", "Mejoras de comodidad portadas de Minish Cap Reborn (GPL-3.0); ver THIRD-PARTY-LICENSES.md. Los ajustes duran hasta cerrar tmc_pc." },
        { "Shells cap 9999", "L\303\255mite de conchas 9999" },
        { "Skip Ezlo hint on resume", "Omitir pista de Ezlo al reanudar" },
        { "Raise minimum figurine chance", "Subir prob. m\303\255nima de figuras" },
        { "Skip Ezlo tutorial pop-ups", "Omitir tutoriales de Ezlo" },
        { "Hero Mode (2\303\227 damage)", "Modo H\303\251roe (doble da\303\261o)" },
        { "SELECT-hold writes to soft slots", "Mantener SELECT escribe en ranuras" },
        { "360\302\260 analog stick movement", "Movimiento anal\303\263gico 360\302\260" },
        { "Analog deadzone", "Zona muerta anal\303\263gica" },
        { "Speedrun practice tools. Overlays draw over the game whenever their toggle is on (independent of this menu).", "Herramientas de pr\303\241ctica para speedrun. Las superposiciones se dibujan sobre el juego mientras est\303\251n activas (independiente de este men\303\272)." },
        { "Overlays", "Superposiciones" },
        { "Show IGT timer", "Mostrar cron\303\263metro IGT" },
        { "Show input display", "Mostrar entradas" },
        { "Show input history", "Mostrar historial de entradas" },
        { "Timer", "Cron\303\263metro" },
        { "Reset timer", "Reiniciar cron\303\263metro" },
        { "Split", "Parcial" },
        { "Practice point", "Punto de pr\303\241ctica" },
        { "Set point", "Fijar punto" },
        { "Reload point", "Recargar punto" },
        { "Speed", "Velocidad" },
        { "Slow-mo", "C\303\241mara lenta" },
        { "Pause", "Pausa" },
        { "Hotkeys", "Atajos" },
        { "Direct Level Editor Mode", "Modo editor directo de niveles" },
        { "Enable Direct Painting Overlay", "Activar pintura directa" },
        { "Unavailable on the SDL_GPU renderer backend.", "No disponible con el renderizador SDL_GPU." },
        { "Controls & Hotkeys:", "Controles y atajos:" },
        { "Unlocks are tracked on retroachievements.org while you play. Needs a free RA account and an internet connection.", "Los logros se registran en retroachievements.org mientras juegas. Necesita una cuenta gratuita de RA y conexi\303\263n a internet." },
        { "Enable RetroAchievements", "Activar RetroAchievements" },
        /* I18N_V4_APPLIED */
        { "PROJECT PICORI", "PROYECTO PICORI" },
        { "Minish Cap PC Port", "Port de Minish Cap para PC" },
        { "Version", "Versi\303\263n" },
        { "Change ROM...", "Cambiar ROM..." },
        { "ROM Region & Language", "Regi\303\263n e idioma de la ROM" },
        { "Preferred ROM", "ROM preferida" },
        { "(used when Play starts)", "(se usa al pulsar Jugar)" },
        { "Language is applied after the selected ROM loads.", "El idioma se aplica al cargar la ROM elegida." },
        { "Play", "Jugar" },
        { "Press Enter or click Play to start", "Pulsa Enter o haz clic en Jugar para empezar" },
        { " CLOSE MENU ", " CERRAR MEN\303\232 " },
        { "Gamepad: D-pad nav   A activate   B back", "Mando: cruceta navegar   A activar   B atr\303\241s" },
        { "Close X", "Salir X" },
        { "Bottle 1", "Botella 1" },
        { "Bottle 2", "Botella 2" },
        { "Bottle 3", "Botella 3" },
        { "Bottle 4", "Botella 4" },
        { "(F8 or Select+Start also toggles)", "(F8 o Select+Start tambi\303\251n lo alterna)" },
        { "F5/F6 quicksave/load   F9 bug report   -   see the Controls tab for all hotkeys", "F5/F6 guardado/carga r\303\241pida   F9 reporte de error   -   ver pesta\303\261a Controles" },
        { "L/R bumpers = page jump", "Gatillos L/R = saltar p\303\241gina" },
        { "Teleport (current room):", "Teletransporte (sala actual):" },
        { "Use Link's pos", "Usar posici\303\263n de Link" },
        { "(in-game only)", "(solo en partida)" },
        { "Noclip (walk through walls)", "Atravesar muros (noclip)" },
        { "Shrink to Minish", "Encoger a Minish" },
        { "All", "Todo" },
        { "Native logic randomizer", "Aleatorizador de l\303\263gica nativa" },
        { "Source ROM:  %s", "ROM de origen:  %s" },
        { "Region:      %s", "Regi\303\263n:       %s" },
        { "Logic:       default.logic (%u parsed locations)", "L\303\263gica:       default.logic (%u ubicaciones le\303\255das)" },
        { "No seed rolled - vanilla.", "Sin semilla: modo original." },
        { "Settings", "Ajustes" },
        { "Item pool", "Conjunto de objetos" },
        { "Glitchless logic", "L\303\263gica sin glitches" },
        { "Obscure spots", "Lugares ocultos" },
        { "Shuffle kinstones", "Mezclar kinstones" },
        { "Shuffle entrances", "Mezclar entradas" },
        { "Shuffle dojos", "Mezclar dojos" },
        { "Shuffle dungeon items", "Mezclar objetos de mazmorra" },
        { "Open world", "Mundo abierto" },
        { "Sleep warp (homewarp)", "Viaje al dormir (casa)" },
        { "Start with Smith's Sword", "Empezar con la Espada del Herrero" },
        { "Early Wind Crests", "Emblemas de viento al inicio" },
        { "Fast text (instant text)", "Texto r\303\241pido (instant\303\241neo)" },
        { "Glitch tricks are selectable when Glitchless logic is OFF.", "Los trucos con glitches se pueden elegir si la l\303\263gica sin glitches est\303\241 apagada." },
        { "Cosmetics", "Cosm\303\251ticos" },
        { "Tunic color", "Color de t\303\272nica" },
        { "Heart color", "Color de coraz\303\263n" },
        { "Seed (empty = random)", "Semilla (vac\303\255o = aleatoria)" },
        { "Random", "Aleatoria" },
        { "Copy", "Copiar" },
        { "Roll new seed", "Nueva semilla" },
        { "Roll race seed", "Semilla de carrera" },
        { "Reset to vanilla", "Volver a original" },
        { "Save before quitting?", "\302\277Guardar antes de salir?" },
        { "Save & Quit writes the current game state to quicksave slot 0 (F6 to reload). Quit Without Saving exits immediately - any progress since your last in-game save is lost.", "Guardar y salir escribe el estado actual en la ranura r\303\241pida 0 (F6 para recargar). Salir sin guardar cierra de inmediato: se pierde el progreso desde tu \303\272ltimo guardado en el juego." },
        { "Save & Quit", "Guardar y salir" },
        { "Quit Without Saving", "Salir sin guardar" },
        { "Fires a snapshot to the auto ring every time you transition between areas/rooms. Independent of the interval timer above.", "Guarda una captura automática cada vez que cambias de zona o sala. Es independiente del intervalo anterior." },
        { "Holds the port provably equivalent to GBA hardware for legitimate speedruns:\n  - input edge-cache off (1-frame granularity)\n  - save-states inert (no mid-run restores)\n  - widescreen forced off (no early off-screen AI / RNG advance)\n  - frame pacing locked to 59.7275 Hz\nLeave OFF for practice/casual play.", "Mantiene el port equivalente al hardware de GBA para speedruns legítimos:\n  - caché de entradas desactivada (precisión de 1 fotograma)\n  - estados de guardado inactivos (sin restauraciones durante la partida)\n  - pantalla panorámica desactivada (evita avances anticipados de IA/RNG fuera de pantalla)\n  - frecuencia de fotogramas fijada en 59,7275 Hz\nDéjalo desactivado para practicar o jugar de forma casual." },
        { "Joystick: touch anywhere on the lower-left of the screen to plant the stick there.\nD-pad: fixed four-way pad.", "Joystick: toca cualquier lugar de la parte inferior izquierda de la pantalla para colocarlo allí.\nCruceta: control fijo de cuatro direcciones." },
        { "Hold a direction and press the Roll attack bind to perform a start-of-roll attack with your best sword, regardless of A/B equip.\nDefault: keyboard D, controller R3 (right stick click).", "Mantén una dirección y pulsa el botón de ataque rodante para atacar al iniciar una voltereta con tu mejor espada, independientemente de lo equipado en A/B.\nPredeterminado: tecla D o R3 del mando (pulsar el stick derecho)." },
        { "Click 'Set' to replace an action's binding, or 'Add' to bind an extra key/controller button to it, then press the input. Esc cancels. Mappings save to config.json automatically. In Console-Parity mode each physical input maps to only one action.", "Pulsa «Asignar» para reemplazar la asignación de una acción o «Añadir» para vincular otra tecla o botón del mando. Después, pulsa la entrada que quieras asignar. Esc cancela. Las asignaciones se guardan automáticamente en config.json. En el modo de paridad, cada entrada física solo puede asignarse a una acción." },
        { "A button", "Botón A" },
        { "B button", "Botón B" },
        { "Copy fingerprint", "Copiar huella" },
        { "Share the seed and logic fingerprint to reproduce placements with the same Picori version.", "Comparte la semilla y la huella de la lógica para reproducir las ubicaciones con la misma versión de Picori." },
        { "Off: keys, maps, compasses and big keys shuffle within their own dungeons. On: all four families can appear anywhere (keysanity). Each pickup credits its home dungeon.", "Desactivado: las llaves, mapas, brújulas y llaves grandes se mezclan dentro de sus propias mazmorras. Activado: los cuatro tipos pueden aparecer en cualquier lugar (keysanity). Cada objeto recogido cuenta para su mazmorra de origen." },
        { "Starts with every permanently solvable obstacle pre-solved: cut trees, cracked blocks, bomb walls, boulder shortcuts, non-key doors, bean vines, switches, levers, chest spawns, and extendable bridges (1:1 with the GBA randomizer's World Settings \"Open\"). Less walking, shorter seeds.", "Comienza con todos los obstáculos que pueden resolverse permanentemente ya superados: árboles cortables, bloques agrietados, muros bombardeables, atajos con rocas, puertas sin llave, enredaderas, interruptores, palancas, cofres y puentes extensibles. Equivale a «Open» en los ajustes del mundo del aleatorizador de GBA. Menos recorridos y semillas más cortas." },
        { "Decimal numbers are used as-is; any other text is hashed to a 64-bit seed, so phrases work and are shareable.", "Los números decimales se usan directamente; cualquier otro texto se convierte mediante un hash en una semilla de 64 bits. Puedes usar frases y compartirlas." },
        { "Left-stick displacement below this fraction is ignored, so the D-pad stays authoritative and a thumb resting on the stick won't drift. Raise it for a worn/drifty stick; lower it for a lighter touch. Default 0.30.", "Se ignora el movimiento del stick izquierdo inferior a esta fracción, para que la cruceta siga teniendo prioridad y el pulgar apoyado no provoque movimientos involuntarios. Aumenta el valor si el stick está desgastado o deriva; redúcelo para que responda a toques más suaves. Valor predeterminado: 0,30." }
,
        { "On: Starting a new save slot will roll a randomized seed using the settings below.\n\nOff (default): New slots start as a normal, unmodified vanilla game.", "Activado: al crear una partida nueva se generará una semilla aleatoria con los ajustes siguientes.\n\nDesactivado (predeterminado): las partidas nuevas comienzan el juego original sin modificaciones." },
        { "Off: dungeon items stay in their own dungeons. On: keys, maps, compasses and big keys can appear anywhere.", "Desactivado: los objetos de las mazmorras permanecen en su mazmorra. Activado: las llaves, mapas, brújulas y llaves grandes pueden aparecer en cualquier lugar." },
        { "Every permanent obstacle (trees, cracked blocks, bomb walls, switches, non-key doors, ...) starts pre-solved, matching the GBA randomizer's World Settings \"Open\".", "Todos los obstáculos permanentes (árboles, bloques agrietados, muros bombardeables, interruptores, puertas sin llave, etc.) comienzan resueltos. Equivale a «Open» en los ajustes del mundo del aleatorizador de GBA." },
        { "The exact logic fingerprint appears after generation.", "La huella exacta de la lógica aparece después de generar la semilla." },
        { "(rate/pitch/volume ignored - NVDA controls those)", "(velocidad, tono y volumen los controla NVDA)" },
        { "(unavailable - install spd-say / espeak-ng on Linux)", "(no disponible: instala spd-say o espeak-ng en Linux)" },
        { "(F7 toggles, F6 stops speech)", "(F7 activa o desactiva; F6 detiene la voz)" },
        { "Per-category SFX mutes. Each toggle suppresses", "Silenciar efectos de sonido por categoría. Cada opción silencia" },
        { "VSync", "Sincronización vertical" },
        { "Discord RPC", "Estado de Discord" },
        { "Live entities: %d", "Entidades activas: %d" },
        { "(snapshot, refreshed each frame)", "(instantánea actualizada cada fotograma)" },
        { "(not owned — pick to grant)", "(no obtenido: selecciónalo para concederlo)" },
        { "Session-only: watches are not saved to config.", "Solo para esta sesión: las variables observadas no se guardan en la configuración." },
        { "Add watch", "Añadir variable" },
        { "Clear all", "Borrar todo" },
        { "Enable Randomizer Mode", "Activar modo aleatorio" },
        { "Randomizer Setup", "Configuración del aleatorizador" },
        { "Kinstones", "Piedras kinstone" },
        { "Entrances", "Entradas" },
        { "Dojos", "Dojo" },
        { "Dungeon items", "Objetos de mazmorra" },
        { "Sleep warp", "Teletransporte al dormir" },
        { "Start Sword", "Espada inicial" },
        { "Early Crests", "Crestas tempranas" },
        { "Fast Text", "Texto rápido" },
        { "Generate & Start", "Generar e iniciar" },
        { "Display & Video", "Pantalla y vídeo" },
        { "Audio & Sound", "Audio y sonido" },
        { "Save Profiles", "Perfiles de guardado" },
        { "Close Sidebar", "Cerrar barra lateral" },
        { "Switch to ribbon mode", "Cambiar al modo de cinta" },
        { "Extracting game assets", "Extrayendo recursos del juego" },
        { "Elapsed: %s (%llu frames)", "Transcurrido: %s (%llu fotogramas)" },
        { "Clear splits", "Borrar parciales" },
        { "OK", "Aceptar" },
        { "Progressive Upgrades", "Mejoras progresivas" },
        { "Blue Sword", "Espada azul" },
        { "Red Sword", "Espada roja" },
        { "Green Sword", "Espada verde" },
        { "Smith's Sword", "Espada del herrero" },
        { "Small Shield", "Escudo pequeño" },
        { "Normal Bombs", "Bombas normales" },
        { "Filter by area/check name", "Filtrar por zona o nombre del objetivo" },
        { "Glitch tricks (progression may be placed behind these)", "Trucos de glitches (pueden ser necesarios para progresar)" },
        { "(locked during gameplay)", "(bloqueado durante la partida)" },
        { "Spoiler log hidden (race seed).", "Registro de spoilers oculto (semilla de carrera)." },
        { "Reveal anyway", "Mostrar de todos modos" },
        { "Spoiler log", "Registro de spoilers" },
        { "Copy to clipboard", "Copiar al portapapeles" },
        { "Save .txt", "Guardar .txt" },
        { "Raise the Mysterious Shells cap from 999 to 9999.", "Aumenta el límite de conchas misteriosas de 999 a 9999." },
        { "Press R while holding L to instantly equip Pegasus Boots to slot A.", "Pulsa R mientras mantienes L para equipar inmediatamente las botas de Pegaso en el espacio A." },
        { "Press SELECT while holding L to instantly equip the Ocarina to slot A.", "Pulsa SELECT mientras mantienes L para equipar inmediatamente la ocarina en el espacio A." },
        { "Suppress the area Ezlo hint that fires the first time you re-enter the room after loading a save.", "Oculta la indicación de Ezlo que aparece la primera vez que vuelves a entrar en una sala tras cargar una partida." },
        { "Keep the Royal Hyrule Library accessible after obtaining the Four Sword. Vanilla closes it permanently.", "Mantiene accesible la Biblioteca Real de Hyrule tras obtener la Espada Cuádruple. El juego original la cierra para siempre." },
        { "Increase the floor on figurine-machine drop probability so duplicates take fewer attempts to clear.", "Aumenta la probabilidad mínima de obtener figuras para conseguir duplicados en menos intentos." },
        { "Suppress the early-game Ezlo tutorial hints (movement, signs, talking, etc.). Doesn't affect plot-critical dialogue.", "Oculta los consejos iniciales de Ezlo (movimiento, letreros, conversaciones, etc.). No afecta a los diálogos importantes de la historia." },
        { "Enemies and hazards deal double damage. Toggleable mid-run; takes effect from the next hit.", "Los enemigos y peligros infligen el doble de daño. Se puede activar durante la partida; surte efecto desde el siguiente golpe." },
        { "Hold L while pressing A or B to fire the item assigned to the port's soft-slot 0 / soft-slot 1 (settable via SELECT-hold in the pause menu, or via the existing X/Y/L2/R2 soft-slot binding UI).", "Mantén L y pulsa A o B para usar el objeto asignado al espacio rápido 0 o 1. Se configura manteniendo SELECT en el menú de pausa o desde los controles X/Y/L2/R2." },
        { "Hold SELECT while pressing A in the pause menu to assign the cursor's item to soft-slot 0 (or B → soft-slot 1) instead of the primary A/B slot. Soft slots persist to the port config, not the save file.", "Mantén SELECT y pulsa A en el menú de pausa para asignar el objeto seleccionado al espacio rápido 0 (o B para el espacio 1), en lugar del espacio principal A/B. Los espacios rápidos se guardan en la configuración del port, no en la partida." },
        { "Move Link with the left analog stick at any of 32 angles (11.25° each) instead of the D-pad's 8. Walk speed is unchanged — only the direction Link faces and walks toward.", "Mueve a Link con el stick analógico izquierdo en cualquiera de 32 direcciones (11,25° cada una), en lugar de las 8 del pad direccional. La velocidad no cambia, solo la dirección en la que mira y camina." },
    };
    return d;
}

/* Warp tab rows look like "0x03  Hyrule Field  (10 rooms)": translate name + "rooms". */
inline const std::unordered_map<std::string, const char*>& AreaNames() {
    static const std::unordered_map<std::string, const char*> d = {
        { "Minish Woods", "Bosque Minish" },
        { "Minish Village", "Aldea Minish" },
        { "Hyrule Town", "Ciudad de Hyrule" },
        { "Hyrule Field", "Campo de Hyrule" },
        { "Castor Wilds", "Tierras de Castor" },
        { "Wind Ruins", "Ruinas del Viento" },
        { "Mt Crenel", "Monte Crenel" },
        { "Castle Garden", "Jard\303\255n del Castillo" },
        { "Cloud Tops", "Cumbres de las Nubes" },
        { "Royal Valley", "Valle Real" },
        { "Veil Falls", "Cascada del Velo" },
        { "Lake Hylia", "Lago Hylia" },
        { "Lake Woods Cave", "Cueva del Bosque del Lago" },
        { "Beanstalks", "Tallos de jud\303\255a" },
        { "Hyrule Dig Caves", "Cuevas excavadas de Hyrule" },
        { "Melari's Mines", "Minas de Melari" },
        { "Minish Paths", "Sendas Minish" },
        { "Crenel Minish Paths", "Sendas Minish de Crenel" },
        { "Dig Caves", "Cuevas excavadas" },
        { "Crenel Dig Cave", "Cueva excavada de Crenel" },
        { "Festival Town", "Ciudad del Festival" },
        { "Veil Falls Dig Cave", "Cueva excavada del Velo" },
        { "Castor Wilds Dig Cave", "Cueva excavada de Castor" },
        { "Outer Fortress of Winds", "Exterior Fortaleza Viento" },
        { "Hylia Dig Caves", "Cuevas excavadas de Hylia" },
        { "Veil Falls Top", "Cima de Cascada del Velo" },
        { "Minish House Interiors", "Interiores casas Minish" },
        { "House Interiors 1", "Interiores de casas 1" },
        { "House Interiors 2", "Interiores de casas 2" },
        { "House Interiors 3", "Interiores de casas 3" },
        { "House Interiors 4", "Interiores de casas 4" },
        { "Tree Interiors", "Interiores de \303\241rboles" },
        { "Dojos", "Dojos" },
        { "Crenel Caves", "Cuevas de Crenel" },
        { "Minish Cracks", "Grietas Minish" },
        { "Great Fairies", "Grandes Hadas" },
        { "Castor Caves", "Cuevas de Castor" },
        { "Castor Darknut", "Darknut de Castor" },
        { "Armos Interiors", "Interiores Armos" },
        { "Town Minish Holes", "Agujeros Minish de la ciudad" },
        { "Minish Rafters", "Vigas Minish" },
        { "Goron Cave", "Cueva Goron" },
        { "Wind Tribe Tower", "Torre Tribu del Viento" },
        { "Wind Tribe Tower Roof", "Azotea Torre Tribu Viento" },
        { "Caves", "Cuevas" },
        { "Veil Falls Caves", "Cuevas de Cascada del Velo" },
        { "Royal Valley Graves", "Tumbas del Valle Real" },
        { "Minish Caves", "Cuevas Minish" },
        { "Castle Garden Minish Holes", "Agujeros Minish del Jard\303\255n" },
        { "Ezlo Cutscene", "Escena de Ezlo" },
        { "Hyrule Town Underground", "Subsuelo de Ciudad de Hyrule" },
        { "Garden Fountains", "Fuentes del Jard\303\255n" },
        { "Hyrule Castle Cellar", "S\303\263tano del Castillo" },
        { "Deepwood Shrine", "Santuario Bosque Profundo" },
        { "Deepwood Shrine - boss", "Santuario Bosque Profundo - jefe" },
        { "Deepwood Shrine - entry", "Santuario Bosque Profundo - entrada" },
        { "Cave of Flames", "Cueva de las Llamas" },
        { "Cave of Flames - boss", "Cueva de las Llamas - jefe" },
        { "Fortress of Winds", "Fortaleza del Viento" },
        { "Fortress of Winds Top", "Cima Fortaleza del Viento" },
        { "Inner Mazaal", "Interior de Mazaal" },
        { "Temple of Droplets", "Templo de las Gotas" },
        { "Hyrule Town Minish Caves", "Cuevas Minish de la Ciudad" },
        { "Royal Crypt", "Cripta Real" },
        { "Palace of Winds", "Palacio de los Vientos" },
        { "Palace of Winds - boss", "Palacio de los Vientos - jefe" },
        { "Sanctuary", "Santuario" },
        { "Sanctuary Entrance", "Entrada del Santuario" },
        { "Hyrule Castle", "Castillo de Hyrule" },
        { "Dark Hyrule Castle", "Castillo Oscuro de Hyrule" },
        { "Dark Hyrule Castle Outside", "Exterior Castillo Oscuro" },
        { "Vaati's Arms", "Brazos de Vaati" },
        { "Vaati 3", "Vaati 3" },
        { "Vaati 2", "Vaati 2" },
        { "Dark Hyrule Castle Bridge", "Puente Castillo Oscuro" }
    };
    return d;
}
inline const char* TranslateArea(const char* s) {
    if (!s || s[0] != '0' || s[1] != 'x') return nullptr;
    std::string in(s);
    size_t a = in.find("  ");
    if (a == std::string::npos) return nullptr;
    size_t nameStart = a + 2;
    size_t b = in.find("  (", nameStart);
    if (b == std::string::npos) return nullptr;
    std::string name = in.substr(nameStart, b - nameStart);
    auto it = AreaNames().find(name);
    std::string out = in.substr(0, nameStart) + (it != AreaNames().end() ? it->second : name.c_str()) + in.substr(b);
    size_t r = out.find(" rooms)");
    if (r != std::string::npos) out.replace(r, 7, " salas)");
    static thread_local std::string ring[8];
    static thread_local int idx = 0;
    std::string& slot = ring[idx++ & 7];
    slot = out;
    return slot.c_str();
}

/* I18N_COLLECTOR_APPLIED
 * Run with TMC_I18N_COLLECT=1 to log every menu string that has no translation
 * to ./i18n_sin_traducir.txt (one per line, newlines written as \n). */
inline void Collect(const std::string& k) {
    static const bool on = std::getenv("TMC_I18N_COLLECT") != nullptr;
    if (!on || k.empty()) return;
    static std::unordered_set<std::string> seen;
    if (!seen.insert(k).second) return;
    int run = 0; bool ok = false;
    for (unsigned char c : k) {
        if (std::isalpha(c)) { if (++run >= 3) { ok = true; break; } } else run = 0;
    }
    if (!ok) return;
    FILE* f = std::fopen("i18n_sin_traducir.txt", "a");
    if (!f) return;
    for (char c : k) { if (c == '\n') std::fputs("\\n", f); else std::fputc(c, f); }
    std::fputc('\n', f);
    std::fclose(f);
}

/* Translate a label. Keeps the "##id" suffix so ImGui widget IDs stay valid. */
inline const char* T(const char* s) {
    if (!s || !Port_Config_GetMenuLangEs()) return s;
    if (const char* ar = TranslateArea(s)) return ar;
    const char* hash = std::strstr(s, "##");
    if (!hash) {
        auto it = Dict().find(s);
        if (it != Dict().end()) return it->second;
        Collect(s);
        return s;
    }
    auto it = Dict().find(std::string(s, (size_t)(hash - s)));
    if (it == Dict().end()) { Collect(std::string(s, (size_t)(hash - s))); return s; }
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
    const char* t = (l && std::strcmp(l, "Accessibility") == 0 && Port_Config_GetMenuLangEs()) ? "Accesib." : T(l);
    return ImGui::BeginTabItem(t, p, f);
}
inline void SeparatorText(const char* l) { ImGui::SeparatorText(T(l)); }
inline bool CollapsingHeader(const char* l, ImGuiTreeNodeFlags f = 0) {
    return ImGui::CollapsingHeader(T(l), f);
}
inline bool CollapsingHeader(const char* l, bool* vis, ImGuiTreeNodeFlags f = 0) {
    return ImGui::CollapsingHeader(T(l), vis, f);
}
/* Text("%s", label): translate the argument instead of the format. */
inline bool IsPlainS(const char* f) { return f && f[0] == '%' && f[1] == 's' && f[2] == 0; }

inline void TextUnformatted(const char* t, const char* end = nullptr) {
    ImGui::TextUnformatted(end ? t : T(t), end);
}
inline void Text(const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::Text("%s", T(x)); }
    else ImGui::TextV(T(fmt), a);
    va_end(a);
}
inline void TextDisabled(const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::TextDisabled("%s", T(x)); }
    else ImGui::TextDisabledV(T(fmt), a);
    va_end(a);
}
inline void TextWrapped(const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::TextWrapped("%s", T(x)); }
    else ImGui::TextWrappedV(T(fmt), a);
    va_end(a);
}
inline void TextColored(const ImVec4& col, const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::TextColored(col, "%s", T(x)); }
    else ImGui::TextColoredV(col, T(fmt), a);
    va_end(a);
}
/* Only the label is translated; every other argument is forwarded untouched. */
template <class... A> inline bool Combo(const char* l, A&&... a) { return ImGui::Combo(T(l), std::forward<A>(a)...); }
template <class... A> inline bool SliderInt(const char* l, A&&... a) { return ImGui::SliderInt(T(l), std::forward<A>(a)...); }
template <class... A> inline bool SliderFloat(const char* l, A&&... a) { return ImGui::SliderFloat(T(l), std::forward<A>(a)...); }
template <class... A> inline void TableSetupColumn(const char* l, A&&... a) { ImGui::TableSetupColumn(T(l), std::forward<A>(a)...); }

template <class... A> inline bool Selectable(const char* l, A&&... a) { return ImGui::Selectable(T(l), std::forward<A>(a)...); }
template <class... A> inline bool RadioButton(const char* l, A&&... a) { return ImGui::RadioButton(T(l), std::forward<A>(a)...); }
template <class... A> inline bool BeginCombo(const char* l, A&&... a) { return ImGui::BeginCombo(T(l), std::forward<A>(a)...); }
template <class... A> inline bool InputText(const char* l, A&&... a) { return ImGui::InputText(T(l), std::forward<A>(a)...); }
template <class... A> inline bool InputInt(const char* l, A&&... a) { return ImGui::InputInt(T(l), std::forward<A>(a)...); }
template <class... A> inline bool InputFloat(const char* l, A&&... a) { return ImGui::InputFloat(T(l), std::forward<A>(a)...); }
template <class... A> inline bool DragInt(const char* l, A&&... a) { return ImGui::DragInt(T(l), std::forward<A>(a)...); }
template <class... A> inline bool DragFloat(const char* l, A&&... a) { return ImGui::DragFloat(T(l), std::forward<A>(a)...); }
template <class... A> inline bool ColorEdit3(const char* l, A&&... a) { return ImGui::ColorEdit3(T(l), std::forward<A>(a)...); }
template <class... A> inline bool ColorEdit4(const char* l, A&&... a) { return ImGui::ColorEdit4(T(l), std::forward<A>(a)...); }
inline void SetTooltip(const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::SetTooltip("%s", T(x)); }
    else ImGui::SetTooltipV(T(fmt), a);
    va_end(a);
}
inline void SetItemTooltip(const char* fmt, ...) {
    va_list a; va_start(a, fmt);
    if (IsPlainS(fmt)) { const char* x = va_arg(a, const char*); ImGui::SetItemTooltip("%s", T(x)); }
    else ImGui::SetItemTooltipV(T(fmt), a);
    va_end(a);
}

} // namespace I18n
