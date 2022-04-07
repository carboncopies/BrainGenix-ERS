//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ScriptEditor.h>


Window_ScriptEditor::Window_ScriptEditor(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    SystemUtils_->Logger_->Log("Initializing GUI ScriptEditor Window", 4);


    Editor_ = std::make_unique<TextEditor>();

    ReloadEditorText(0);
}

Window_ScriptEditor::~Window_ScriptEditor() {

    SystemUtils_->Logger_->Log("GUI ScriptEditor Window Destructor Called", 6);

}


void Window_ScriptEditor::ReloadEditorText(int ScriptIndex) {

    // Perform Sanity Check
    std::string Code;
    if (ScriptIndex >= ProjectUtils_->ProjectManager_->Project_.Scripts.size()) {
        Code = "Script Loading Error";
    } else {
        Code = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndex].Code_;
    }

    // Set Editor Text
    Editor_->SetText(Code);

}


void Window_ScriptEditor::SaveScript(std::string ScriptText, long AssetID) {

    // Write Data
    std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
    
    Data->Data.reset(new unsigned char[ScriptText.size()]);
    Data->Size_B = ScriptText.size();
    memcpy(Data->Data.get(), ScriptText.c_str(), ScriptText.size());

    // Write To Storage
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(AssetID, Data.get());


}

void Window_ScriptEditor::Draw() {

    // Check Enable Change
    if (LastEnabledState_ != Enabled_) {

        // If Just Enabled
        if (Enabled_) {
            LivePreviewScriptIndex_ = VisualRenderer_->Scripts_.size();
        } else {


            // Set Any Viewports Scripts To 0 Who Are Using This Script
            for (int i = 0; (long)i < (long)VisualRenderer_->Viewports_.size(); i++) {
                if (VisualRenderer_->Viewports_[i]->ScriptIndex == LivePreviewScriptIndex_) {
                    VisualRenderer_->Viewports_[i]->ScriptIndex = 0;
                }
            }

            // Remove Script From List
            VisualRenderer_->Scripts_.erase(LivePreviewScriptIndex_);


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



void Window_ScriptEditor::DrawEditorWindow() {

    bool Visible = ImGui::Begin("Script Editor", &Enabled_, ImGuiWindowFlags_MenuBar);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);

        if (Visible) {


            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {


                    // New Script Option
                    if (ImGui::MenuItem("New")) {

                        // ERS_STRUCT_ScriptProgramAssetIDs ScriptProgram;
                        // ScriptProgram.Name = "Untitled";
                        // ScriptProgram.FragmentID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        // ScriptProgram.VertexID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        // ProjectUtils_->ProjectManager_->Project_.ScriptPrograms.push_back(ScriptProgram);

                    }

                    // Program Selector Dropdown
                    if (ImGui::BeginMenu("Open")) {

                        for (long i = 0; (long)i < (long)ProjectUtils_->ProjectManager_->Project_.ScriptPrograms.size(); i++) {

                            std::string ScriptProgramName = ProjectUtils_->ProjectManager_->Project_.ScriptPrograms[i].Name;
                            if (ImGui::MenuItem(ScriptProgramName.c_str())) {

                                // Update Index, REload
                                SelectedScriptProgramIndex_ = i;
                                ReloadEditorText();

                            }
                        }


                    ImGui::EndMenu();
                    }

                    // Save Options
                    ImGui::Separator();
                    if (ImGui::MenuItem("Save")) {
                        if (Mode_ == 0) {
                            SaveScript(Editors_[0]->GetText(), ProjectUtils_->ProjectManager_->Project_.ScriptPrograms[SelectedScriptProgramIndex_].VertexID);
                        } else {
                            SaveScript(Editors_[1]->GetText(), ProjectUtils_->ProjectManager_->Project_.ScriptPrograms[SelectedScriptProgramIndex_].FragmentID);
                        }
                    }

                    if (ImGui::MenuItem("Save All")) {
                        SaveScript(Editors_[0]->GetText(), ProjectUtils_->ProjectManager_->Project_.ScriptPrograms[SelectedScriptProgramIndex_].VertexID);
                        SaveScript(Editors_[1]->GetText(), ProjectUtils_->ProjectManager_->Project_.ScriptPrograms[SelectedScriptProgramIndex_].FragmentID);
                    }


                    // Exit Button
                    ImGui::Separator();
                    if (ImGui::MenuItem("Exit")) {
                        Enabled_ = false;
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
            

                // Vertex/Fragment Mode Selector
                if (ImGui::BeginMenu("Mode")) {
                    
                    if (ImGui::MenuItem("Vertex", nullptr, (Mode_==0))) {
                        Mode_ = 0;
                        Editor_ = Editors_[Mode_];
                        Editor_->Render("Script Editor");
                    }

                    if (ImGui::MenuItem("Fragment", nullptr, (Mode_==1))) {
                        Mode_ = 1;
                        Editor_ = Editors_[Mode_];
                        Editor_->Render("Script Editor");
                    }


                ImGui::EndMenu();
                }

            
            ImGui::EndMenuBar();
            }


            // Render Editor
            Editor_->Render("Script Editor");


        }
    ImGui::End();

}


void Window_ScriptEditor::DrawToolsWindow() {

    bool CompileVisible = ImGui::Begin("Script Tools", &Enabled_);

        // Compile Script Object
        std::string VertexText = Editors_[0]->GetText();
        std::string FragmentText = Editors_[1]->GetText();

        LivePreviewScript_->~ERS_STRUCT_Script();
        LivePreviewScript_ = std::make_shared<ERS_STRUCT_Script>();
        std::string VertexLog = LivePreviewScript_->CompileVertexScript(VertexText.c_str());
        std::string FragmentLog = LivePreviewScript_->CompileFragmentScript(FragmentText.c_str());
        LivePreviewScript_->CreateScriptProgram();
        bool ScriptCompiled = LivePreviewScript_->MakeActive();
        LivePreviewScript_->SetInt("texture_diffuse1", 0);
        LivePreviewScript_->DisplayName = "Preview Script";
        LivePreviewScript_->InternalName = "Preview Script";


        // If Autopreview, Update Script
        if (ScriptCompiled) {
            VisualRenderer_->SetScript(LivePreviewScript_, LivePreviewScriptIndex_);
        }


        // Extract Script Log
        std::string ScriptLog;
        if (Mode_ == 0) {
            ScriptLog = VertexLog;
        } else if (Mode_ == 1) {
            ScriptLog = FragmentLog;
        }

        if (ScriptLog == "") {
            ScriptLog = "No errors detected.";
        }


        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);


        if (CompileVisible) {

            // Draw Log
            ImGui::BeginChild("Script Log");
            ImGui::TextWrapped("%s", ScriptLog.c_str());
            ImGui::EndChild();

        }


 
    ImGui::End();

}


