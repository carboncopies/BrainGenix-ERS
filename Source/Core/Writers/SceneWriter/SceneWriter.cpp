//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-22
*/

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <SceneWriter.h>

// SceneWriter Constructor
SceneWriter::SceneWriter(LoggerClass *Logger) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initializaton Start
    Logger_->Log("Initializing SceneWriter Subsystem", 5);

}

// SceneWriter Destructor
SceneWriter::~SceneWriter() {

    // Log Destructor Call
    Logger_->Log("SceneWriter Destructor Called", 6);

}

// Process Scenes
void SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene, const char* ScenePath) {

    // Convert Scene To YAML
    std::string ScenefileData = ProcessScene(InputScene); 

    // Write To File
    std::ofstream FileOutput(ScenePath);
    FileOutput<<ScenefileData.c_str();
    FileOutput.close();

}

// SceneWriter Process Scene Function
std::string SceneWriter::ProcessScene(ERS_OBJECT_SCENE InputScene) {

    // Log Scene Write
    Logger_->Log(std::string(std::string("Serializing Scene '") + InputScene.SceneName + std::string("'")).c_str(), 4);

    // Create Emitter
    YAML::Emitter Output;

    // Begin Writing
    Output << YAML::BeginMap;

    // Write Metadata
    Output << YAML::Key << "SceneName" << YAML::Value << InputScene.SceneName;
    Output << YAML::Key << "SceneFormatVersion" << YAML::Value << InputScene.SceneFormatVersion;

    // Write SceneData
    Output << YAML::Key << "SceneData";
    Output << YAML::Key << YAML::BeginMap;

    long AssetIndex = 0;

    while (AssetIndex < InputScene.Models.size()) {

        // Begin Asset Tag
        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;

        // Write Asset Metadata
        Output << YAML::Key << "AssetName" << YAML::Value << InputScene.Models[AssetIndex].Name;
        Output << YAML::Key << "AssetType" << YAML::Value << "Model";
        Output << YAML::Key << "AssetPath" << YAML::Value << InputScene.Models[AssetIndex].AssetPath_;

        // Write Asset Position Data
        Output << YAML::Key << "AssetPositionX" << YAML::Value << InputScene.Models[AssetIndex].ModelPosition[0];
        Output << YAML::Key << "AssetPositionY" << YAML::Value << InputScene.Models[AssetIndex].ModelPosition[1];
        Output << YAML::Key << "AssetPositionZ" << YAML::Value << InputScene.Models[AssetIndex].ModelPosition[2];

        Output << YAML::Key << "AssetRotationX" << YAML::Value << InputScene.Models[AssetIndex].ModelRotation[0];
        Output << YAML::Key << "AssetRotationY" << YAML::Value << InputScene.Models[AssetIndex].ModelRotation[1];
        Output << YAML::Key << "AssetRotationZ" << YAML::Value << InputScene.Models[AssetIndex].ModelRotation[2];

        Output << YAML::Key << "AssetScaleX" << YAML::Value << InputScene.Models[AssetIndex].ModelScale[0];
        Output << YAML::Key << "AssetScaleY" << YAML::Value << InputScene.Models[AssetIndex].ModelScale[1];
        Output << YAML::Key << "AssetScaleZ" << YAML::Value << InputScene.Models[AssetIndex].ModelScale[2];

        // Write Asset Texture Data
        Output << YAML::Key << "FlipTextures" << YAML::Value << InputScene.Models[AssetIndex].FlipTextures;

        
        // End Map
        Output << YAML::EndMap;

        AssetIndex++;
    }

    // End Writing
    Output << YAML::EndMap;
    Output << YAML::EndMap;


    // Check For Errors
    if (!Output.good()) {
        std::string LogError = "Scene Serialization Error: " + std::string(Output.GetLastError()) + std::string("\n");
        Logger_->Log(LogError.c_str(), 8);
    }

    // Return Scene
    return std::string(Output.c_str());

}

