//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ViewportMenu.h>


ERS_CLASS_ViewportMenu::ERS_CLASS_ViewportMenu(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, double* GameStartTime, bool* IsEditorMode, std::map<int, std::shared_ptr<ERS_STRUCT_Shader>>* Shaders) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    GameStartTime_ = GameStartTime;
    IsEditorMode_ = IsEditorMode;
    Shaders_ = Shaders;

    SystemUtils_->Logger_->Log("Initializing Viewport Menu Subsystem", 5);

}


ERS_CLASS_ViewportMenu::~ERS_CLASS_ViewportMenu() {

    SystemUtils_->Logger_->Log("Viewport Menu Subsystem Destructor Invoked", 6);

}


void ERS_CLASS_ViewportMenu::DrawMenu(ERS_STRUCT_Viewport* Viewport) {


    // Menu Bar
    if (ImGui::BeginMenuBar()) {


        // Viewport Cube Controls
        if (ImGui::BeginMenu("Controls")) {

            // Draw Controls
            ImGui::MenuItem("Scene Info Overlay", nullptr, &Viewport->ShowSceneInfo_);
            ImGui::MenuItem("System Resources Overlay", nullptr, &Viewport->ShowResourceInfo_);
            ImGui::MenuItem("Loading Time Overlay", nullptr, &Viewport->ShowLoadingTimeInfo_);

            ImGui::Separator();

            ImGui::MenuItem("Rotation Indicator", nullptr, &Viewport->ShowCube);
            ImGui::MenuItem("Gizmo", nullptr, &Viewport->GizmoEnabled);
            ImGui::MenuItem("Grid", nullptr, &Viewport->GridEnabled);
            ImGui::MenuItem("Light Icons", nullptr, &Viewport->LightIcons);

            ImGui::Separator();

            ImGui::MenuItem("Gamma Correction", nullptr, &Viewport->GammaCorrection);
            ImGui::MenuItem("HDR", nullptr, &Viewport->HDREnabled_);


        ImGui::EndMenu();
        }


        // Shader Control Menu
        if(ImGui::BeginMenu("Shader")) {

            // Draw Selectable Menu Showing Active Viewport Shader
            for (int i = 0; (long)i < (long)Shaders_->size(); i++) {

                if (strcmp((*Shaders_)[i]->DisplayName.substr(0, 1).c_str(), "_")) {
                    if (ImGui::Selectable((*Shaders_)[i]->DisplayName.c_str(), i == Viewport->ShaderIndex)) {
                        Viewport->ShaderIndex = i;
                    }
                }

            }

        ImGui::EndMenu();
        }

        // Grid Control Menu
        if (ImGui::BeginMenu("Grid")) {

            // Grid Scale Submenu
            if (ImGui::BeginMenu("Scale")) {

                if (ImGui::MenuItem("0.0625 Units", nullptr, (Viewport->Grid->GridSize_ == 0.00125f))) {
                    Viewport->Grid->GridSize_ = 0.00125f;
                }

                if (ImGui::MenuItem("0.125 Units", nullptr, (Viewport->Grid->GridSize_ == 0.0025f))) {
                    Viewport->Grid->GridSize_ = 0.0025f;
                }

                if (ImGui::MenuItem("0.25 Units", nullptr, (Viewport->Grid->GridSize_ == 0.005f))) {
                    Viewport->Grid->GridSize_ = 0.005f;
                }

                if (ImGui::MenuItem("0.5 Units", nullptr, (Viewport->Grid->GridSize_ == 0.01f))) {
                    Viewport->Grid->GridSize_ = 0.01f;
                }

                if (ImGui::MenuItem("1 Unit", nullptr, (Viewport->Grid->GridSize_ == 0.02f))) {
                    Viewport->Grid->GridSize_ = 0.02f;
                }

                if (ImGui::MenuItem("2.5 Units", nullptr, (Viewport->Grid->GridSize_ == 0.05f))) {
                    Viewport->Grid->GridSize_ = 0.05f;
                }

                if (ImGui::MenuItem("5 Units", nullptr, (Viewport->Grid->GridSize_ == 0.1f))) {
                    Viewport->Grid->GridSize_ = 0.1f;
                }
                
            ImGui::EndMenu();
            }

            // Line Thickness Submenu
            if (ImGui::BeginMenu("Line Thickness")) {

                if (ImGui::MenuItem("0.5%", nullptr, (Viewport->Grid->GridLineThickness_ == 0.005f))) {
                    Viewport->Grid->GridLineThickness_ = 0.005f;
                }

                if (ImGui::MenuItem("1%", nullptr, (Viewport->Grid->GridLineThickness_ == 0.01f))) {
                    Viewport->Grid->GridLineThickness_ = 0.01f;
                }

                if (ImGui::MenuItem("2%", nullptr, (Viewport->Grid->GridLineThickness_ == 0.02f))) {
                    Viewport->Grid->GridLineThickness_ = 0.02f;
                }

                if (ImGui::MenuItem("3%", nullptr, (Viewport->Grid->GridLineThickness_ == 0.03f))) {
                    Viewport->Grid->GridLineThickness_ = 0.03f;
                }

                if (ImGui::MenuItem("4%", nullptr, (Viewport->Grid->GridLineThickness_ == 0.04f))) {
                    Viewport->Grid->GridLineThickness_ = 0.04f;
                }
                
            ImGui::EndMenu();
            }

            // Color Scheme
            if (ImGui::BeginMenu("Colors")) {

                // Base Color
                if (ImGui::BeginMenu("Base")) {


                    if (ImGui::MenuItem("White")) {
                        Viewport->Grid->GridColor_ = glm::vec3(1.0f);
                    }

                    if (ImGui::MenuItem("Light Grey")) {
                        Viewport->Grid->GridColor_ = glm::vec3(0.75f);
                    }

                    if (ImGui::MenuItem("Grey")) {
                        Viewport->Grid->GridColor_ = glm::vec3(0.5f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewport->Grid->GridColor_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewport->Grid->GridColor_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewport->Grid->GridColor_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }

                // X Axis Color
                if (ImGui::BeginMenu("X Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewport->Grid->GridColorX_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }


                // Z Axis Color
                if (ImGui::BeginMenu("Z Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewport->Grid->GridColorZ_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }


            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }


        // Add Items Menu
        if (ImGui::BeginMenu("Add")) {

            if (ImGui::BeginMenu("Light")) {

                if (ImGui::MenuItem("Point Light")) {
                    ProjectUtils_->SceneManager_->AddPointLight();
                }

                if (ImGui::MenuItem("Spot Light")) {
                    ProjectUtils_->SceneManager_->AddSpotLight();
                }

                if (ImGui::MenuItem("Directional Light")) {
                    ProjectUtils_->SceneManager_->AddDirectionalLight();
                }

            ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Script")) {
                
                ERS_STRUCT_Script NewScript;
                NewScript.AssetID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
                NewScript.Code_ = "# ERS Script\n";
                NewScript.Name_ = "Untitled Script";
                ProjectUtils_->ProjectManager_->Project_.Scripts.push_back(NewScript);
            
            }


        ImGui::EndMenu();
        }


        // Grid Snapping Control Menu
        if (ImGui::BeginMenu("Grid Snapping")) {

            if (ImGui::BeginMenu("Translation")) {

                if (ImGui::MenuItem("Disabled", nullptr, (Viewport->GridSnapAmountTranslate_ == 0.0f))) {
                    Viewport->GridSnapAmountTranslate_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("0.1", nullptr, (Viewport->GridSnapAmountTranslate_ == 0.1f))) {
                    Viewport->GridSnapAmountTranslate_ = 0.1f;
                }
                if (ImGui::MenuItem("0.25", nullptr, (Viewport->GridSnapAmountTranslate_ == 0.25f))) {
                    Viewport->GridSnapAmountTranslate_ = 0.25f;
                }
                if (ImGui::MenuItem("0.5", nullptr, (Viewport->GridSnapAmountTranslate_ == 0.5f))) {
                    Viewport->GridSnapAmountTranslate_ = 0.5f;
                }
                if (ImGui::MenuItem("0.75", nullptr, (Viewport->GridSnapAmountTranslate_ == 0.75f))) {
                    Viewport->GridSnapAmountTranslate_ = 0.75f;
                }
                if (ImGui::MenuItem("1.0", nullptr, (Viewport->GridSnapAmountTranslate_ == 1.0f))) {
                    Viewport->GridSnapAmountTranslate_ = 1.0f;
                }

            ImGui::EndMenu();
            }


            if (ImGui::BeginMenu("Rotate")) {

                if (ImGui::MenuItem("Disabled", nullptr, (Viewport->GridSnapAmountRotate_ == 0.0f))) {
                    Viewport->GridSnapAmountRotate_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("1", nullptr, (Viewport->GridSnapAmountRotate_ == 1.0f))) {
                    Viewport->GridSnapAmountRotate_ = 1.0f;
                }
                if (ImGui::MenuItem("5", nullptr, (Viewport->GridSnapAmountRotate_ == 5.0f))) {
                    Viewport->GridSnapAmountRotate_ = 5.0f;
                }
                if (ImGui::MenuItem("10", nullptr, (Viewport->GridSnapAmountRotate_ == 10.0f))) {
                    Viewport->GridSnapAmountRotate_ = 10.0f;
                }
                if (ImGui::MenuItem("25", nullptr, (Viewport->GridSnapAmountRotate_ == 25.0f))) {
                    Viewport->GridSnapAmountRotate_ = 25.0f;
                }
                if (ImGui::MenuItem("45", nullptr, (Viewport->GridSnapAmountRotate_ == 45.0f))) {
                    Viewport->GridSnapAmountRotate_ = 45.0f;
                }
                if (ImGui::MenuItem("90", nullptr, (Viewport->GridSnapAmountRotate_ == 90.0f))) {
                    Viewport->GridSnapAmountRotate_ = 90.0f;
                }

            ImGui::EndMenu();
            }



            if (ImGui::BeginMenu("Scale")) {

                if (ImGui::MenuItem("Disabled", nullptr, (Viewport->GridSnapAmountScale_ == 0.0f))) {
                    Viewport->GridSnapAmountScale_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("0.1", nullptr, (Viewport->GridSnapAmountScale_ == 0.1f))) {
                    Viewport->GridSnapAmountScale_ = 0.1f;
                }
                if (ImGui::MenuItem("0.25", nullptr, (Viewport->GridSnapAmountScale_ == 0.25f))) {
                    Viewport->GridSnapAmountScale_ = 0.25f;
                }
                if (ImGui::MenuItem("0.5", nullptr, (Viewport->GridSnapAmountScale_ == 0.5f))) {
                    Viewport->GridSnapAmountScale_ = 0.5f;
                }
                if (ImGui::MenuItem("0.75", nullptr, (Viewport->GridSnapAmountScale_ == 0.75f))) {
                    Viewport->GridSnapAmountScale_ = 0.75f;
                }
                if (ImGui::MenuItem("1.0", nullptr, (Viewport->GridSnapAmountScale_ == 1.0f))) {
                    Viewport->GridSnapAmountScale_ = 1.0f;
                }

            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }

        // Game Control Menu
        if (ImGui::BeginMenu("Run")) {

            // Run Option
            if (ImGui::MenuItem("Run With Editor", "F5")) {
                *IsEditorMode_ = false;
                *GameStartTime_ = glfwGetTime();
            }

            // Stop Option
            if (ImGui::MenuItem("Stop", "Escape")) {
                *IsEditorMode_ = !IsEditorMode_;
            }

        ImGui::EndMenu();
        }

    ImGui::EndMenuBar();
    }


    // Keybinds
    if (ImGui::IsKeyPressed(GLFW_KEY_F5)) {
        *IsEditorMode_ = false;
        *GameStartTime_ = glfwGetTime();
    }
    if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        *IsEditorMode_ = true;
    }


}