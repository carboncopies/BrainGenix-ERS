//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Widget_RAMGraph.h>


Widget_RAMGraph::Widget_RAMGraph(ERS_STRUCT_SystemUtils* SystemUtils) {
    
    SystemUtils_ = SystemUtils;

}

Widget_RAMGraph::~Widget_RAMGraph() {

}

void Widget_RAMGraph::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        bool WindowVisible = ImGui::Begin("Frame Latency Graph", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(300,250), ImGuiCond_FirstUseEver);

            // Check If Window Visible
            if (WindowVisible) {

                // Get Window Size (To Size Graph)
                ImVec2 WindowSize = ImGui::GetContentRegionAvail();
                ImVec2 GraphSize = ImVec2(WindowSize.x, WindowSize.y);

                // Graph
                if (WindowVisible && (SystemUtils_->FramerateManager_->ActualFrameTimesMS_.size() > 0)) {
                    ImPlot::SetNextAxesToFit();
                    bool PlotVisible = ImPlot::BeginPlot("Frame Latency Graph", GraphSize);
                    if (PlotVisible) {
                        ImPlot::PlotLine("Frame Latency (ms)", (const float*)SystemUtils_->FramerateManager_->ActualFrameTimesMS_.data(), SystemUtils_->FramerateManager_->ActualFrameTimesMS_.size());
                        ImPlot::EndPlot();
                    }
                }

            }

        // End System Info Window
        ImGui::End();
        

    }


}