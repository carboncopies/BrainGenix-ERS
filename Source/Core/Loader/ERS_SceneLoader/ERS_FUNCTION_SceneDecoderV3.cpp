//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SceneDecoderV3.h>


bool ERS_FUNCTION_DecodeSceneV3(YAML::Node SceneData, ERS_STRUCT_Scene *Scene, ERS_STRUCT_SystemUtils *SystemUtils, ERS_CLASS_ModelLoader* ModelLoader, bool LogEnable) {


    // // Grab Metadata
    // Scene->SceneFormatVersion = SceneData["SceneFormatVersion"].as<long>();
    // Scene->SceneName = SceneData["SceneName"].as<std::string>();

    // if (SceneData["ActiveCameraIndex"]) {
    //     Scene->ActiveSceneCameraIndex = SceneData["ActiveCameraIndex"].as<int>();
    // }

    // // Log Scene Processing
    // SystemUtils->Logger_->Log(std::string("Processing Scene: ") + std::string(Scene->SceneName), 3, LogEnable);

    // // Create List Of Scene Items
    // std::vector<YAML::Node> SceneItems;
    // YAML::Node SceneDataNode = SceneData["SceneData"];
    // for (YAML::const_iterator it=SceneDataNode.begin(); it!=SceneDataNode.end(); ++it) {
    //     SceneItems.push_back(it->second);
    // }


    // // Iterate Through Vector To Add Each Asset To Loading Queue Of Requested Type
    // for (long i = 0; (long)i < (long)SceneDataNode.size(); i++) {

    //     // Get Asset Information
    //     std::string AssetName = SceneDataNode[i]["AssetName"].as<std::string>();
    //     std::string AssetType = SceneDataNode[i]["AssetType"].as<std::string>();

    //     // If type Is Model
    //     if (AssetType == std::string("Model")) {

    //         long AssetID = SceneDataNode[i]["AssetID"].as<long>();

    //         // Get Asset LocRotScale
    //         float PosX = SceneDataNode[i]["AssetPositionX"].as<double>();
    //         float PosY = SceneDataNode[i]["AssetPositionY"].as<double>();
    //         float PosZ = SceneDataNode[i]["AssetPositionZ"].as<double>();

    //         float RotX = SceneDataNode[i]["AssetRotationX"].as<double>();
    //         float RotY = SceneDataNode[i]["AssetRotationY"].as<double>();
    //         float RotZ = SceneDataNode[i]["AssetRotationZ"].as<double>();

    //         float ScaleX = SceneDataNode[i]["AssetScaleX"].as<double>();
    //         float ScaleY = SceneDataNode[i]["AssetScaleY"].as<double>();
    //         float ScaleZ = SceneDataNode[i]["AssetScaleZ"].as<double>();

    //         //Load Model 
    //         Scene->Models.push_back(std::make_shared<ERS_STRUCT_Model>());
    //         int CurrentSize = Scene->Models.size();
    //         ModelLoader->AddModelToLoadingQueue(AssetID, Scene->Models[CurrentSize-1]);

    //         // Add Instance To Models Vector
    //         Scene->Models[CurrentSize-1]->IsTemplateModel = false;
    //         Scene->Models[CurrentSize-1]->SetLocRotScale(glm::vec3(PosX, PosY, PosZ), glm::vec3(RotX, RotY, RotZ), glm::vec3(ScaleX, ScaleY, ScaleZ));
    //         Scene->Models[CurrentSize-1]->ApplyTransformations();
    //         Scene->Models[CurrentSize-1]->AssetID = AssetID;
    //         Scene->Models[CurrentSize-1]->Name = AssetName;


    //         // Load Attached Scripts
    //         if (SceneDataNode[i]["AttachedScripts"]) {
    //             YAML::Node Scripts = SceneDataNode[i]["AttachedScripts"];
    //             for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
    //                 Scene->Models[CurrentSize-1]->AttachedScriptIndexes_.push_back(it->second.as<long>());
    //             }
    //         }


    //         // Load Shadow Configuration
    //         if (SceneDataNode[i]["CastDynamicShadows"]) {
    //             Scene->Models[CurrentSize-1]->CastDynamicShadows_ = SceneDataNode[i]["CastDynamicShadows"].as<bool>();
    //         }

    //         if (SceneDataNode[i]["CastStaticShadows"]) {
    //             Scene->Models[CurrentSize-1]->CastStaticShadows_ = SceneDataNode[i]["CastStaticShadows"].as<bool>();
    //         }

    //         if (SceneDataNode[i]["ReceiveShadows"]) {
    //             Scene->Models[CurrentSize-1]->ReceiveShadows_ = SceneDataNode[i]["ReceiveShadows"].as<bool>();
    //         }

    //         if (SceneDataNode[i]["ShaderOverrideIndex"]) {
    //             Scene->Models[CurrentSize-1]->ShaderOverrideIndex_ = SceneDataNode[i]["ShaderOverrideIndex"].as<long>();
    //         }


    //     } else if (AssetType == std::string("DirectionalLight")) {

    //         // Setup Model Pointer In Scene To Work On
    //         Scene->DirectionalLights.push_back(std::make_shared<ERS_STRUCT_DirectionalLight>());
    //         int LightIndex = Scene->DirectionalLights.size() - 1;

    //         Scene->DirectionalLights[LightIndex]->UserDefinedName = AssetName;

    //         if (SceneDataNode[i]["ColorRed"] && SceneDataNode[i]["ColorGreen"] && SceneDataNode[i]["ColorBlue"]) {
    //             Scene->DirectionalLights[LightIndex]->Color = glm::vec3(
    //                 SceneDataNode[i]["ColorRed"].as<float>(),
    //                 SceneDataNode[i]["ColorGreen"].as<float>(),
    //                 SceneDataNode[i]["ColorBlue"].as<float>()
    //                 );
    //         }

    //         if (SceneDataNode[i]["Intensity"]) {
    //             Scene->DirectionalLights[LightIndex]->Intensity = SceneDataNode[i]["Intensity"].as<float>();
    //         }

    //         if (SceneDataNode[i]["MaxDistance"]) {
    //             Scene->DirectionalLights[LightIndex]->MaxDistance = SceneDataNode[i]["MaxDistance"].as<float>();
    //         }

    //         Scene->DirectionalLights[LightIndex]->Pos = glm::vec3(
    //             SceneDataNode[i]["PosX"].as<float>(),
    //             SceneDataNode[i]["PosY"].as<float>(),
    //             SceneDataNode[i]["PosZ"].as<float>()
    //             );
    //         Scene->DirectionalLights[LightIndex]->Rot = glm::vec3(
    //             SceneDataNode[i]["RotX"].as<float>(),
    //             SceneDataNode[i]["RotY"].as<float>(),
    //             SceneDataNode[i]["RotZ"].as<float>()
    //             );


    //         if (SceneDataNode[i]["CastShadows"]) {
    //             Scene->DirectionalLights[LightIndex]->CastsShadows_ = SceneDataNode[i]["CastShadows"].as<bool>();
    //         }

    //         // Load Attached Scripts
    //         if (SceneDataNode[i]["AttachedScripts"]) {
    //             YAML::Node Scripts = SceneDataNode[i]["AttachedScripts"];
    //             for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
    //                 Scene->DirectionalLights[LightIndex]->AttachedScriptIndexes_.push_back(it->second.as<long>());
    //             }
    //         }

    //     } else if (AssetType == std::string("PointLight")) {

    //         // Setup Model Pointer In Scene To Work On
    //         Scene->PointLights.push_back(std::make_shared<ERS_STRUCT_PointLight>());
    //         int LightIndex = Scene->PointLights.size() - 1;

    //         Scene->PointLights[LightIndex]->UserDefinedName = AssetName;
    //         if (SceneDataNode[i]["Intensity"]) {
    //             Scene->PointLights[LightIndex]->Intensity = SceneDataNode[i]["Intensity"].as<float>();
    //         }
    //         if (SceneDataNode[i]["MaxDistance"]) {
    //             Scene->PointLights[LightIndex]->MaxDistance = SceneDataNode[i]["MaxDistance"].as<float>();
    //         }

            
    //         if (SceneDataNode[i]["ColorRed"] && SceneDataNode[i]["ColorGreen"] && SceneDataNode[i]["ColorBlue"]) {
    //             Scene->PointLights[LightIndex]->Color = glm::vec3(
    //                 SceneDataNode[i]["ColorRed"].as<float>(),
    //                 SceneDataNode[i]["ColorGreen"].as<float>(),
    //                 SceneDataNode[i]["ColorBlue"].as<float>()
    //                 );
    //         }

    //         Scene->PointLights[LightIndex]->Pos = glm::vec3(
    //             SceneDataNode[i]["PosX"].as<float>(),
    //             SceneDataNode[i]["PosY"].as<float>(),
    //             SceneDataNode[i]["PosZ"].as<float>()
    //             );

    //         if (SceneDataNode[i]["CastShadows"]) {
    //             Scene->PointLights[LightIndex]->CastsShadows_ = SceneDataNode[i]["CastShadows"].as<bool>();
    //         }

    //         // Load Attached Scripts
    //         if (SceneDataNode[i]["AttachedScripts"]) {
    //             YAML::Node Scripts = SceneDataNode[i]["AttachedScripts"];
    //             for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
    //                 Scene->PointLights[LightIndex]->AttachedScriptIndexes_.push_back(it->second.as<long>());
    //             }
    //         }

    //     } else if (AssetType == std::string("SpotLight")) {

    //         // Setup Model Pointer In Scene To Work On
    //         Scene->SpotLights.push_back(std::make_shared<ERS_STRUCT_SpotLight>());
    //         int LightIndex = Scene->SpotLights.size() - 1;

    //         Scene->SpotLights[LightIndex]->UserDefinedName = AssetName;

    //         if (SceneDataNode[i]["Intensity"]) {
    //             Scene->SpotLights[LightIndex]->Intensity = SceneDataNode[i]["Intensity"].as<float>();
    //         }
    //         if (SceneDataNode[i]["MaxDistance"]) {
    //             Scene->SpotLights[LightIndex]->MaxDistance = SceneDataNode[i]["MaxDistance"].as<float>();
    //         }
    //         Scene->SpotLights[LightIndex]->CutOff = SceneDataNode[i]["CutOff"].as<float>();

    //         if (SceneDataNode[i]["RollOff"]) {
    //             Scene->SpotLights[LightIndex]->Rolloff = SceneDataNode[i]["RollOff"].as<float>();
    //         }
    //         if (SceneDataNode[i]["ColorRed"] && SceneDataNode[i]["ColorGreen"] && SceneDataNode[i]["ColorBlue"]) {
    //             Scene->SpotLights[LightIndex]->Color = glm::vec3(
    //                 SceneDataNode[i]["ColorRed"].as<float>(),
    //                 SceneDataNode[i]["ColorGreen"].as<float>(),
    //                 SceneDataNode[i]["ColorBlue"].as<float>()
    //                 );
    //         }


    //         Scene->SpotLights[LightIndex]->Pos = glm::vec3(
    //             SceneDataNode[i]["PosX"].as<float>(),
    //             SceneDataNode[i]["PosY"].as<float>(),
    //             SceneDataNode[i]["PosZ"].as<float>()
    //             );
    //         Scene->SpotLights[LightIndex]->Rot = glm::vec3(
    //             SceneDataNode[i]["RotX"].as<float>(),
    //             SceneDataNode[i]["RotY"].as<float>(),
    //             SceneDataNode[i]["RotZ"].as<float>()
    //             );


    //         if (SceneDataNode[i]["CastShadows"]) {
    //             Scene->SpotLights[LightIndex]->CastsShadows_ = SceneDataNode[i]["CastShadows"].as<bool>();
    //         }

    //         // Load Attached Scripts
    //         if (SceneDataNode[i]["AttachedScripts"]) {
    //             YAML::Node Scripts = SceneDataNode[i]["AttachedScripts"];
    //             for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
    //                 Scene->SpotLights[LightIndex]->AttachedScriptIndexes_.push_back(it->second.as<long>());
    //             }
    //         }

    //     } else if (AssetType == std::string("SceneCamera")) {

    //         // Setup Model Pointer In Scene To Work On
    //         Scene->SceneCameras.push_back(std::make_shared<ERS_STRUCT_SceneCamera>());
    //         int SceneCameraIndex = Scene->SceneCameras.size() - 1;

    //         Scene->SceneCameras[SceneCameraIndex]->UserDefinedName_ = AssetName;
    //         Scene->SceneCameras[SceneCameraIndex]->Pos_ = glm::vec3(
    //             SceneDataNode[i]["PosX"].as<float>(),
    //             SceneDataNode[i]["PosY"].as<float>(),
    //             SceneDataNode[i]["PosZ"].as<float>()
    //             );
    //         Scene->SceneCameras[SceneCameraIndex]->Rot_ = glm::vec3(
    //             SceneDataNode[i]["RotX"].as<float>(),
    //             SceneDataNode[i]["RotY"].as<float>(),
    //             SceneDataNode[i]["RotZ"].as<float>()
    //             );

    //         Scene->SceneCameras[SceneCameraIndex]->NearClip_                = SceneDataNode[i]["NearClip"].as<float>();
    //         Scene->SceneCameras[SceneCameraIndex]->FarClip_                 = SceneDataNode[i]["FarClip"].as<float>();
    //         Scene->SceneCameras[SceneCameraIndex]->FOV_                     = SceneDataNode[i]["FOV"].as<float>();
    //         Scene->SceneCameras[SceneCameraIndex]->EnforceAspectRatio_      = SceneDataNode[i]["EnforceAspectRatio"].as<float>();
    //         Scene->SceneCameras[SceneCameraIndex]->AspectRatio_             = SceneDataNode[i]["AspectRatio"].as<float>();
    //         Scene->SceneCameras[SceneCameraIndex]->StreamingPriority_       = SceneDataNode[i]["StreamingPriority"].as<float>();
            

    //         // Load Attached Scripts
    //         if (SceneDataNode[i]["AttachedScripts"]) {
    //             YAML::Node Scripts = SceneDataNode[i]["AttachedScripts"];
    //             for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
    //                 Scene->SceneCameras[SceneCameraIndex]->AttachedScriptIndexes_.push_back(it->second.as<long>());
    //             }
    //         }

    //     } else {
    //         SystemUtils->Logger_->Log(std::string("Unsupported/Unknown Asset Type: ") + AssetType, 9);
    //     }

    // }

    // // Indicate Scene Is Loaded
    // Scene->IsSceneLoaded = true;
    // return true;

}


