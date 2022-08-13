//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SceneDecoderV3.h>


bool ERS_FUNCTION_DecodeSceneV3(YAML::Node SceneData, ERS_STRUCT_Scene *Scene, ERS_STRUCT_SystemUtils *SystemUtils, ERS_CLASS_ModelLoader* ModelLoader, bool LogEnable) {

    // Init
    bool Success = true;
    SystemUtils->Logger_->Log(std::string("Processing Scene '") + Scene->SceneName + "' With Decoder Version 3", 3, LogEnable);

    // Grab Metadata
    std::vector<YAML::Node> Models, PointLights, SpotLights, DirectionalLights, SceneCameras;
    Success &= ERS_FUNCTION_GetLong       (SceneData, "SceneFormatVersion", Scene->SceneFormatVersion      );
    Success &= ERS_FUNCTION_GetString     (SceneData, "SceneName",          Scene->SceneName               );
    Success &= ERS_FUNCTION_GetInt        (SceneData, "ActiveCameraIndex",  Scene->ActiveSceneCameraIndex  );
    Success &= ERS_FUNCTION_GetNodeVector (SceneData, "Models",             Models                         );
    Success &= ERS_FUNCTION_GetNodeVector (SceneData, "PointLights",        PointLights                    );
    Success &= ERS_FUNCTION_GetNodeVector (SceneData, "SpotLights",         SpotLights                     );
    Success &= ERS_FUNCTION_GetNodeVector (SceneData, "DirectionalLights",  DirectionalLights              );
    Success &= ERS_FUNCTION_GetNodeVector (SceneData, "SceneCameras",       SceneCameras                   );


    for (unsigned int i = 0; i < Models.size(); i++) {

        YAML::Node Item = Models[i];
        ERS_STRUCT_Model Model;
        Success &= ERS_FUNCTION_GetLong       (Item, "AssetID",              Model.AssetID                 );
        Success &= ERS_FUNCTION_GetVec3       (Item, "AssetPosition",        Model.ModelPosition           );
        Success &= ERS_FUNCTION_GetVec3       (Item, "AssetRotation",        Model.ModelRotation           );
        Success &= ERS_FUNCTION_GetVec3       (Item, "AssetScale",           Model.ModelScale              );
        Success &= ERS_FUNCTION_GetBool       (Item, "CastDynamicShadows",   Model.CastDynamicShadows_     );
        Success &= ERS_FUNCTION_GetBool       (Item, "CastStaticShadows",    Model.CastStaticShadows_      );
        Success &= ERS_FUNCTION_GetBool       (Item, "ReceiveShadows",       Model.ReceiveShadows_         );
        Success &= ERS_FUNCTION_GetLong       (Item, "ShaderOverrideIndex",  Model.ShaderOverrideIndex_    );
        Success &= ERS_FUNCTION_GetString     (Item, "AssetName",            Model.Name                    );
        Success &= ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Model.AttachedScriptIndexes_  );

        Scene->Models.push_back(std::make_shared<ERS_STRUCT_Model>(Model));
        ModelLoader->AddModelToLoadingQueue(Scene->Models[Scene->Models.size()-1]);

    }

    for (unsigned int i = 0; i < PointLights.size(); i++) {

        YAML::Node Item = Models[i];
        ERS_STRUCT_PointLight Light;
        Success &= ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
        Success &= ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
        Success &= ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
        Success &= ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
        Success &= ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
        Success &= ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
        Scene->PointLights.push_back(std::make_shared<ERS_STRUCT_PointLight>(Light));
    }
    
    for (unsigned int i = 0; i < SpotLights.size(); i++) {

        YAML::Node Item = Models[i];
        ERS_STRUCT_SpotLight Light;
        Success &= ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
        Success &= ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Rot",                  Light.Rot                     );
        Success &= ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
        Success &= ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
        Success &= ERS_FUNCTION_GetFloat      (Item, "CutOff",               Light.CutOff                  );
        Success &= ERS_FUNCTION_GetFloat      (Item, "RollOff",              Light.Rolloff                 );
        Success &= ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
        Success &= ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
        Scene->SpotLights.push_back(std::make_shared<ERS_STRUCT_SpotLight>(Light));

    }

    for (unsigned int i = 0; i < DirectionalLights.size(); i++) {

        YAML::Node Item = Models[i];
        ERS_STRUCT_DirectionalLight Light;
        Success &= ERS_FUNCTION_GetString     (Item, "AssetName",            Light.UserDefinedName         );
        Success &= ERS_FUNCTION_GetVec3Color  (Item, "Color",                Light.Color                   );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Pos",                  Light.Pos                     );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Rot",                  Light.Rot                     );
        Success &= ERS_FUNCTION_GetFloat      (Item, "Intensity",            Light.Intensity               );
        Success &= ERS_FUNCTION_GetFloat      (Item, "MaxDistance",          Light.MaxDistance             );
        Success &= ERS_FUNCTION_GetBool       (Item, "CastShadows",          Light.CastsShadows_           );
        Success &= ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Light.AttachedScriptIndexes_  );
        Scene->DirectionalLights.push_back(std::make_shared<ERS_STRUCT_DirectionalLight>(Light));

    }

    for (unsigned int i = 0; i < SceneCameras.size(); i++) {

        YAML::Node Item = Models[i];
        ERS_STRUCT_SceneCamera Camera;
        Success &= ERS_FUNCTION_GetString     (Item, "AssetName",            Camera.UserDefinedName_       );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Pos",                  Camera.Pos_                   );
        Success &= ERS_FUNCTION_GetVec3       (Item, "Rot",                  Camera.Rot_                   );
        Success &= ERS_FUNCTION_GetFloat      (Item, "NearClip",             Camera.NearClip_              );
        Success &= ERS_FUNCTION_GetFloat      (Item, "FarClip",              Camera.FarClip_               );
        Success &= ERS_FUNCTION_GetFloat      (Item, "FOV",                  Camera.FOV_                   );
        Success &= ERS_FUNCTION_GetBool       (Item, "EnforceAspectRatio",   Camera.EnforceAspectRatio_    );
        Success &= ERS_FUNCTION_GetFloat      (Item, "AspectRatio",          Camera.AspectRatio_           );
        Success &= ERS_FUNCTION_GetInt        (Item, "StreamingPriority",    Camera.StreamingPriority_     );
        Success &= ERS_FUNCTION_GetLongVector (Item, "AttachedScripts",      Camera.AttachedScriptIndexes_ );
        Scene->SceneCameras.push_back(std::make_shared<ERS_STRUCT_SceneCamera>(Camera));

    }



    // Indicate Scene Is Loaded
    Scene->IsSceneLoaded = Success;
    return Success;
}


