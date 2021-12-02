//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_FramerateCounter.h>


// Define Draw Function
void Widget_FramerateCounter::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Framerate Counter", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,150), ImGuiCond_FirstUseEver);

            // FPS Counter
            ImGui::Text("System Framerate %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        // End System Info Window
        ImGui::End();
        

    }


}