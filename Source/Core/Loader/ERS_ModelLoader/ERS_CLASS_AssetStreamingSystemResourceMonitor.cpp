//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingSystemResourceMonitor.h>


ERS_CLASS_AssetStreamingSystemResourceMonitor::ERS_CLASS_AssetStreamingSystemResourceMonitor(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Starting Asset Streaming Subsystem", 5);

    // Initialize Memory Info
    TotalSystemRAM_ = 0;
    TotalSystemVRAM_ = 0;
    UsedSystemRAM_ = 0;
    UsedSystemVRAM_ = 0;

    // Get System Memory Size Info
    SystemUtils_->Logger_->Log("Detecting Hardware Memory Information", 4);
    ERS_STRUCT_HardwareInfo HWInfo = SystemUtils_->ERS_CLASS_HardwareInformation_->GetHWInfo();

    TotalSystemRAM_ = HWInfo.Dynamic_.PhysicalMemoryCapacity;
    SystemUtils_->Logger_->Log(std::string("Detected RAM Size To Be ") + std::to_string(TotalSystemRAM_) + " Bytes", 3);
    if (HWInfo.Static_.GPUVRAMSizes.size() > 0) {
        TotalSystemVRAM_ = HWInfo.Static_.GPUVRAMSizes[0];
        SystemUtils_->Logger_->Log(std::string("Detected VRAM Size To Be ") + std::to_string(TotalSystemVRAM_) + " Bytes", 3);
    } else {
        TotalSystemVRAM_ = 4294967296; // Assume 4gb of VRAM min
        SystemUtils_->Logger_->Log(std::string("Failed To Detect VRAM Size, Assuming Minimum Of ") + std::to_string(TotalSystemVRAM_) + " Bytes", 7);
    }

}

ERS_CLASS_AssetStreamingSystemResourceMonitor::~ERS_CLASS_AssetStreamingSystemResourceMonitor() {

    SystemUtils_->Logger_->Log("Asset Streaming Subsystem Destructor Invoked", 6);

}


bool ERS_CLASS_AssetStreamingSystemResourceMonitor::TextureFitsInVRAMBudget(unsigned long Size) {

    // Calculate Free Sizes
    long HardwareFreeBytes = TotalSystemVRAM_ - UsedSystemVRAM_;
    long BudgetFreeBytes = SystemUtils_->RendererSettings_->VRAMBudget_ - UsedSystemVRAM_;

    // Perform Comparison To Check If The Texture Would Fit
    bool FitsInHardware = Size < HardwareFreeBytes;
    bool FitsInBudget = Size < BudgetFreeBytes;

    // Return Result
    return FitsInBudget && FitsInHardware;
}
