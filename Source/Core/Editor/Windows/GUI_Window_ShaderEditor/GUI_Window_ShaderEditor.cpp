//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ShaderEditor.h>


GUI_Window_ShaderEditor::GUI_Window_ShaderEditor(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_VisualRenderer* VisualRenderer) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    VisualRenderer_ = VisualRenderer;
    SystemUtils_->Logger_->Log("Initializing GUI ShaderEditor Window", 4);


    for (int i = 0; i < ShaderStageCount_; i++) {
        Editors_.push_back(std::make_shared<TextEditor>());
    }
    
    ReloadEditorText();

    ShaderLoader_ = std::make_unique<ERS_CLASS_ShaderLoader>(SystemUtils_);


    // Set Default Shader Text
    NewShaderVertexText_ = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "layout (location = 2) in vec2 aTexCoords;\n"
    "\n"
    "out vec2 TexCoords;\n"
    "\n"
    "\n"
    "// Set Model Info\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "// Get Input Vars\n"
    "uniform float Time; // Time since program started in seconds\n"
    "uniform float FrameTime; // Render Time Of The Frame\n"
    "uniform int FrameNumber; // Number of the frame, counts up from zero\n"
    "uniform vec2 ViewportRes; // XY Resolution of the viewport\n"
    "\n"
    "\n"
    "\n"
    "void main()\n"
    "{\n"
    "    TexCoords = aTexCoords;    \n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\n";

    NewshaderFragmentText_ = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "in vec2 TexCoords;\n"
    "\n"
    "// Get Texture Sampler And Lighting Info\n"
    "uniform sampler2D texture_ambient1;\n"
    "uniform sampler2D texture_ambient_occlusion1;\n"
    "uniform sampler2D texture_base_color1;\n"
    "uniform sampler2D texture_diffuse1;\n"
    "uniform sampler2D texture_diffuse_roughness1;\n"
    "uniform sampler2D texture_displacement1;\n"
    "uniform sampler2D texture_emission_color1;\n"
    "uniform sampler2D texture_emissive1;\n"
    "uniform sampler2D texture_height1;\n"
    "uniform sampler2D texture_lightmap1;\n"
    "uniform sampler2D texture_normal_camera1;\n"
    "uniform sampler2D texture_normals1;\n"
    "uniform sampler2D texture_opacity1;\n"
    "uniform sampler2D texture_reflection1;\n"
    "uniform sampler2D texture_shininess1;\n"
    "uniform sampler2D texture_specular1;\n"
    "\n"
    "\n"
    "// Get Input Vars\n"
    "uniform float Time; // Time since program started in seconds\n"
    "uniform float FrameTime; // Render Time Of The Frame\n"
    "uniform int FrameNumber; // Number of the frame, counts up from zero\n"
    "uniform vec2 ViewportRes; // XY Resolution of the viewport\n"
    "\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(texture_diffuse1, TexCoords);\n"
    "}\n";


}

GUI_Window_ShaderEditor::~GUI_Window_ShaderEditor() {

    SystemUtils_->Logger_->Log("GUI ShaderEditor Window Destructor Called", 6);

}


void GUI_Window_ShaderEditor::ReloadEditorText() {

    for (int Stage = 0; Stage < ShaderStageCount_; Stage++) {
        Editors_[Stage]->SetText(ReadShaderText(GetStageAssetID(Stage)));
    }
    Editor_ = Editors_[Mode_];

}

const char* GUI_Window_ShaderEditor::GetStageName(int Stage) const {

    switch (Stage) {
        case 0:
            return "Vertex";
        case 1:
            return "Fragment";
        case 2:
            return "Geometry";
        case 3:
            return "Compute";
        case 4:
            return "Tess Control";
        case 5:
            return "Tess Eval";
        default:
            return "Unknown";
    }

}

long GUI_Window_ShaderEditor::GetStageAssetID(int Stage) const {

    const ERS_STRUCT_ShaderProgramAssetIDs& ShaderProgram = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_];
    switch (Stage) {
        case 0:
            return ShaderProgram.VertexID;
        case 1:
            return ShaderProgram.FragmentID;
        case 2:
            return ShaderProgram.GeometryID;
        case 3:
            return ShaderProgram.ComputeID;
        case 4:
            return ShaderProgram.TCID;
        case 5:
            return ShaderProgram.TEID;
        default:
            return -1;
    }

}

void GUI_Window_ShaderEditor::SetStageAssetID(int Stage, long AssetID) {

    ERS_STRUCT_ShaderProgramAssetIDs& ShaderProgram = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[SelectedShaderProgramIndex_];
    switch (Stage) {
        case 0:
            ShaderProgram.VertexID = AssetID;
            break;
        case 1:
            ShaderProgram.FragmentID = AssetID;
            break;
        case 2:
            ShaderProgram.GeometryID = AssetID;
            break;
        case 3:
            ShaderProgram.ComputeID = AssetID;
            break;
        case 4:
            ShaderProgram.TCID = AssetID;
            break;
        case 5:
            ShaderProgram.TEID = AssetID;
            break;
        default:
            break;
    }

}

std::string GUI_Window_ShaderEditor::ReadShaderText(long AssetID) {

    if (AssetID == -1) {
        return "";
    }

    std::unique_ptr<BG::ERS::IOSubsystem::IOData> Data = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, Data.get());
    if ((Data->Data == nullptr) || (Data->Size_B == 0)) {
        return "";
    }
    return std::string(reinterpret_cast<const char*>(Data->Data.get()), Data->Size_B);

}


void GUI_Window_ShaderEditor::SaveShader(std::string ShaderText, long AssetID) {

    // Write Data
    std::unique_ptr<BG::ERS::IOSubsystem::IOData> Data = std::make_unique<BG::ERS::IOSubsystem::IOData>();
    
    Data->Data.reset(new unsigned char[ShaderText.size()]);
    Data->Size_B = ShaderText.size();
    memcpy(Data->Data.get(), ShaderText.c_str(), ShaderText.size());

    // Write To Storage
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(AssetID, Data.get());


}

void GUI_Window_ShaderEditor::SaveShaderStage(int Stage) {

    std::string ShaderText = Editors_[Stage]->GetText();
    long AssetID = GetStageAssetID(Stage);
    if ((Stage > 1) && ShaderText.empty()) {
        SetStageAssetID(Stage, -1);
        return;
    }

    if (AssetID == -1) {
        AssetID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
        SetStageAssetID(Stage, AssetID);
    }

    SaveShader(ShaderText, AssetID);

}

void GUI_Window_ShaderEditor::Draw() {

    // Check Enable Change
    if (LastEnabledState_ != Enabled_) {

        // If Just Enabled
        if (Enabled_) {
            VisualRenderer_->Shaders_.push_back(std::make_unique<ERS_STRUCT_Shader>());
        } else {


            // Set Any Viewports Shaders To 0 Who Are Using This Shader
            for (int i = 0; (long)i < (long)VisualRenderer_->Viewports_.size(); i++) {
                if (VisualRenderer_->Viewports_[i]->ShaderIndex == (int)(VisualRenderer_->Shaders_.size() - 1)) {
                    VisualRenderer_->Viewports_[i]->ShaderIndex = 0;
                }
            }

            // Remove Shader From List
            VisualRenderer_->Shaders_.erase(VisualRenderer_->Shaders_.begin() + VisualRenderer_->Shaders_.size() - 1);


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



void GUI_Window_ShaderEditor::DrawEditorWindow() {

    bool Visible = ImGui::Begin("Shader Editor", &Enabled_, ImGuiWindowFlags_MenuBar);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);

        if (Visible) {


            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {


                    // New Shader Option
                    if (ImGui::MenuItem("New")) {

                        // Create New Struct In System
                        ERS_STRUCT_ShaderProgramAssetIDs ShaderProgram;
                        ShaderProgram.Name = "New Shader Program";
                        ShaderProgram.FragmentID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        ShaderProgram.VertexID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                        ShaderProgram.ComputeID = -1;
                        ShaderProgram.GeometryID = -1;
                        ShaderProgram.TCID = -1;
                        ShaderProgram.TEID = -1;
                        ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.push_back(ShaderProgram);
                        

                        // Save To Disk, So Opening It Works
                        SaveShader(NewShaderVertexText_,   ShaderProgram.VertexID);
                        SaveShader(NewshaderFragmentText_, ShaderProgram.FragmentID);
                        SelectedShaderProgramIndex_ = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.size() - 1;
                        ReloadEditorText();

                    }

                    // Program Selector Dropdown
                    if (ImGui::BeginMenu("Open")) {

                        for (long i = 0; (long)i < (long)ProjectUtils_->ProjectManager_->Project_.ShaderPrograms.size(); i++) {

                            std::string ShaderProgramName = ProjectUtils_->ProjectManager_->Project_.ShaderPrograms[i].Name;
                            if (ImGui::MenuItem(ShaderProgramName.c_str())) {

                                // Update Index, REload
                                SelectedShaderProgramIndex_ = i;
                                ReloadEditorText();

                            }
                        }


                    ImGui::EndMenu();
                    }

                    // Save Options
                    ImGui::Separator();
                    if (ImGui::MenuItem("Save")) {
                        SaveShaderStage(Mode_);
                    }

                    if (ImGui::MenuItem("Save All")) {
                        for (int Stage = 0; Stage < ShaderStageCount_; Stage++) {
                            SaveShaderStage(Stage);
                        }
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

                    for (int Stage = 0; Stage < ShaderStageCount_; Stage++) {
                        if (ImGui::MenuItem(GetStageName(Stage), nullptr, (Mode_ == Stage))) {
                            Mode_ = Stage;
                            Editor_ = Editors_[Mode_];
                            Editor_->Render("Shader Editor");
                        }
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


void GUI_Window_ShaderEditor::DrawToolsWindow() {

    bool CompileVisible = ImGui::Begin("Compiler Log", &Enabled_);

    // Compile Shader Object
    std::string VertexText = Editors_[0]->GetText();
    std::string FragmentText = Editors_[1]->GetText();
    std::string GeometryText = Editors_[2]->GetText();
    std::string ComputeText = Editors_[3]->GetText();
    std::string TCText = Editors_[4]->GetText();
    std::string TEText = Editors_[5]->GetText();
    VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->ResetProgram();
    std::string VertexLog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileVertexShader(VertexText.c_str());
    std::string FragmentLog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileFragmentShader(FragmentText.c_str());
    std::string GeometryLog;
    std::string ComputeLog;
    std::string TCLog;
    std::string TELog;
    if (!GeometryText.empty()) {
        GeometryLog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileGeometryShader(GeometryText.c_str());
    }
    if (!ComputeText.empty()) {
        ComputeLog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileComputeShader(ComputeText.c_str());
    }
    if (!TCText.empty()) {
        TCLog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileTCShader(TCText.c_str());
    }
    if (!TEText.empty()) {
        TELog = VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CompileTEShader(TEText.c_str());
    }
    VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->CreateShaderProgram(SystemUtils_->Logger_.get(), false);
    VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->DisplayName = "Preview Shader";
    VisualRenderer_->Shaders_[VisualRenderer_->Shaders_.size() - 1]->InternalName = "Preview Shader";

    // Extract Shader Log
    std::string ShaderLog;
    if (Mode_ == 0) {
        ShaderLog = VertexLog;
    } else if (Mode_ == 1) {
        ShaderLog = FragmentLog;
    } else if (Mode_ == 2) {
        ShaderLog = GeometryLog;
    } else if (Mode_ == 3) {
        ShaderLog = ComputeLog;
    } else if (Mode_ == 4) {
        ShaderLog = TCLog;
    } else if (Mode_ == 5) {
        ShaderLog = TELog;
    }

    // Set Default Window Size
    ImGui::SetWindowSize(ImVec2(600,400), ImGuiCond_FirstUseEver);
        if (CompileVisible) {
            // Draw Log
            ImGui::BeginChild("Shader Log");
            ImGui::TextWrapped("%s", ShaderLog.c_str());
            ImGui::EndChild();
        }
     ImGui::End();

}
