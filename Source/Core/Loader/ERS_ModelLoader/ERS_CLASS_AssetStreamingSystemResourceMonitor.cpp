//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingSystemResourceMonitor.h>


ERS_CLASS_AssetStreamingSystemResourceMonitor::ERS_CLASS_AssetStreamingSystemResourceMonitor(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Starting Asset Streaming Subsystem", 5);

    // Get System Resource Info
    SystemUtils_->Logger_->Log("Detecting Hardware Memory Information", 4);
    ERS_STRUCT_HardwareInfo HWInfo = SystemUtils_->ERS_CLASS_HardwareInformation_->GetHWInfo();

    TotalSystemRAM_ = HWInfo.Dynamic_.PhysicalMemoryCapacity;
    
    if (HWInfo.Static_.GPUVRAMSizes.size() > 0) {
        TotalSystemVRAM_ = HWInfo.Static_.GPUVRAMSizes[0];
    } else {
        TotalSystemVRAM_ = 4294967296; // Assume 4gb of VRAM min
    }
}