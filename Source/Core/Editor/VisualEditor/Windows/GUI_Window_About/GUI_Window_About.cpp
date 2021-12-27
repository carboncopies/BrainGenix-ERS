//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_About.h>


// Constructor
Window_About::Window_About(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

}

// Destructor
Window_About::~Window_About() {

}



// Draw Window
void Window_About::Draw() {


    if (Enabled_) {
    ImGui::Begin("About", &Enabled_);

        // Set Window Size
        ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

        // Write Text
        ImGui::Text("You're running BrainGenix-ERS. ERS (Environment Rendering System) is a part of the software suite designed to facilitate Whole Brain Emulation.");

        // Operating System Status
        ImGui::BeginChild("OS Status");
        if (!SystemUtils_->IsLinux_) {
            ImGui::TextColored(ImVec4(0.8f, 0.2f, 0.2f, 1.0f), "Some features are not available in Windows. To use all features, please use Linux/BSD.");
        } else {
            ImGui::Text("All features are enabled. Congrats on using Open Source Software!");
        }
        ImGui::EndChild();

        // License Info
        ImGui::BeginChild("License");
        ImGui::Text("This program is free software: you can redistribute it and/or modify"
                    "it under the terms of the GNU Affero General Public License as"
                    "published by the Free Software Foundation, either version 3 of the"
                    "License, or (at your option) any later version."

                    "This program is distributed in the hope that it will be useful,"
                    "but WITHOUT ANY WARRANTY; without even the implied warranty of"
                    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
                    "GNU Affero General Public License for more details."

                    "You should have received a copy of the GNU Affero General Public License"
                    "along with this program.  If not, see <https://www.gnu.org/licenses/>.");
        ImGui::EndChild();



    ImGui::End();
    }


}