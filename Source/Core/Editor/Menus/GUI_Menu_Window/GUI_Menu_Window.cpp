//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Window.h>


GUI_Menu_Window::GUI_Menu_Window(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, Cursors3D* Cursors3D, ERS_CLASS_SceneManager* SceneManager, ERS_CLASS_VisualRenderer* VisualRendererInstance) {

    SystemUtils_ = SystemUtils;
    VisualRenderer_ = VisualRendererInstance;
    ProjectUtils_ = ProjectUtils;
    SystemUtils_->Logger_->Log("Editor Setting Up Window Menu", 4);


    SystemUtils_->Logger_->Log("Initializing Editor Widgets", 5);
    GUI_Window_ObjectProperties_ = std::make_unique<GUI_Window_ObjectProperties>(Cursors3D, SceneManager, ProjectUtils_);
    GUI_Window_RenderingSettings_ = std::make_unique<GUI_Window_RenderingSettings>(SystemUtils_);
    GUI_Window_FrameLatencyGraph_ = std::make_unique<GUI_Window_FrameLatencyGraph>(SystemUtils_);
    GUI_Window_RAMGraph_ = std::make_unique<GUI_Window_RAMGraph>(SystemUtils_);


    SystemUtils_->Logger_->Log("Initializing Editor Windows", 5);
    GUI_Window_SceneTree_ = std::make_unique<GUI_Window_SceneTree>(SceneManager, SystemUtils_, ProjectUtils_, Cursors3D);
    GUI_Window_SystemLog_ = std::make_unique<GUI_Window_SystemLog>(SystemUtils_);
    GUI_Window_AssetExplorer_ = std::make_unique<GUI_Window_AssetExplorer>(SystemUtils_, ProjectUtils_);
    GUI_Window_ScriptEditor_ = std::make_unique<GUI_Window_ScriptEditor>(SystemUtils_, ProjectUtils_, VisualRenderer_);

}


GUI_Menu_Window::~GUI_Menu_Window() {

    SystemUtils_->Logger_->Log("Editor Destroying Window Menu", 4);

}


void GUI_Menu_Window::Draw() {

    // Window Menu
    if (ImGui::BeginMenu("Window")) {



        // Add Windows Menu
        if (ImGui::BeginMenu("Windows")) {

            // Add Scene Tree Editor Window
            ImGui::Checkbox("Scene Tree", &GUI_Window_SceneTree_->Enabled_);
            ImGui::Checkbox("System Log", &GUI_Window_SystemLog_->Enabled_);
            ImGui::Checkbox("Asset Explorer", &GUI_Window_AssetExplorer_->Enabled_);
            ImGui::Checkbox("Object Properties", &GUI_Window_ObjectProperties_->Enabled_);
            ImGui::Checkbox("Global Viewport Settings", &GUI_Window_RenderingSettings_->Enabled_);
                

            // Framerate Widgets
            if (ImGui::BeginMenu("Framerate")) {

                // Framerate Related Tools
                ImGui::Checkbox("Framerate Counter", &GUI_Window_FramerateCounter_.Enabled_);
                ImGui::Checkbox("Framerate Histogram", &GUI_Window_FramerateHistogram_.Enabled_);
                ImGui::Checkbox("Framerate Graph", &GUI_Window_FramerateGraph_.Enabled_);
                ImGui::Checkbox("Framerate Plot", &GUI_Window_FrameratePlot_.Enabled_);
                ImGui::Checkbox("Frame Latency Graph", &GUI_Window_FrameLatencyGraph_->Enabled_);

            ImGui::EndMenu();
            }

            // System Resource Widgets
            if (ImGui::BeginMenu("System Resources")) {

                // Framerate Related Tools
                ImGui::Checkbox("RAM", &GUI_Window_RAMGraph_->Enabled_);

            ImGui::EndMenu();
            }

      


        ImGui::EndMenu();
        }

        // Viewport Menu
        if (ImGui::BeginMenu("Viewport")) {

            // Viewport Options
            if (ImGui::MenuItem("Add Viewport")) {
                VisualRenderer_->CreateViewport();
            }

            if (ImGui::MenuItem("Remove Viewport")) {
                if (VisualRenderer_->Viewports_.size() > 0) {
                    VisualRenderer_->DeleteViewport(VisualRenderer_->Viewports_.size()-1);
                }
            }
            


        ImGui::EndMenu();
        }

        ImGui::MenuItem("Script Editor", "", &GUI_Window_ScriptEditor_->Enabled_);


    ImGui::EndMenu();
    }



    // Update Widgets
    GUI_Window_FramerateCounter_.Draw();
    GUI_Window_FramerateHistogram_.Draw();
    GUI_Window_FramerateGraph_.Draw();
    GUI_Window_FrameratePlot_.Draw();

    // Update Widgets
    GUI_Window_ObjectProperties_->Draw();
    GUI_Window_RAMGraph_->Draw();
    GUI_Window_RenderingSettings_->Draw();
    GUI_Window_FrameLatencyGraph_->Draw();

    // Update Windows
    GUI_Window_SceneTree_->Draw();
    GUI_Window_SystemLog_->Draw();
    GUI_Window_AssetExplorer_->Draw();
    GUI_Window_ScriptEditor_->Draw();


}