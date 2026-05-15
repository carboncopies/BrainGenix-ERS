//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GPURequest.h>

#include <cstdlib>

namespace {

void SetGPUSelectionEnvVar(const char* Name, const std::string& Value) {
#ifdef _WIN32
    _putenv_s(Name, Value.c_str());
#else
    setenv(Name, Value.c_str(), 1);
#endif
}

}

void ERS_FUNCTION_ApplyGPUSelectionRequest(BG::Common::Logger::LoggingSystem* Logger, const ERS_STRUCT_HardwareInfo& HardwareInfo) {

    if (!HardwareInfo.Static_.HasPreferredGPU) {
        Logger->Log("No preferred GPU request was exported for future EGL/device-selection paths.", 3);
        return;
    }

    SetGPUSelectionEnvVar("BG_ERS_PREFERRED_GPU_ID", std::to_string(HardwareInfo.Static_.PreferredGPUDeviceID));
    SetGPUSelectionEnvVar("BG_ERS_PREFERRED_GPU_VENDOR", HardwareInfo.Static_.PreferredGPUVendor);
    SetGPUSelectionEnvVar("BG_ERS_PREFERRED_GPU_NAME", HardwareInfo.Static_.PreferredGPUName);

    Logger->Log(std::string("Exported preferred GPU request for future platform backends: Device ")
        + std::to_string(HardwareInfo.Static_.PreferredGPUDeviceID)
        + std::string(" [")
        + HardwareInfo.Static_.PreferredGPUVendor
        + std::string("] ")
        + HardwareInfo.Static_.PreferredGPUName
        + std::string(" (")
        + HardwareInfo.Static_.PreferredGPUSelectionReason
        + std::string(")"), 3);

#ifdef _WIN32
    Logger->Log("Windows discrete-GPU export symbols remain enabled; future EGL/non-Windows paths can also read BG_ERS_PREFERRED_GPU_*.", 3);
#else
    Logger->Log("Future EGL platform-device code can read BG_ERS_PREFERRED_GPU_* to bind the requested GPU explicitly.", 3);
#endif
}
