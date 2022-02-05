//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ShaderEditor.h>


// Constructor
Window_ShaderEditor::Window_ShaderEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<VisualRenderer> VisualRenderer) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    VisualRenderer_ = VisualRenderer;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI ShaderEditor Window", 4);


    // Setup Editors
    Editors_.push_back(std::make_shared<TextEditor>());
    Editors_.push_back(std::make_shared<TextEditor>());

    // Load Shader
    ReloadEditorText();

    // Setup Shader Loader
    ShaderLoader_ = std::make_shared<ERS_CLASS_ShaderLoader>(SystemUtils_);
    LivePreviewShader_ = std::make_shared<ERS_STRUCT_Shader>();



}

// Destructor
Window_ShaderEditor::~Window_ShaderEditor() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI ShaderEditor Window Destructor Called", 6);

}


// Reload Assets
void Window_ShaderEditor::ReloadEditorText() {

    // Load Vertex Shader
    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].VertexID, Data);
    std::string VertexText = std::string((const char*)Data->Data.get());

    // Load Fragment Shader
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].FragmentID, Data);
    std::string  FragmentText = std::string((const char*)Data->Data.get());

    // Set Editor Text
    Editors_[0]->SetText(VertexText);
    Editors_[1]->SetText(FragmentText);
    Editor_ = Editors_[Mode_];

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

    // Check Enable Change
    if (LastEnabledState_ != Enabled_) {

        // If Just Enabled
        if (Enabled_) {
            LivePreviewShaderIndex_ = VisualRenderer_->Shaders_.size();
        } else {


            // Set Any Viewports Shaders To 0 Who Are Using This Shader
            for (int i = 0; i < VisualRenderer_->Viewports_.size(); i++) {
                if (VisualRenderer_->Viewports_[i]->ShaderIndex == LivePreviewShaderIndex_) {
                    VisualRenderer_->Viewports_[i]->ShaderIndex = 0;
                }
            }

            // Remove Shader From List
            VisualRenderer_->Shaders_.erase(LivePreviewShaderIndex_);


        }

        // Update Last State
        LastEnabledState_ = Enabled_;
    }

    // Draw Windows
    if (Enabled_) {
    
        DrawEditorWindow();
        DrawToolsWindow();

    }


}




// Draw The Editor Window
void Window_ShaderEditor::DrawEditorWindow() {

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
                        SaveShader(Editors_[0]->GetText(), ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].VertexID);
                        SaveShader(Editors_[1]->GetText(), ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_].FragmentID);

                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit"))
                {
                    bool ro = Editor_->IsReadOnly();
                    if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                        Editor_->SetReadOnly(ro);
                    ImGui::Separator();

                    if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && Editor_->CanUndo()))
                        Editor_->Undo();
                    if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && Editor_->CanRedo()))
                        Editor_->Redo();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, Editor_->HasSelection()))
                        Editor_->Copy();
                    if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && Editor_->HasSelection()))
                        Editor_->Cut();
                    if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && Editor_->HasSelection()))
                        Editor_->Delete();
                    if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                        Editor_->Paste();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Select all", nullptr, nullptr))
                        Editor_->SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(Editor_->GetTotalLines(), 0));

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View"))
                {
                    if (ImGui::MenuItem("Dark palette"))
                        Editor_->SetPalette(TextEditor::GetDarkPalette());
                    if (ImGui::MenuItem("Light palette"))
                        Editor_->SetPalette(TextEditor::GetLightPalette());
                    if (ImGui::MenuItem("Retro blue palette"))
                        Editor_->SetPalette(TextEditor::GetRetroBluePalette());
                    ImGui::EndMenu();
                }
            
                if (ImGui::BeginMenu("Shader")) {

                    // Mode Menu
                    if (ImGui::BeginMenu("Mode")) {

                        if (ImGui::MenuItem("Vertex", nullptr, (Mode_==0))) {
                            Mode_ = 0;
                            Editor_ = Editors_[Mode_];
                            Editor_->Render("Shader Editor");
                        }
                        if (ImGui::MenuItem("Fragment", nullptr, (Mode_==1))) {
                            Mode_ = 1;
                            Editor_ = Editors_[Mode_];
                            Editor_->Render("Shader Editor");
                        }

                    // New Shader Menu
                    if (ImGui::MenuItem("New Shader Program")) {

                        // ERS_STRUCT_ShaderProgramAssetIDs ShaderProgram;
                        // ShaderProgram.Name = "Untitled";
                        // ShaderProgram.FragmentID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        // ShaderProgram.VertexID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        // ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.push_back(ShaderProgram);

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
            Editor_->Render("Shader Editor");


        }
    ImGui::End();

}


// Draw The Tools Window
void Window_ShaderEditor::DrawToolsWindow() {

    bool CompileVisible = ImGui::Begin("Shader Tools", &Enabled_);

        // Compile Shader Object
        std::string VertexText = Editors_[0]->GetText();
        std::string FragmentText = Editors_[1]->GetText();

        LivePreviewShader_->~ERS_STRUCT_Shader();
        LivePreviewShader_ = std::make_shared<ERS_STRUCT_Shader>();
        std::string VertexLog = LivePreviewShader_->CompileVertexShader(VertexText.c_str());
        std::string FragmentLog = LivePreviewShader_->CompileFragmentShader(FragmentText.c_str());
        LivePreviewShader_->CreateShaderProgram();
        bool ShaderCompiled = LivePreviewShader_->MakeActive();
        LivePreviewShader_->SetInt("texture_diffuse1", 0);
        LivePreviewShader_->DisplayName = "Preview Shader";
        LivePreviewShader_->InternalName = "Preview Shader";


        // If Autopreview, Update Shader
        if (LivePreview_ && ShaderCompiled) {
            VisualRenderer_->SetShader(LivePreviewShader_, LivePreviewShaderIndex_);
        }


        // Extract Shader Log
        std::string ShaderLog;
        if (Mode_ == 0) {
            ShaderLog = VertexLog;
        } else if (Mode_ == 1) {
            ShaderLog = FragmentLog;
        }

        if (ShaderLog == "") {
            ShaderLog = "No errors detected.";
        }


        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);


        if (CompileVisible) {


            // Draw The Controls
            ImGui::Checkbox("Live Preview", &LivePreview_);
            ImGui::Separator();

            // Draw Log
            ImGui::BeginChild("Shader Log");
            ImGui::TextWrapped("%s", ShaderLog.c_str());
            ImGui::EndChild();

        }


 
    ImGui::End();

}


