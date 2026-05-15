//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Window.h>
#include <EditorLocalization.h>

namespace Localization = ERS::Editor::Localization;

GUI_Menu_Window::GUI_Menu_Window(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_Windows* Windows,  ERS_CLASS_VisualRenderer* VisualRendererInstance) {

    SystemUtils_ = SystemUtils;
    VisualRenderer_ = VisualRendererInstance;
    Windows_ = Windows;
    SystemUtils_->Logger_->Log("Editor Setting Up Window Menu", 4);

}


GUI_Menu_Window::~GUI_Menu_Window() {

    SystemUtils_->Logger_->Log("Editor Destroying Window Menu", 4);

}


void GUI_Menu_Window::Draw() {

    // Window Menu
    if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Window))) {



        // Add Windows Menu
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Windows))) {

            // Add Scene Tree Editor Window
            ImGui::MenuItem(Localization::Get(Localization::TextID::SceneTree), "", &Windows_->GUI_Window_SceneTree_->Enabled_);
            ImGui::MenuItem(Localization::Get(Localization::TextID::SystemLog), "", &Windows_->GUI_Window_SystemLog_->Enabled_);
            ImGui::MenuItem(Localization::Get(Localization::TextID::AssetExplorer), "", &Windows_->GUI_Window_AssetExplorer_->Enabled_);
            ImGui::MenuItem(Localization::Get(Localization::TextID::ObjectProperties), "", &Windows_->GUI_Window_ObjectProperties_->Enabled_);

            // Framerate Widgets
            if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Framerate))) {

                // Framerate Related Tools
                ImGui::MenuItem(Localization::Get(Localization::TextID::FramerateCounter), "", &Windows_->GUI_Window_FramerateCounter_->Enabled_);
                ImGui::MenuItem(Localization::Get(Localization::TextID::FramerateHistogram), "", &Windows_->GUI_Window_FramerateHistogram_->Enabled_);
                ImGui::MenuItem(Localization::Get(Localization::TextID::FramerateGraph), "", &Windows_->GUI_Window_FramerateGraph_->Enabled_);
                ImGui::MenuItem(Localization::Get(Localization::TextID::FrameratePlot), "", &Windows_->GUI_Window_FrameratePlot_->Enabled_);
                ImGui::MenuItem(Localization::Get(Localization::TextID::FrameLatencyGraph), "", &Windows_->GUI_Window_FrameLatencyGraph_->Enabled_);

            ImGui::EndMenu();
            }

            // System Resource Widgets
            if (ImGui::BeginMenu(Localization::Get(Localization::TextID::SystemResources))) {

                // Framerate Related Tools
                ImGui::MenuItem(Localization::Get(Localization::TextID::RAM), "", &Windows_->GUI_Window_RAMGraph_->Enabled_);

            ImGui::EndMenu();
            }

      


        ImGui::EndMenu();
        }

        // Viewport Menu
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Viewport))) {

            // Viewport Options
            if (ImGui::MenuItem(Localization::Get(Localization::TextID::AddViewport))) {
                VisualRenderer_->CreateViewport();
            }

            if (ImGui::MenuItem(Localization::Get(Localization::TextID::RemoveViewport))) {
                if (VisualRenderer_->Viewports_.size() > 0) {
                    VisualRenderer_->DeleteViewport(VisualRenderer_->Viewports_.size()-1);
                }
            }
            


        ImGui::EndMenu();
        }

        ImGui::MenuItem(Localization::Get(Localization::TextID::ScriptEditor), "", &Windows_->GUI_Window_ScriptEditor_->Enabled_);
        ImGui::MenuItem(Localization::Get(Localization::TextID::ShaderEditor), "", &Windows_->GUI_Window_ShaderEditor_->Enabled_);


    ImGui::EndMenu();
    }


}
