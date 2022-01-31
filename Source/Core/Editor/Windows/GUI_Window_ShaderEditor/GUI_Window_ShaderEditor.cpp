//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ShaderEditor.h>


// Constructor
Window_ShaderEditor::Window_ShaderEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI ShaderEditor Window", 4);

}

// Destructor
Window_ShaderEditor::~Window_ShaderEditor() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI ShaderEditor Window Destructor Called", 6);

}


// Draw Window
void Window_ShaderEditor::Draw() {

if (Enabled_) {
    bool Visible = ImGui::Begin("Shader Editor", &Enabled_, ImGuiWindowFlags_MenuBar);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);


        if (Visible) {
 
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Save"))
                    {
                        std::string textToSave = Editor_.GetText();
                        /// save text....
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit"))
                {
                    bool ro = Editor_.IsReadOnly();
                    if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                        Editor_.SetReadOnly(ro);
                    ImGui::Separator();

                    if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && Editor_.CanUndo()))
                        Editor_.Undo();
                    if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && Editor_.CanRedo()))
                        Editor_.Redo();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, Editor_.HasSelection()))
                        Editor_.Copy();
                    if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && Editor_.HasSelection()))
                        Editor_.Cut();
                    if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && Editor_.HasSelection()))
                        Editor_.Delete();
                    if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                        Editor_.Paste();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Select all", nullptr, nullptr))
                        Editor_.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(Editor_.GetTotalLines(), 0));

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View"))
                {
                    if (ImGui::MenuItem("Dark palette"))
                        Editor_.SetPalette(TextEditor::GetDarkPalette());
                    if (ImGui::MenuItem("Light palette"))
                        Editor_.SetPalette(TextEditor::GetLightPalette());
                    if (ImGui::MenuItem("Retro blue palette"))
                        Editor_.SetPalette(TextEditor::GetRetroBluePalette());
                    ImGui::EndMenu();
                }
            
                if (ImGui::BeginMenu("Shader")) {

                    if (ImGui::MenuItem("Vertex")) {
                        Mode_ = 0;
                    }
                    if (ImGui::MenuItem("Fragment")) {
                        Mode_ = 1;
                    }
                ImGui::EndMenu();
                }
            
            ImGui::EndMenuBar();
            }



            // Render Editor
            Editor_.Render("Shader Editor");

        }

    ImGui::End();
    }

}