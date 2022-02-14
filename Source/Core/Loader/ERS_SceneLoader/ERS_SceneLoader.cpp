//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <ERS_SceneLoader.h>

ERS_CLASS_SceneLoader::ERS_CLASS_SceneLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader) {

    SystemUtils_ = SystemUtils;
    ModelLoader_ = ModelLoader;

    SystemUtils_->Logger_->Log("Initializing ERS_CLASS_SceneLoader Subsystem", 5);

}

ERS_CLASS_SceneLoader::~ERS_CLASS_SceneLoader() {

    SystemUtils_->Logger_->Log("ERS_CLASS_SceneLoader Destructor Called", 6);

}

ERS_STRUCT_Scene ERS_CLASS_SceneLoader::ProcessScene(long AssetID) {

    // Read Asset Info
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Scene At ID: ") + std::to_string(AssetID)).c_str(), 4);
    std::shared_ptr<ERS_STRUCT_IOData> SceneData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, SceneData);


    // Load Then Process Scene
    std::string SceneDataString = std::string((const char*)SceneData->Data.get());
    YAML::Node SceneNode = YAML::Load(SceneDataString);

    return ProcessScene(SceneNode, AssetID);

}

ERS_STRUCT_Scene ERS_CLASS_SceneLoader::ProcessScene(YAML::Node RawSceneData, long AssetID) {

    // Create Scene Instance
    ERS_STRUCT_Scene Scene;

    // Grab Metadata
    Scene.SceneFormatVersion = RawSceneData["SceneFormatVersion"].as<long>();
    Scene.SceneName = RawSceneData["SceneName"].as<std::string>();
    Scene.ScenePath = AssetID;

    // Log Scene Processing
    SystemUtils_->Logger_->Log(std::string(std::string("Processing Scene: ") + std::string(Scene.SceneName)).c_str(), 3);

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

        // If type Is Model
        if (AssetType == std::string("Model")) {

            long AssetID = SceneDataNode[i]["AssetID"].as<long>();


            // Get Model Texture Info
            bool FlipTextures = SceneDataNode[i]["FlipTextures"].as<bool>();

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

            //Load Model 
            Scene.Models.push_back(std::make_shared<ERS_STRUCT_Model>());
            int CurrentSize = Scene.Models.size();
            ModelLoader_->AddModelToLoadingQueue(AssetID, Scene.Models[CurrentSize-1], FlipTextures);

            // Add Instance To Models Vector
            Scene.Models[CurrentSize-1]->IsTemplateModel = false;
            Scene.Models[CurrentSize-1]->SetLocRotScale(glm::vec3(PosX, PosY, PosZ), glm::vec3(RotX, RotY, RotZ), glm::vec3(ScaleX, ScaleY, ScaleZ));
            Scene.Models[CurrentSize-1]->ApplyTransformations();
            Scene.Models[CurrentSize-1]->AssetID = AssetID;
            Scene.Models[CurrentSize-1]->Name = AssetName;
            Scene.Models[CurrentSize-1]->FlipTextures = FlipTextures;

        } else if (AssetType == std::string("Light")) {

            // Setup Model Pointer In Scene To Work On
            Scene.Lights.push_back(std::make_shared<ERS_STRUCT_Light>());
            int LightIndex = Scene.Lights.size() - 1;


            Scene.Lights[LightIndex]->UserDefinedName = AssetName;
            Scene.Lights[LightIndex]->UserAdditionalNotes = SceneDataNode[i]["AdditionalNotes"].as<std::string>();
            Scene.Lights[LightIndex]->LightType = SceneDataNode[i]["LightType"].as<std::string>();
            
            Scene.Lights[LightIndex]->Intensity = SceneDataNode[i]["Intensity"].as<float>();
            Scene.Lights[LightIndex]->ColorRed = SceneDataNode[i]["ColorRed"].as<float>();
            Scene.Lights[LightIndex]->ColorGreen = SceneDataNode[i]["ColorGreen"].as<float>();
            Scene.Lights[LightIndex]->ColorBlue = SceneDataNode[i]["ColorBlue"].as<float>();

            Scene.Lights[LightIndex]->PosX = SceneDataNode[i]["PosX"].as<float>();
            Scene.Lights[LightIndex]->PosY = SceneDataNode[i]["PosY"].as<float>();
            Scene.Lights[LightIndex]->PosZ = SceneDataNode[i]["PosZ"].as<float>();

            Scene.Lights[LightIndex]->RotX = SceneDataNode[i]["PosX"].as<float>();
            Scene.Lights[LightIndex]->RotY = SceneDataNode[i]["RotY"].as<float>();
            Scene.Lights[LightIndex]->RotZ = SceneDataNode[i]["RotZ"].as<float>();

            Scene.Lights[LightIndex]->PosX = SceneDataNode[i]["PosX"].as<float>();
            Scene.Lights[LightIndex]->PosX = SceneDataNode[i]["PosX"].as<float>();
            Scene.Lights[LightIndex]->PosX = SceneDataNode[i]["PosX"].as<float>();



        }

    }

    // Indicate Scene Is Loaded
    Scene.IsSceneLoaded = true;

    // Return Scene
    return Scene;

}

void ERS_CLASS_SceneLoader::AddModel(std::shared_ptr<ERS_STRUCT_Scene> Scene, long AssetID) {

    // Log Model Addition
    SystemUtils_->Logger_->Log(std::string(std::string("Adding Model With ID '") + std::to_string(AssetID) + std::string("' To Scene")).c_str(), 3);

    // Add Model To Loading Queue
    Scene->Models.push_back(std::make_shared<ERS_STRUCT_Model>());
    int CurrentSize = Scene->Models.size();

    Scene->Models[CurrentSize-1]->IsTemplateModel = false;
    Scene->Models[CurrentSize-1]->SetLocRotScale(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Scene->Models[CurrentSize-1]->ApplyTransformations();
    Scene->Models[CurrentSize-1]->AssetID = AssetID;
    Scene->Models[CurrentSize-1]->Name = std::string("Untitled");
    Scene->Models[CurrentSize-1]->FlipTextures = true;

    ModelLoader_->AddModelToLoadingQueue(AssetID, Scene->Models[CurrentSize-1], Scene->Models[CurrentSize-1]->FlipTextures);



}