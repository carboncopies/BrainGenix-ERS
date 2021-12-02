//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_FrameratePlot.h>


// Define Draw Function
void Widget_FrameratePlot::Draw() {

    // Push Back Current Framerate To Vector
    FramerateHistory_.push_back(ImGui::GetIO().Framerate);
    


    // Cap Array Length At Target Set
    if (FramerateHistory_.size() > HistoryLength_) {
        FramerateHistory_.erase(FramerateHistory_.begin());
    } else {

        // Fill With Zeros
        int Delta = HistoryLength_ - FramerateHistory_.size();
        for (int i = 0; i < Delta; i++) {
            FramerateHistory_.push_back(0.0f);
        }

    }

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Framerate Plot", &Enabled_);

            // Get Window Size (To Size Graph)
            ImVec2 WindowSize = ImGui::GetContentRegionAvail();
            ImVec2 GraphSize = ImVec2(WindowSize.x, WindowSize.y);

            // Plot
            ImGui::PlotLines("Framerate", (const float*)FramerateHistory_.data(), FramerateHistory_.size(), -1, NULL, -1.0f, 100.0f, GraphSize);

        // End System Info Window
        ImGui::End();
        

    }


}