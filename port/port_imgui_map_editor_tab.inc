/* Map Editor ribbon tab — extracted from port_imgui_menu.cpp. Included into the same
 * translation unit; relies on the declarations already visible there. */
extern "C" bool Port_LevelEditor_IsOpen(void);
extern "C" void Port_LevelEditor_Toggle(void);
extern "C" void Port_LevelEditor_Render(void* renderer, int winW, int winH);

static void DrawRibbonMapEditorTab(void) {
    I18n::TextColored(ImVec4(0.4f, 0.8f, 0.4f, 1.0f), "Direct Level Editor Mode");
    ImGui::Separator();
    bool editorOpen = Port_LevelEditor_IsOpen();
#ifdef TMC_GPU_RENDERER
    /* The overlay draws with SDL_Renderer primitives; there is nothing to
     * draw it with on the SDL_GPU path, so painting would be blind. */
    const bool noOverlay = (sRenderer == nullptr);
#else
    const bool noOverlay = false;
#endif
    ImGui::BeginDisabled(noOverlay);
    if (I18n::Checkbox("Enable Direct Painting Overlay", &editorOpen)) {
        Port_LevelEditor_Toggle();
        if (editorOpen) {
            extern void Port_DebugMenu_Toggle(void);
            Port_DebugMenu_Toggle();
        }
    }
    ImGui::EndDisabled();
    if (noOverlay)
        I18n::TextDisabled("Unavailable on the SDL_GPU renderer backend.");
    ImGui::Separator();
    I18n::TextDisabled("Controles y atajos:");
    ImGui::BulletText("Clic izquierdo: pintar la casilla seleccionada");
    ImGui::BulletText("Clic derecho: cuentagotas (copiar casilla)");
    ImGui::BulletText("[ / ]        : ID de casilla anterior/siguiente (Mayús: saltar 16)");
    ImGui::BulletText("L: cambiar entre capas superior e inferior");
    ImGui::BulletText("M / F        : Música siguiente / música de combate (Mayús: anterior)");
    ImGui::BulletText("K            : Aumentar iluminación (Mayús: reducir)");
    ImGui::BulletText("S            : Guardar habitación en edited_levels/");
    ImGui::BulletText("Esc: cerrar el editor de niveles");
}
