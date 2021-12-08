//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_ObjectProperties.h>


// Define Draw Function
void Widget_ObjectProperties::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Rendering Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);

            // Wireframe Rendering Mode
            ImGui::Checkbox("Wireframe Rendering Mode", &OpenGLDrawLines_);
            ImGui::NewLine();


            // Rendering Background Clear Color
            ImGui::ColorEdit4("Background Clear Color", (float*)&ClearColor_);
            ImGui::NewLine();



        // End System Controls Window
        ImGui::End();

    }

    // Update OpenGL Settings
    if (OpenGLDrawLines_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glClearColor(ClearColor_.x, ClearColor_.y, ClearColor_.z, ClearColor_.w);


}