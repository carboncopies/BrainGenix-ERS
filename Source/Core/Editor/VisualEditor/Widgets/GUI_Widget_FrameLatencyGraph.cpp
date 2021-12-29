//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-28
*/

#include <GUI_Widget_FrameLatencyGraph.h>


// Constructor
Widget_FrameLatencyGraph::Widget_FrameLatencyGraph(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {
    
    // Copy Pointer
    SystemUtils_ = SystemUtils;

}

// Destructor
Widget_FrameLatencyGraph::~Widget_FrameLatencyGraph() {

}

// Define Draw Function
void Widget_FrameLatencyGraph::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Frame Latency Graph", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(300,250), ImGuiCond_FirstUseEver);

            // Get Window Size (To Size Graph)
            ImVec2 WindowSize = ImGui::GetContentRegionAvail();
            ImVec2 GraphSize = ImVec2(WindowSize.x, WindowSize.y);

            // Graph
            if (!ImGui::IsWindowCollapsed()) {
                ImPlot::SetNextAxesToFit();
                ImPlot::BeginPlot("Framerate Graph", GraphSize);
                ImPlot::PlotLine("Framerate", (const float*)SystemUtils_->FramerateManager_->ActualFrameTimes_.data(), SystemUtils_->FramerateManager_->ActualFrameTimes_.size());
                ImPlot::EndPlot();
            }

        // End System Info Window
        ImGui::End();
        

    }


}