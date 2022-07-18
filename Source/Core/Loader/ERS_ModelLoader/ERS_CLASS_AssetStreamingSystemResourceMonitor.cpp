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

        SystemUtils_->Logger_->Log("Reading Configuration File For VRAM Margin", 4);

        long VRAMMargin = 4294967296; // Add 4GB Default Margin
        if (SystemUtils_->LocalSystemConfiguration_["VRAMMarginBytes"]) {
            VRAMMargin = SystemUtils_->LocalSystemConfiguration_["VRAMMarginBytes"].as<long>();
            SystemUtils_->Logger_->Log(std::string("Adding Margin Of ") + std::to_string(VRAMMargin) + " Bytes", 4);
            TotalSystemVRAM_ -= VRAMMargin;
        } else {
            SystemUtils_->Logger_->Log(std::string("Failed To Find VRAMMarginBytes Parameter, Assuming A Margin Of ") + std::to_string(VRAMMargin) + " Bytes", 8);
        }
    } else {
        TotalSystemVRAM_ = 4294967296; // Assume 4gb of VRAM min
        SystemUtils_->Logger_->Log(std::string("Failed To Detect VRAM Size, Assuming Minimum Of ") + std::to_string(TotalSystemVRAM_) + " Bytes Free", 7);
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

void ERS_CLASS_AssetStreamingSystemResourceMonitor::SetTextureVRAMBudget(unsigned long Size) {
    SystemUtils_->RendererSettings_->VRAMBudget_ = Size;
}

void ERS_CLASS_AssetStreamingSystemResourceMonitor::AllocateTextureVRAMFromBudget(unsigned long Size) {
    UsedSystemVRAM_ += Size;
}

void ERS_CLASS_AssetStreamingSystemResourceMonitor::DeallocateTextureVRAMFromBudget(unsigned long Size) {
    UsedSystemVRAM_ -= Size;
}


bool ERS_CLASS_AssetStreamingSystemResourceMonitor::TextureFitsInRAMBudget(unsigned long Size) {

    // Calculate Free Sizes
    long HardwareFreeBytes = TotalSystemRAM_ - UsedSystemRAM_;
    long BudgetFreeBytes = SystemUtils_->RendererSettings_->RAMBudget_ - UsedSystemRAM_;

    // Perform Comparison To Check If The Texture Would Fit
    bool FitsInHardware = Size < HardwareFreeBytes;
    bool FitsInBudget = Size < BudgetFreeBytes;

    // Return Result
    return FitsInBudget && FitsInHardware;
}

void ERS_CLASS_AssetStreamingSystemResourceMonitor::SetTextureRAMBudget(unsigned long Size) {
    SystemUtils_->RendererSettings_->RAMBudget_ = Size;
}

void ERS_CLASS_AssetStreamingSystemResourceMonitor::AllocateTextureRAMFromBudget(unsigned long Size) {
    UsedSystemRAM_ += Size;
}

void ERS_CLASS_AssetStreamingSystemResourceMonitor::DeallocateTextureRAMFromBudget(unsigned long Size) {
    UsedSystemRAM_ -= Size;
}
