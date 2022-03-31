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


    // Update Data In Vectors
    ERS_STRUCT_HardwareInfo HWInfo = SystemUtils_->HardwareInformation_->GetHWInfo();
    TotalRAM_.push_back(HWInfo.Dynamic_.PhysicalMemoryCapacity / 1073741824);
    UsedRAM_.push_back((HWInfo.Dynamic_.PhysicalMemoryCapacity - HWInfo.Dynamic_.PhysicalMemoryFree) / 1073741824);
    TotalSwap_.push_back(HWInfo.Dynamic_.SwapCapacity / 1073741824);
    UsedSwap_.push_back((HWInfo.Dynamic_.SwapCapacity - HWInfo.Dynamic_.SwapFree) / 1073741824);



    // If Window Drawing Enabled
    if (Enabled_) {
        bool WindowVisible = ImGui::Begin("RAM Graph", &Enabled_);

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
                    bool PlotVisible = ImPlot::BeginPlot("RAM Information", GraphSize);


                    if (PlotVisible) {
                        ImPlot::PlotLine("Total RAM (GB)", (const float*)TotalRAM_.data(), TotalRAM_.size());
                        ImPlot::PlotLine("Used RAM (GB)", (const float*)UsedRAM_.data(), UsedRAM_.size());
                        ImPlot::PlotLine("Total Swap (GB)", (const float*)TotalSwap_.data(), TotalSwap_.size());
                        ImPlot::PlotLine("Used Swap (GB)", (const float*)UsedSwap_.data(), UsedSwap_.size());


                        ImPlot::EndPlot();
                    }
                }

            }

        // End System Info Window
        ImGui::End();
        

    }


}