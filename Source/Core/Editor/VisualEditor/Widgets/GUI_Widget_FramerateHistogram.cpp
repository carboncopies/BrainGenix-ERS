//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_FramerateHistogram.h>


// Define Draw Function
void Widget_FramerateHistogram::Draw() {

    // Push Back Current Framerate To Vector
    FramerateHistory_.push_back(ImGui::GetIO().Framerate);

    // Cap Array Length At Target Set
    if (FramerateHistory_.size() > HistoryLength_ - 1) {

        // Drop Item
        FramerateHistory_.erase(FramerateHistory_.begin());

        // If Still Longer (User Reduced Length)
        if (FramerateHistory_.size() != HistoryLength_) {
            for (int i = 0; i < FramerateHistory_.size()-HistoryLength_; i++) {
                FramerateHistory_.erase(FramerateHistory_.begin());
            }
        }
    }

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Framerate Histogram", &Enabled_);

            // Histogram
            ImGui::PlotHistogram("Framerate", (const float*)FramerateHistory_.data(), FramerateHistory_.size(), -1, NULL, -1.0f, 100.0f, ImGui::GetWindowSize());

            // Sample Counter
            ImGui::DragInt("Number Of Samples", &HistoryLength_, 1.0f, 100, 100000);

        // End System Info Window
        ImGui::End();
        

    }


}