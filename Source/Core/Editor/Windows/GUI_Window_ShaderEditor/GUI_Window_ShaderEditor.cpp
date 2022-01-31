//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ShaderEditor.h>


// Constructor
Window_ShaderEditor::Window_ShaderEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI ShaderEditor Window", 4);

    // Load Shader
    ReloadEditorText();

    // Setup Shader Loader
    ShaderLoader_ = std::make_shared<ERS_CLASS_ShaderLoader>(SystemUtils_);



}

// Destructor
Window_ShaderEditor::~Window_ShaderEditor() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI ShaderEditor Window Destructor Called", 6);

}


// Reload Assets
void Window_ShaderEditor::ReloadEditorText() {

    // Get Selected Asset Index
    long AssetID;
    if (Mode_ == 0) {
        AssetID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].VertexID;
    } else if (Mode_ == 1) {
        AssetID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].FragmentID;
    }

    // Load The Selected File
    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, Data);
    std::string Text = std::string((const char*)Data->Data.get());

    // Update Editor Text
    Editor_.SetText(Text);

}


// Save Shader
void Window_ShaderEditor::SaveShader(std::string ShaderText, long AssetID) {

    // Write Data
    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    
    Data->Data.reset(new unsigned char[ShaderText.size()]);
    Data->Size_B = ShaderText.size();
    memcpy(Data->Data.get(), ShaderText.c_str(), ShaderText.size());

    // Write To Storage
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(AssetID, Data);


}

// Draw Window
void Window_ShaderEditor::Draw() {

if (Enabled_) {
    bool Visible = ImGui::Begin("Shader Editor", &Enabled_, ImGuiWindowFlags_MenuBar);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);


        if (Visible) {
 
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Save"))
                    {
                        // Write The Asset
                        long AssetID;
                        if (Mode_ == 0) {
                            AssetID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].VertexID;
                        } else if (Mode_ == 1) {
                            AssetID = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].FragmentID;
                        }

                        std::string TextToSave = Editor_.GetText();

                        SaveShader(TextToSave, AssetID);
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

                    // Mode Menu
                    if (ImGui::BeginMenu("Mode")) {

                        if (ImGui::MenuItem("Vertex", nullptr, (Mode_==0))) {
                            Mode_ = 0;
                            ReloadEditorText();
                        }
                        if (ImGui::MenuItem("Fragment", nullptr, (Mode_==1))) {
                            Mode_ = 1;
                            ReloadEditorText();
                        }

                    ImGui::EndMenu();
                    }

                    // Shader Dropdown
                    if (ImGui::BeginMenu("Programs")) {

                        for (long i = 0; i < ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.size(); i++) {

                            std::string ShaderProgramName = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].Name;
                            if (ImGui::MenuItem(ShaderProgramName.c_str())) {

                                // Update Index, REload
                                SelectedShaderProgramIndex_ = i;
                                ReloadEditorText();


                            }

                        }


                    ImGui::EndMenu();
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