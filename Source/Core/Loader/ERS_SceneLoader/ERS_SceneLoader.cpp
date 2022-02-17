//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <ERS_SceneLoader.h>

ERS_CLASS_SceneLoader::ERS_CLASS_SceneLoader(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader) {

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

        } else if (AssetType == std::string("DirectionalLight")) {

            // Setup Model Pointer In Scene To Work On
            Scene.DirectionalLights.push_back(std::make_shared<ERS_STRUCT_DirectionalLight>());
            int LightIndex = Scene.DirectionalLights.size() - 1;

            Scene.DirectionalLights[LightIndex]->UserDefinedName = AssetName;
            
            Scene.DirectionalLights[LightIndex]->Ambient = glm::vec3(
                SceneDataNode[i]["AmbientRed"].as<float>(),
                SceneDataNode[i]["AmbientGreen"].as<float>(),
                SceneDataNode[i]["AmbientBlue"].as<float>()
                );
            Scene.DirectionalLights[LightIndex]->Diffuse = glm::vec3(
                SceneDataNode[i]["DiffuseRed"].as<float>(),
                SceneDataNode[i]["DiffuseGreen"].as<float>(),
                SceneDataNode[i]["DiffuseBlue"].as<float>()
                );
            Scene.DirectionalLights[LightIndex]->Specular = glm::vec3(
                SceneDataNode[i]["SpecularRed"].as<float>(),
                SceneDataNode[i]["SpecularGreen"].as<float>(),
                SceneDataNode[i]["SpecularBlue"].as<float>()
                );

            Scene.DirectionalLights[LightIndex]->Pos = glm::vec3(
                SceneDataNode[i]["PosX"].as<float>(),
                SceneDataNode[i]["PosY"].as<float>(),
                SceneDataNode[i]["PosZ"].as<float>()
                );
            Scene.DirectionalLights[LightIndex]->Rot = glm::vec3(
                SceneDataNode[i]["RotX"].as<float>(),
                SceneDataNode[i]["RotY"].as<float>(),
                SceneDataNode[i]["RotZ"].as<float>()
                );

        } else if (AssetType == std::string("PointLight")) {

            // Setup Model Pointer In Scene To Work On
            Scene.PointLights.push_back(std::make_shared<ERS_STRUCT_PointLight>());
            int LightIndex = Scene.PointLights.size() - 1;

            Scene.PointLights[LightIndex]->UserDefinedName = AssetName;


            Scene.PointLights[LightIndex]->RolloffConstant = SceneDataNode[i]["RolloffConstant"].as<float>();
            Scene.PointLights[LightIndex]->RolloffLinear = SceneDataNode[i]["RolloffLinear"].as<float>();
            Scene.PointLights[LightIndex]->RolloffQuadratic = SceneDataNode[i]["RolloffQuadratic"].as<float>();

            
            Scene.PointLights[LightIndex]->Ambient = glm::vec3(
                SceneDataNode[i]["AmbientRed"].as<float>(),
                SceneDataNode[i]["AmbientGreen"].as<float>(),
                SceneDataNode[i]["AmbientBlue"].as<float>()
                );
            Scene.PointLights[LightIndex]->Diffuse = glm::vec3(
                SceneDataNode[i]["DiffuseRed"].as<float>(),
                SceneDataNode[i]["DiffuseGreen"].as<float>(),
                SceneDataNode[i]["DiffuseBlue"].as<float>()
                );
            Scene.PointLights[LightIndex]->Specular = glm::vec3(
                SceneDataNode[i]["SpecularRed"].as<float>(),
                SceneDataNode[i]["SpecularGreen"].as<float>(),
                SceneDataNode[i]["SpecularBlue"].as<float>()
                );

            Scene.PointLights[LightIndex]->Pos = glm::vec3(
                SceneDataNode[i]["PosX"].as<float>(),
                SceneDataNode[i]["PosY"].as<float>(),
                SceneDataNode[i]["PosZ"].as<float>()
                );

        } else if (AssetType == std::string("SpotLight")) {

            // Setup Model Pointer In Scene To Work On
            Scene.SpotLights.push_back(std::make_shared<ERS_STRUCT_SpotLight>());
            int LightIndex = Scene.SpotLights.size() - 1;

            Scene.SpotLights[LightIndex]->UserDefinedName = AssetName;


            Scene.SpotLights[LightIndex]->RolloffConstant = SceneDataNode[i]["RolloffConstant"].as<float>();
            Scene.SpotLights[LightIndex]->RolloffLinear = SceneDataNode[i]["RolloffLinear"].as<float>();
            Scene.SpotLights[LightIndex]->RolloffQuadratic = SceneDataNode[i]["RolloffQuadratic"].as<float>();


            Scene.SpotLights[LightIndex]->CutOff = SceneDataNode[i]["CutOff"].as<float>();
            Scene.SpotLights[LightIndex]->OuterCutOff = SceneDataNode[i]["OuterCutOff"].as<float>();


            Scene.SpotLights[LightIndex]->Ambient = glm::vec3(
                SceneDataNode[i]["AmbientRed"].as<float>(),
                SceneDataNode[i]["AmbientGreen"].as<float>(),
                SceneDataNode[i]["AmbientBlue"].as<float>()
                );
            Scene.SpotLights[LightIndex]->Diffuse = glm::vec3(
                SceneDataNode[i]["DiffuseRed"].as<float>(),
                SceneDataNode[i]["DiffuseGreen"].as<float>(),
                SceneDataNode[i]["DiffuseBlue"].as<float>()
                );
            Scene.SpotLights[LightIndex]->Specular = glm::vec3(
                SceneDataNode[i]["SpecularRed"].as<float>(),
                SceneDataNode[i]["SpecularGreen"].as<float>(),
                SceneDataNode[i]["SpecularBlue"].as<float>()
                );

            Scene.SpotLights[LightIndex]->Pos = glm::vec3(
                SceneDataNode[i]["PosX"].as<float>(),
                SceneDataNode[i]["PosY"].as<float>(),
                SceneDataNode[i]["PosZ"].as<float>()
                );
            Scene.SpotLights[LightIndex]->Rot = glm::vec3(
                SceneDataNode[i]["RotX"].as<float>(),
                SceneDataNode[i]["RotY"].as<float>(),
                SceneDataNode[i]["RotZ"].as<float>()
                );


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