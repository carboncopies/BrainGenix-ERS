//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GPURequest.h>

// cppcheck-suppress missingIncludeSystem
#include <algorithm>
// cppcheck-suppress missingIncludeSystem
#include <cctype>
// cppcheck-suppress missingIncludeSystem
#include <cstdlib>

namespace {

void SetGPUSelectionEnvVar(const char* Name, const std::string& Value) {
#ifdef _WIN32
    _putenv_s(Name, Value.c_str());
#else
    setenv(Name, Value.c_str(), 1);
#endif
}

bool ContainsInsensitive(const std::string& Value, const char* Needle) {
    std::string ValueLower = Value;
    std::string NeedleLower = Needle;
    std::transform(ValueLower.begin(), ValueLower.end(), ValueLower.begin(), [](unsigned char Character) {
        return static_cast<char>(std::tolower(Character));
    });
    std::transform(NeedleLower.begin(), NeedleLower.end(), NeedleLower.begin(), [](unsigned char Character) {
        return static_cast<char>(std::tolower(Character));
    });
    return ValueLower.find(NeedleLower) != std::string::npos;
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
    SetGPUSelectionEnvVar("BG_ERS_PREFERRED_GPU_REASON", HardwareInfo.Static_.PreferredGPUSelectionReason);

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
    SetGPUSelectionEnvVar("DRI_PRIME", std::to_string(HardwareInfo.Static_.PreferredGPUDeviceID));
    Logger->Log(std::string("Exported DRI_PRIME=")
        + std::to_string(HardwareInfo.Static_.PreferredGPUDeviceID)
        + std::string(" for Linux EGL/OpenGL GPU selection before renderer startup."), 3);

    std::string PreferredGPUDescription = HardwareInfo.Static_.PreferredGPUVendor + std::string(" ") + HardwareInfo.Static_.PreferredGPUName;
    if (ContainsInsensitive(PreferredGPUDescription, "nvidia")) {
        SetGPUSelectionEnvVar("__NV_PRIME_RENDER_OFFLOAD", "1");
        SetGPUSelectionEnvVar("__GLX_VENDOR_LIBRARY_NAME", "nvidia");
        Logger->Log("Exported NVIDIA PRIME render-offload hints for the selected GPU.", 3);
    }

    Logger->Log("Future explicit EGL platform-device code can also read BG_ERS_PREFERRED_GPU_* to bind the requested GPU.", 3);
#endif
}
