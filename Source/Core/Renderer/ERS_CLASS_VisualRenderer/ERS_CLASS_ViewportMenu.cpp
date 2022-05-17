//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ViewportMenu.h>


ERS_CLASS_ViewportMenu::ERS_CLASS_ViewportMenu(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

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
            ImGui::MenuItem("Scene Info Overlay", nullptr, &Viewports_[Index]->ShowSceneInfo_);
            ImGui::MenuItem("System Resources Overlay", nullptr, &Viewports_[Index]->ShowResourceInfo_);
            ImGui::MenuItem("Loading Time Overlay", nullptr, &Viewports_[Index]->ShowLoadingTimeInfo_);

            ImGui::Separator();

            ImGui::MenuItem("Rotation Indicator", nullptr, &Viewports_[Index]->ShowCube);
            ImGui::MenuItem("Gizmo", nullptr, &Viewports_[Index]->GizmoEnabled);
            ImGui::MenuItem("Grid", nullptr, &Viewports_[Index]->GridEnabled);
            ImGui::MenuItem("Light Icons", nullptr, &Viewports_[Index]->LightIcons);

            ImGui::Separator();

            ImGui::MenuItem("Gamma Correction", nullptr, &Viewports_[Index]->GammaCorrection);
            ImGui::MenuItem("HDR", nullptr, &Viewports_[Index]->HDREnabled_);


        ImGui::EndMenu();
        }


        // Shader Control Menu
        if(ImGui::BeginMenu("Shader")) {

            // Draw Selectable Menu Showing Active Viewport Shader
            for (int i = 0; (long)i < (long)Shaders_.size(); i++) {

                if (strcmp(Shaders_[i]->DisplayName.substr(0, 1).c_str(), "_")) {
                    if (ImGui::Selectable(Shaders_[i]->DisplayName.c_str(), i == Viewports_[Index]->ShaderIndex)) {
                        Viewports_[Index]->ShaderIndex = i;
                    }
                }

            }

        ImGui::EndMenu();
        }

        // Grid Control Menu
        if (ImGui::BeginMenu("Grid")) {

            // Grid Scale Submenu
            if (ImGui::BeginMenu("Scale")) {

                if (ImGui::MenuItem("0.0625 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.00125f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.00125f;
                }

                if (ImGui::MenuItem("0.125 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.0025f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.0025f;
                }

                if (ImGui::MenuItem("0.25 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.005f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.005f;
                }

                if (ImGui::MenuItem("0.5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.01f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.01f;
                }

                if (ImGui::MenuItem("1 Unit", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.02f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.02f;
                }

                if (ImGui::MenuItem("2.5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.05f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.05f;
                }

                if (ImGui::MenuItem("5 Units", nullptr, (Viewports_[Index]->Grid->GridSize_ == 0.1f))) {
                    Viewports_[Index]->Grid->GridSize_ = 0.1f;
                }
                
            ImGui::EndMenu();
            }

            // Line Thickness Submenu
            if (ImGui::BeginMenu("Line Thickness")) {

                if (ImGui::MenuItem("0.5%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.005f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.005f;
                }

                if (ImGui::MenuItem("1%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.01f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.01f;
                }

                if (ImGui::MenuItem("2%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.02f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.02f;
                }

                if (ImGui::MenuItem("3%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.03f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.03f;
                }

                if (ImGui::MenuItem("4%", nullptr, (Viewports_[Index]->Grid->GridLineThickness_ == 0.04f))) {
                    Viewports_[Index]->Grid->GridLineThickness_ = 0.04f;
                }
                
            ImGui::EndMenu();
            }

            // Color Scheme
            if (ImGui::BeginMenu("Colors")) {

                // Base Color
                if (ImGui::BeginMenu("Base")) {


                    if (ImGui::MenuItem("White")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(1.0f);
                    }

                    if (ImGui::MenuItem("Light Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.75f);
                    }

                    if (ImGui::MenuItem("Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.5f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColor_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }

                // X Axis Color
                if (ImGui::BeginMenu("X Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColorX_ = glm::vec3(0.0f);
                    }

                ImGui::EndMenu();
                }


                // Z Axis Color
                if (ImGui::BeginMenu("Z Axis")) {


                    if (ImGui::MenuItem("Red")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(1.0f, 0.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Green")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f, 1.0f, 0.0f);
                    }

                    if (ImGui::MenuItem("Blue")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f, 0.0f, 1.0f);
                    }

                    if (ImGui::MenuItem("Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.25f);
                    }

                    if (ImGui::MenuItem("Very Dark Grey")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.1f);
                    }

                    if (ImGui::MenuItem("Black")) {
                        Viewports_[Index]->Grid->GridColorZ_ = glm::vec3(0.0f);
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
                    SceneManager->AddPointLight();
                }

                if (ImGui::MenuItem("Spot Light")) {
                    SceneManager->AddSpotLight();
                }

                if (ImGui::MenuItem("Directional Light")) {
                    SceneManager->AddDirectionalLight();
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

                if (ImGui::MenuItem("Disabled", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 0.0f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("0.1", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 0.1f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 0.1f;
                }
                if (ImGui::MenuItem("0.25", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 0.25f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 0.25f;
                }
                if (ImGui::MenuItem("0.5", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 0.5f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 0.5f;
                }
                if (ImGui::MenuItem("0.75", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 0.75f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 0.75f;
                }
                if (ImGui::MenuItem("1.0", nullptr, (Viewports_[Index]->GridSnapAmountTranslate_ == 1.0f))) {
                    Viewports_[Index]->GridSnapAmountTranslate_ = 1.0f;
                }

            ImGui::EndMenu();
            }


            if (ImGui::BeginMenu("Rotate")) {

                if (ImGui::MenuItem("Disabled", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 0.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("1", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 1.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 1.0f;
                }
                if (ImGui::MenuItem("5", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 5.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 5.0f;
                }
                if (ImGui::MenuItem("10", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 10.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 10.0f;
                }
                if (ImGui::MenuItem("25", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 25.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 25.0f;
                }
                if (ImGui::MenuItem("45", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 45.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 45.0f;
                }
                if (ImGui::MenuItem("90", nullptr, (Viewports_[Index]->GridSnapAmountRotate_ == 90.0f))) {
                    Viewports_[Index]->GridSnapAmountRotate_ = 90.0f;
                }

            ImGui::EndMenu();
            }



            if (ImGui::BeginMenu("Scale")) {

                if (ImGui::MenuItem("Disabled", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 0.0f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 0.0f;
                }

                ImGui::Separator();
                
                if (ImGui::MenuItem("0.1", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 0.1f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 0.1f;
                }
                if (ImGui::MenuItem("0.25", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 0.25f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 0.25f;
                }
                if (ImGui::MenuItem("0.5", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 0.5f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 0.5f;
                }
                if (ImGui::MenuItem("0.75", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 0.75f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 0.75f;
                }
                if (ImGui::MenuItem("1.0", nullptr, (Viewports_[Index]->GridSnapAmountScale_ == 1.0f))) {
                    Viewports_[Index]->GridSnapAmountScale_ = 1.0f;
                }

            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }

        // Game Control Menu
        if (ImGui::BeginMenu("Run")) {

            // Run Option
            if (ImGui::MenuItem("Run With Editor", "F5")) {
                IsEditorMode_ = false;
                GameStartTime_ = glfwGetTime();
            }

            // Stop Option
            if (ImGui::MenuItem("Stop", "Escape")) {
                IsEditorMode_ = !IsEditorMode_;
            }

        ImGui::EndMenu();
        }

    ImGui::EndMenuBar();
    }


    // Keybinds
    if (ImGui::IsKeyPressed(GLFW_KEY_F5)) {
        IsEditorMode_ = false;
        GameStartTime_ = glfwGetTime();
    }
    if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        IsEditorMode_ = true;
    }


}