//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_SystemLog.h>


// Constructor
Window_SystemLog::Window_SystemLog(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI_Window_SystemLog", 5);

}

// Destructor
Window_SystemLog::~Window_SystemLog() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI_Window_SystemLog Destructor Called", 6);


}


// Draw Window
void Window_SystemLog::Draw() {

    if (Enabled_) {
    ImGui::Begin("System Log", &Enabled_);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);

        
        // Min Log Level Slider
        ImGui::SliderInt("Minimum Log Level", &MinLogLevel_, 0, 10);
        ImGui::SameLine();

        // Autoscroll
        ImGui::Checkbox("Lock To Bottom", &AutoScroll_);


        // Clear Button
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            SystemUtils_->Logger_->LogColors_.erase(SystemUtils_->Logger_->LogColors_.begin(), SystemUtils_->Logger_->LogColors_.end());
            SystemUtils_->Logger_->LogMessages_ = std::vector<std::string>();
            SystemUtils_->Logger_->FullLogMessages_ = std::vector<std::string>();
            SystemUtils_->Logger_->LogLevels_ = std::vector<int>();
            SystemUtils_->Logger_->LogTimes_ = std::vector<std::string>();

        }        
        ImGui::Separator();

        // Draw Log Textbox
        ImGui::BeginChild("Log Text", ImVec2(0,0), true, ImGuiWindowFlags_HorizontalScrollbar);
        for (int i = 0; i < SystemUtils_->Logger_->LogMessages_.size(); i++) {

            // Check Log Level
            if (SystemUtils_->Logger_->LogLevels_[i] > MinLogLevel_) {

                float ColorRed = SystemUtils_->Logger_->LogColors_[i].Red / 255.0f;
                float ColorGreen = SystemUtils_->Logger_->LogColors_[i].Green / 255.0f;
                float ColorBlue = SystemUtils_->Logger_->LogColors_[i].Blue / 255.0f;


                std::string LogText = SystemUtils_->Logger_->FullLogMessages_[i];
                ImVec4 TextColor = ImVec4(ColorRed, ColorGreen, ColorBlue, 1.0f);
                ImGui::TextColored(TextColor, "%s", LogText.c_str());

            }

        }
        // Scroll To Bottom If Enabled
        if (AutoScroll_) {
            ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();


    ImGui::End();
    }


}