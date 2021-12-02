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
    if (FramerateHistory_.size() > HistoryLength_) {
        std::cout<<"Dropping Item"<<std::endl;
        FramerateHistory_.erase(FramerateHistory_.begin());
    } else {
    std::cout<<"Delta"<<HistoryLength_ - FramerateHistory_.size()<<std::endl;
    std::cout<<"CurrentSize"<<FramerateHistory_.size()<<std::endl;
        // Fill With Zeros
        int Delta = HistoryLength_ - FramerateHistory_.size();
        for (int i = 0; i < Delta; i++) {
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