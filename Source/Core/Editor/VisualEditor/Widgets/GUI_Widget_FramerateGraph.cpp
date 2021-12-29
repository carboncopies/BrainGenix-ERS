//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_FramerateGraph.h>


// Define Draw Function
void Widget_FramerateGraph::Draw() {

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
        ImGui::Begin("Framerate Graph", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(300,250), ImGuiCond_FirstUseEver);

            // Get Window Size (To Size Graph)
            ImVec2 WindowSize = ImGui::GetContentRegionAvail();
            ImVec2 GraphSize = ImVec2(WindowSize.x, WindowSize.y);

            // Graph
            if (ImGui::IsWindowDocked() {
                ImPlot::SetNextAxesToFit();
                ImPlot::BeginPlot("Framerate Graph", GraphSize);
                ImPlot::PlotLine("Framerate", (const float*)FramerateHistory_.data(), FramerateHistory_.size());
                ImPlot::EndPlot();
            }

        // End System Info Window
        ImGui::End();
        

    }


}