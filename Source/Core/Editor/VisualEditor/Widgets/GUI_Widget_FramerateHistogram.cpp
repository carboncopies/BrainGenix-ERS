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
    
    std::cout<<"Delta"<<HistoryLength_ - FramerateHistory_.size()<<std::endl;
    std::cout<<"CurrentSize"<<FramerateHistory_.size()<<std::endl;

    // Cap Array Length At Target Set
    if (FramerateHistory_.size() > HistoryLength_) {
        FramerateHistory_.erase(FramerateHistory_.begin());
    } else {

        // Fill With Zeros
        for (signed int i = 0; i < HistoryLength_ - FramerateHistory_.size(); i++) {
            FramerateHistory_.push_back(0.0f);
        }

        std::cout<<"UpdateSize"<<FramerateHistory_.size()<<std::endl;

    }

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Framerate Histogram", &Enabled_);

            // Get Window Size (To Size Graph)
            ImVec2 WindowSize = ImGui::GetContentRegionAvail();
            ImVec2 GraphSize = ImVec2(WindowSize.x, WindowSize.y);

            // Histogram
            ImGui::PlotHistogram("Framerate", (const float*)FramerateHistory_.data(), FramerateHistory_.size(), -1, NULL, -1.0f, 100.0f, GraphSize);


        // End System Info Window
        ImGui::End();
        

    }


}