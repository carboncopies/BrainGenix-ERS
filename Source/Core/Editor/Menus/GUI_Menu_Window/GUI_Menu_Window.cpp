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
    Window_SceneTree_ = std::make_unique<Window_SceneTree>(SceneManager, SystemUtils_, ProjectUtils_, Cursors3D);
    Window_SystemLog_ = std::make_unique<Window_SystemLog>(SystemUtils_);
    Window_AssetExplorer_ = std::make_unique<Window_AssetExplorer>(SystemUtils_, ProjectUtils_);
    Window_ScriptEditor_ = std::make_unique<Window_ScriptEditor>(SystemUtils_, ProjectUtils_, VisualRenderer_);

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

        ImGui::MenuItem("Script Editor", "", &Window_ScriptEditor_->Enabled_);


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
    Window_SceneTree_->Draw();
    Window_SystemLog_->Draw();
    Window_AssetExplorer_->Draw();
    Window_ScriptEditor_->Draw();


}