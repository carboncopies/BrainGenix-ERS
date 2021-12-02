//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_RenderingSettings.h>


// Define Draw Function
void Widget_RenderingSettings::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("System Controls", &Enabled_);


            // Wireframe Rendering Mode
            static bool OpenGLDrawLines = false;
            ImGui::Checkbox("Wireframe Rendering Mode", &OpenGLDrawLines);
            ImGui::NewLine();
            if (OpenGLDrawLines) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }


            // Rendering Background Clear Color
            static ImVec4 ClearColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
            ImGui::ColorEdit4("Background Clear Color", (float*)&ClearColor);
            ImGui::NewLine();
            glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);



        // End System Controls Window
        ImGui::End();

    }


}