//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Menu_Window.h>


// Constructor
GUI_Menu_Window::GUI_Menu_Window(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<Cursors3D> Cursors3D, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<VisualRenderer> VisualRendererInstance) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;
    VisualRenderer_ = VisualRendererInstance;

    // Log Initialization
    SystemUtils_->Logger_->Log("Editor Setting Up Window Menu", 4);


    // Initialize Widgets
    SystemUtils_->Logger_->Log("Initializing Editor Widgets", 5);
    Widget_ObjectProperties_ = std::make_shared<Widget_ObjectProperties>(Cursors3D);
    Widget_RenderingSettings_ = std::make_unique<Widget_RenderingSettings>(SystemUtils_);
    Widget_FrameLatencyGraph_ = std::make_unique<Widget_FrameLatencyGraph>(SystemUtils_);

    // Initialize Windows
    SystemUtils_->Logger_->Log("Initializing Editor Windows", 5);
    Window_SceneTree_ = std::make_shared<Window_SceneTree>(SceneManager);
    Window_SystemLog_ = std::make_unique<Window_SystemLog>(SystemUtils_);
    Window_AssetExplorer_ = std::make_unique<Window_AssetExplorer>(SystemUtils_);
    

}


// Destructor
GUI_Menu_Window::~GUI_Menu_Window() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Editor Destroying Window Menu", 4);

}


// Draw Function
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
            bool AddViewport = false;
            bool RemoveViewport = false;
            ImGui::Checkbox("Add Viewport", &AddViewport);
            ImGui::Checkbox("Remove Viewport", &RemoveViewport);
            
            if (AddViewport) {
                VisualRenderer_->CreateViewport("Viewport");
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