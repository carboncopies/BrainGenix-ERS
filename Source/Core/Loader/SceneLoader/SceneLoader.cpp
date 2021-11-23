//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#include <SceneLoader.h>

// SceneLoader Constructor
SceneLoader::SceneLoader(LoggerClass *Logger, ModelLoader *ModelLoader) {

    // Create Local Pointer
    Logger_ = Logger;
    ModelLoader_ = ModelLoader;

    // Log Initializaton Start
    Logger_->Log("Initializing SceneLoader Subsystem", 5);

}

// SceneLoader Destructor
SceneLoader::~SceneLoader() {

    // Log Destructor Call
    Logger_->Log("SceneLoader Destructor Called", 6);

}


// SceneLoader Process Scene Function
void SceneLoader::ProcessScene(YAML::Node RawSceneData) {

    // Create Scene Instance
    ERS_OBJECT_SCENE Scene;

    // Grab Metadata
    Scene.SceneFormatVersion = RawSceneData["SceneFormatVersion"].as<long>();
    Scene.SceneName = RawSceneData["SceneName"].as<std::string>();

    // Create Vector Of YAML::Nodes
    std::vector<YAML::Node> SceneItems;

    // Populate Vector With Elements From SceneData
    YAML::Node SceneDataNode = RawSceneData["SceneData"];
    for (YAML::const_iterator it=SceneDataNode.begin(); it!=SceneDataNode.end(); ++it) {
        SceneItems.push_back(it->second);
    }

    // Iterate Through Vector To Add Each Asset To Loading Queue Of Requested Type
    for (long i = 0; i < SceneDataNode.size(); i++) {

        // Get Asset Information
        std::string AssetName = SceneDataNode[i]["AssetName"].as<std::string>();
        std::string AssetType = SceneDataNode[i]["AssetType"].as<std::string>();
        std::string AssetPath = SceneDataNode[i]["AssetPath"].as<std::string>();


        // If type Is Model
        if (AssetType == std::string("Model")) {

            // Get Asset LocRotScale
            float PosX = SceneDataNode[i]["AssetPositionX"].as<double>();
            float PosY = SceneDataNode[i]["AssetPositionY"].as<double>();
            float PosZ = SceneDataNode[i]["AssetPositionZ"].as<double>();

            float RotX = SceneDataNode[i]["AssetRotationX"].as<double>();
            float RotY = SceneDataNode[i]["AssetRotationY"].as<double>();
            float RotZ = SceneDataNode[i]["AssetRotationZ"].as<double>();

            float ScaleX = SceneDataNode[i]["AssetScaleX"].as<double>();
            float ScaleY = SceneDataNode[i]["AssetScaleY"].as<double>();
            float ScaleZ = SceneDataNode[i]["AssetScaleZ"].as<double>();

            // Load Model
            ERS_OBJECT_MODEL Model = ModelLoader_->LoadModelFromFile(AssetPath.c_str());
            Model.SetLocRotScale(glm::vec3(PosX, PosY, PosZ), glm::vec3(RotX, RotY, RotZ), glm::vec3(ScaleX, ScaleY, ScaleZ));
            Scene.Models.push_back(Model);

        }


    }

    // Return Scene
    return Scene;

}

