//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SceneDecoderV1.h>



bool ERS_FUNCTION_DecodeSceneV1(YAML::Node SceneData, ERS_STRUCT_Scene *Scene, ERS_STRUCT_SystemUtils *SystemUtils, ERS_CLASS_ModelLoader* ModelLoader, bool LogEnable) {


    // Grab Metadata
    SystemUtils->Logger_->Log(std::string("Processing Scene '") + Scene->SceneName + "'", 3, LogEnable);
    std::vector<YAML::Node> SceneItems;

    ERS_FUNCTION_GetLong       (SceneData, "SceneFormatVersion", Scene->SceneFormatVersion      );
    ERS_FUNCTION_GetString     (SceneData, "SceneName",          Scene->SceneName               );
    ERS_FUNCTION_GetInt        (SceneData, "ActiveCameraIndex",  Scene->ActiveSceneCameraIndex  );
    ERS_FUNCTION_GetNodeVector (SceneData, "SceneData",          SceneItems                     );

    // Iterate Through Vector To Add Each Asset To Loading Queue Of Requested Type
    for (long i = 0; (long)i < (long)SceneItems.size(); i++) {

        // Get Asset Information
        YAML::Node Item = SceneItems[i];
        std::string AssetName, AssetType;
        ERS_FUNCTION_GetString(Item, "AssetName", AssetName);
        ERS_FUNCTION_GetString(Item, "AssetType", AssetType);


        if (AssetType == "Model") {

            ERS_STRUCT_Model Model;
            ERS_FUNCTION_GetLong       (Item, "AssetID",              Model.AssetID                 );
            ERS_FUNCTION_GetVec3       (Item, "AssetPosition",        Model.ModelPosition           );
            ERS_FUNCTION_GetVec3       (Item, "AssetRotation",        Model.ModelRotation           );
            ERS_FUNCTION_GetVec3       (Item, "AssetScale",           Model.ModelScale              );
            ERS_FUNCTION_GetBool       (Item, "CastDynamicShadows",   Model.CastDynamicShadows_     );
            ERS_FUNCTION_GetBool       (Item, "CastStaticShadows",    Model.CastStaticShadows_      );
            ERS_FUNCTION_GetBool       (Item, "ReceiveShadows",       Model.ReceiveShadows_         );
            ERS_FUNCTION_GetLong       (Item, "ShaderOverrideIndex",  Model.ShaderOverrideIndex_    );
            ERS_FUNCTION_GetString     (Item, "AssetName",            Model.Name                    );
            ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Model.AttachedScriptIndexes_  );

            Scene->Models.push_back(std::make_shared<ERS_STRUCT_Model>(Model));
            ModelLoader->AddModelToLoadingQueue(Scene->Models[Scene->Models.size()-1]);

        } else if (AssetType == std::string("DirectionalLight")) {

            ERS_STRUCT_DirectionalLight Light;
            ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
            ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
            ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
            ERS_FUNCTION_GetVec3       (Item, "Rot",                  Light.Rot                     );
            ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
            ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
            ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
            ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
            Scene->DirectionalLights.push_back(std::make_shared<ERS_STRUCT_DirectionalLight>(Light));

        } else if (AssetType == std::string("PointLight")) {

            ERS_STRUCT_PointLight Light;
            ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
            ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
            ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
            ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
            ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
            ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
            ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
            Scene->PointLights.push_back(std::make_shared<ERS_STRUCT_PointLight>(Light));

        } else if (AssetType == std::string("SpotLight")) {

            ERS_STRUCT_SpotLight Light;
            ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
            ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
            ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
            ERS_FUNCTION_GetVec3       (Item, "Rot",                  Light.Rot                     );
            ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
            ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
            ERS_FUNCTION_GetFloat      (Item, "CutOff",               Light.CutOff                  );
            ERS_FUNCTION_GetFloat      (Item, "RollOff",              Light.Rolloff                 );
            ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
            ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
            Scene->SpotLights.push_back(std::make_shared<ERS_STRUCT_SpotLight>(Light));

        } else if (AssetType == std::string("SceneCamera")) {

            // Setup Model Pointer In Scene To Work On
            Scene->SceneCameras.push_back(std::make_shared<ERS_STRUCT_SceneCamera>());
            int SceneCameraIndex = Scene->SceneCameras.size() - 1;

            Scene->SceneCameras[SceneCameraIndex]->UserDefinedName_ = AssetName;
            Scene->SceneCameras[SceneCameraIndex]->Pos_ = glm::vec3(
                SceneItems[i]["PosX"].as<float>(),
                SceneItems[i]["PosY"].as<float>(),
                SceneItems[i]["PosZ"].as<float>()
                );
            Scene->SceneCameras[SceneCameraIndex]->Rot_ = glm::vec3(
                SceneItems[i]["RotX"].as<float>(),
                SceneItems[i]["RotY"].as<float>(),
                SceneItems[i]["RotZ"].as<float>()
                );

            // Load Attached Scripts
            if (SceneItems[i]["AttachedScripts"]) {
                YAML::Node Scripts = SceneItems[i]["AttachedScripts"];
                for (YAML::const_iterator it=Scripts.begin(); it!=Scripts.end(); ++it) {
                    Scene->SceneCameras[SceneCameraIndex]->AttachedScriptIndexes_.push_back(it->second.as<long>());
                }
            }

        } else {
            SystemUtils->Logger_->Log(std::string("Unsupported/Unknown Asset Type: ") + AssetType, 9);
        }

    }

    // Indicate Scene Is Loaded
    Scene->IsSceneLoaded = true;
    return true;

}


