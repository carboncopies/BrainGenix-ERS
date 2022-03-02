//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Window.h>


GUI_Menu_Window::GUI_Menu_Window(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, std::shared_ptr<Cursors3D> Cursors3D, ERS_CLASS_SceneManager* SceneManager, std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRendererInstance) {

    SystemUtils_ = SystemUtils;
    VisualRenderer_ = VisualRendererInstance;
    ProjectUtils_ = ProjectUtils;
    SystemUtils_->Logger_->Log("Editor Setting Up Window Menu", 4);


    SystemUtils_->Logger_->Log("Initializing Editor Widgets", 5);
    Widget_ObjectProperties_ = std::make_unique<Widget_ObjectProperties>(Cursors3D);
    Widget_RenderingSettings_ = std::make_unique<Widget_RenderingSettings>(SystemUtils_);
    Widget_FrameLatencyGraph_ = std::make_unique<Widget_FrameLatencyGraph>(SystemUtils_);


    SystemUtils_->Logger_->Log("Initializing Editor Windows", 5);
    Window_SceneTree_ = std::make_unique<Window_SceneTree>(SceneManager, SystemUtils_, ProjectUtils_);
    Window_SystemLog_ = std::make_unique<Window_SystemLog>(SystemUtils_);
    Window_AssetExplorer_ = std::make_unique<Window_AssetExplorer>(SystemUtils_);
    

}


GUI_Menu_Window::~GUI_Menu_Window() {

    SystemUtils_->Logger_->Log("Editor Destroying Window Menu", 4);

}


void GUI_Menu_Window::Draw() {

    // Window Menu
    if (ImGui::BeginMenu("Window")) {

        // Add Widgets Menu
        if (ImGui::BeginMenu("Widgets")) {

            // Framerate Widgets
            if (ImGui::BeginMenu("Framerate")) {

                // Framerate Related Tools
                ImGui::Checkbox("Framerate Counter", &Widget_FramerateCounter_.Enabled_);
                ImGui::Checkbox("Framerate Histogram", &Widget_FramerateHistogram_.Enabled_);
                ImGui::Checkbox("Framerate Graph", &Widget_FramerateGraph_.Enabled_);
                ImGui::Checkbox("Framerate Plot", &Widget_FrameratePlot_.Enabled_);
                ImGui::Checkbox("Frame Latency Graph", &Widget_FrameLatencyGraph_->Enabled_);

            ImGui::EndMenu();
            }

            // Viewport Widgets
            if (ImGui::BeginMenu("Viewport")) {

                // Viewport Settings
                ImGui::Checkbox("Object Properties", &Widget_ObjectProperties_->Enabled_);
                ImGui::Checkbox("Global Viewport Settings", &Widget_RenderingSettings_->Enabled_);
                

            ImGui::EndMenu();
            }


        ImGui::EndMenu();
        }

        // Add Windows Menu
        if (ImGui::BeginMenu("Windows")) {

            // Add Scene Tree Editor Window
            ImGui::Checkbox("Scene Tree", &Window_SceneTree_->Enabled_);
            ImGui::Checkbox("System Log", &Window_SystemLog_->Enabled_);
            ImGui::Checkbox("Asset Explorer", &Window_AssetExplorer_->Enabled_);
            

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


    ImGui::EndMenu();
    }



    // Update Widgets
    Widget_FramerateCounter_.Draw();
    Widget_FramerateHistogram_.Draw();
    Widget_FramerateGraph_.Draw();
    Widget_FrameratePlot_.Draw();
    Widget_ObjectProperties_->Draw();

    // Update Widgets
    Widget_RenderingSettings_->Draw();
    Widget_FrameLatencyGraph_->Draw();

    // Update Windows
    Window_SceneTree_->Draw();
    Window_SystemLog_->Draw();
    Window_AssetExplorer_->Draw();


}