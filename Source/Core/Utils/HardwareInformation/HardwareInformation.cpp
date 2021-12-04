//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing hardware information collection.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-03
*/

#include <HardwareInformation.h>







static const char* cache_type_name(iware::cpu::cache_type_t cache_type) noexcept {
	switch(cache_type) {
		case iware::cpu::cache_type_t::unified:
			return "Unified";
		case iware::cpu::cache_type_t::instruction:
			return "Instruction";
		case iware::cpu::cache_type_t::data:
			return "Data";
		case iware::cpu::cache_type_t::trace:
			return "Trace";
		default:
			return "Unknown";
	}
}

static const char* architecture_name(iware::cpu::architecture_t architecture) noexcept {
	switch(architecture) {
		case iware::cpu::architecture_t::x64:
			return "x64";
		case iware::cpu::architecture_t::arm:
			return "ARM";
		case iware::cpu::architecture_t::itanium:
			return "Itanium";
		case iware::cpu::architecture_t::x86:
			return "x86";
		default:
			return "Unknown";
	}
}

static const char* endianness_name(iware::cpu::endianness_t endianness) noexcept {
	switch(endianness) {
		case iware::cpu::endianness_t::little:
			return "Little-Endian";
		case iware::cpu::endianness_t::big:
			return "Big-Endian";
		default:
			return "Unknown";
	}
}

static const char* kernel_variant_name(iware::system::kernel_t variant) noexcept {
	switch(variant) {
		case iware::system::kernel_t::windows_nt:
			return "Windows NT";
		case iware::system::kernel_t::linux:
			return "Linux";
		case iware::system::kernel_t::darwin:
			return "Darwin";
		default:
			return "Unknown";
	}
}




// HWinfo Constructor
HardwareInformation::HardwareInformation(LoggerClass *Logger) {

    // Copy Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Hardware Info Subsystem", 5);

    // Collect Static Hardware Information
    Logger_->Log("Collecting Static Hardware Information", 5);

    // Get System Info
    Logger_->Log("Getting System Information", 4);
    const auto KernelInfo = iware::system::kernel_info();
    const auto OSInfo = iware::system::OS_info();
    HardwareInfo_.Static_.KernelName = std::string(kernel_variant_name(KernelInfo.variant));
    HardwareInfo_.Static_.KernelVersion = std::string(std::string(KernelInfo.major) + std::string('.') + std::string(KernelInfo.minor) + std::string('.') + std::string(KernelInfo.patch) + std::string(" Build ") + std::string(KernelInfo.build_number));

    // Get CPU Info
    Logger_->Log("Getting CPU Information", 4);
    const auto CPUQuantities = iware::cpu::quantities();
    HardwareInfo_.Static_.CPUPhysicalCores = CPUQuantities.physical;
    HardwareInfo_.Static_.CPULogicalCores = CPUQuantities.logical;
    HardwareInfo_.Static_.CPUPackages = CPUQuantities.packages;
    HardwareInfo_.Static_.CPUArchitecture = std::string(architecture_name(iware::cpu::architecture()));
    HardwareInfo_.Static_.CPUEndianness = std::string(endianness_name(iware::cpu::endianness()));
    HardwareInfo_.Static_.CPUModelName = std::string(iware::cpu::model_name());
    HardwareInfo_.Static_.CPUModelName = std::string(iware::cpu::vendor_id());

    Logger_->Log(std::string(std::string("Physical CPU Cores: ") + std::to_string(HardwareInfo_.Static_.CPUPhysicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Logical CPU Cores: ") + std::to_string(HardwareInfo_.Static_.CPULogicalCores)).c_str(), 4);
    Logger_->Log(std::string(std::string("Physical CPU Packages: ") + std::to_string(HardwareInfo_.Static_.CPUPackages)).c_str(), 4);
    Logger_->Log(std::string(std::string("CPU Architecture: ") + HardwareInfo_.Static_.CPUArchitecture).c_str(), 4);
    Logger_->Log(std::string(std::string("CPU Endianness: ") + HardwareInfo_.Static_.CPUEndianness).c_str(), 4);
    Logger_->Log(std::string(std::string("CPU Model Name: ") + HardwareInfo_.Static_.CPUModelName).c_str(), 4);
    Logger_->Log(std::string(std::string("CPU Vendor ID: ") + HardwareInfo_.Static_.CPUVendorID).c_str(), 4);

    // Get CPU Cache Info
    for (int i = 0; i < 3; i++) {
        const auto CPUCacheInfo = iware::cpu::cache(i+1);
        HardwareInfo_.Static_.CPUPhysicalCoreCacheSize.push_back(CPUCacheInfo.size);
        HardwareInfo_.Static_.CPUPhysicalCoreCacheLineSize.push_back(CPUCacheInfo.line_size);
        HardwareInfo_.Static_.CPUPhysicalCoreAssociativity.push_back(CPUCacheInfo.associativity);
        HardwareInfo_.Static_.CPUPhysicalCoreType.push_back(cache_type_name(CPUCacheInfo.type));
        
        Logger_->Log(std::string(std::string("Cache Level: ") + std::to_string(i+1)).c_str(), 4);
        Logger_->Log(std::string(std::string("    Cache Size: ") + std::to_string(HardwareInfo_.Static_.CPUPhysicalCoreCacheSize[i])).c_str(), 4);
        Logger_->Log(std::string(std::string("    Cache Line Size: ") + std::to_string(HardwareInfo_.Static_.CPUPhysicalCoreCacheLineSize[i])).c_str(), 4);
        Logger_->Log(std::string(std::string("    Cache Associativity: ") + std::to_string(HardwareInfo_.Static_.CPUPhysicalCoreAssociativity[i])).c_str(), 4);
        Logger_->Log(std::string(std::string("    Cache Type: ") + std::string(HardwareInfo_.Static_.CPUPhysicalCoreType[i])).c_str(), 4);

    }



}

// Destructor
HardwareInformation::~HardwareInformation() {

    // Log Destructor Call
    Logger_->Log("Hardware Information Destructor Called", 4);

}