//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the controller settings loader system.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-09
*/

#include <ERS_ControllerSettingsLoader.h>


// Constructor
ERS_CLASS_ControllerSettingsLoader::ERS_CLASS_ControllerSettingsLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS Controller Settings Loader", 5);

}


// Destructor
ERS_CLASS_ControllerSettingsLoader::~ERS_CLASS_ControllerSettingsLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Controller Settings Loader Destructor Called", 4);

};


// Load System Controller Settings
bool ERS_CLASS_ControllerSettingsLoader::LoadControllerSettings(std::shared_ptr<ERS_STRUCT_ControllerSettings> ControllerSettings, long AssetID) {

    // Log Loading
    SystemUtils_->Logger_->Log(std::string(std::string("Loading ERS Controller Settings From AssetID: ") + std::to_string(AssetID)).c_str(), 4);

    // Read Data
    std::shared_ptr<ERS_STRUCT_IOData> SettingsRawData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, SettingsRawData);
    std::string SettingsEncodedString = std::string((const char*)SettingsRawData->Data.get());
    YAML::Node SettingsData = YAML::Load(SettingsEncodedString);
    

    // Populate Settings Params
    ControllerSettings->JoystickLeftXGain = SettingsData["JoystickLeftXGain"].as<float>();
    ControllerSettings->JoystickLeftYGain = SettingsData["JoystickLeftYGain"].as<float>();

    ControllerSettings->JoystickRightXGain = SettingsData["JoystickRightXGain"].as<float>();
    ControllerSettings->JoystickRightYGain = SettingsData["JoystickRightYGain"].as<float>();


    ControllerSettings->MinThresholdJoystickLeftX = SettingsData["MinThresholdJoystickLeftX"].as<float>();
    ControllerSettings->MinThresholdJoystickLeftY = SettingsData["MinThresholdJoystickLeftY"].as<float>();
    ControllerSettings->MinThresholdJoystickRightX = SettingsData["MinThresholdJoystickLeftX"].as<float>();
    ControllerSettings->MinThresholdJoystickRightY = SettingsData["MinThresholdJoystickRightY"].as<float>();

    ControllerSettings->MaxThresholdJoystickLeftX = SettingsData["MaxThresholdJoystickLeftX"].as<float>();
    ControllerSettings->MaxThresholdJoystickLeftY = SettingsData["MaxThresholdJoystickLeftY"].as<float>();
    ControllerSettings->MaxThresholdJoystickRightX = SettingsData["MaxThresholdJoystickRightX"].as<float>();
    ControllerSettings->MaxThresholdJoystickRightY = SettingsData["MaxThresholdJoystickRightY"].as<float>();


    ControllerSettings->JoystickLeftButtonIndex = SettingsData["JoystickLeftButtonIndex"].as<int>();
    ControllerSettings->JoystickRightButtonIndex = SettingsData["JoystickRightButtonIndex"].as<int>();
    ControllerSettings->BackButtonIndex = SettingsData["BackButtonIndex"].as<int>();
    ControllerSettings->MenuButtonIndex = SettingsData["MenuButtonIndex"].as<int>();
    ControllerSettings->OptionsButtonIndex = SettingsData["OptionsButtonIndex"].as<int>();
    ControllerSettings->TriangleButtonIndex = SettingsData["TriangleButtonIndex"].as<int>();
    ControllerSettings->SquareButtonIndex = SettingsData["SquareButtonIndex"].as<int>();
    ControllerSettings->CircleButtonIndex = SettingsData["CircleButtonIndex"].as<int>();
    ControllerSettings->CrossButtonIndex = SettingsData["CrossButtonIndex"].as<int>();
    ControllerSettings->RightBumperButtonIndex = SettingsData["RightBumperButtonIndex"].as<int>();
    ControllerSettings->LeftBumperButtonIndex = SettingsData["LeftBumperButtonIndex"].as<int>();
    
    

}