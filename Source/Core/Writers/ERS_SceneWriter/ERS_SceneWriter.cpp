//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <ERS_SceneWriter.h>

SceneWriter::SceneWriter(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing SceneWriter Subsystem", 5);

}

SceneWriter::~SceneWriter() {

    SystemUtils_->Logger_->Log("SceneWriter Destructor Called", 6);

}

void SceneWriter::ProcessScene(ERS_STRUCT_Scene* InputScene, long AssetID) {

    // Convert Scene To YAML Encoded String
    std::string SceneByteString = ProcessScene(InputScene); 

    // Copy Into System IOData Struct
    std::unique_ptr<ERS_STRUCT_IOData> SceneData = std::make_unique<ERS_STRUCT_IOData>();

    SceneData->Data.reset(new unsigned char[SceneByteString.size()]);
    SceneData->Size_B = SceneByteString.size();
    memcpy(SceneData->Data.get(), SceneByteString.c_str(), SceneByteString.size());

    // Write To Storage
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(AssetID, SceneData.get());

}

std::string SceneWriter::ProcessScene(ERS_STRUCT_Scene* InputScene) {

    // Log Scene Write
    SystemUtils_->Logger_->Log(std::string(std::string("Serializing Scene '") + InputScene->SceneName + std::string("'")).c_str(), 4);

    // Create Emitter
    YAML::Emitter Output;

    // Begin Writing
    Output << YAML::BeginMap;

    // Write Metadata
    Output << YAML::Key << "SceneName" << YAML::Value << InputScene->SceneName;
    Output << YAML::Key << "SceneFormatVersion" << YAML::Value << InputScene->SceneFormatVersion;

    // Write SceneData
    Output << YAML::Key << "SceneData";
    Output << YAML::Key << YAML::BeginMap;
    long AssetIndex = 0;

    //---- Write Models ----//
    for (int i = 0; (long)i < (long)InputScene->Models.size(); i++) {

        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;


        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->Models[i]->Name;
        Output << YAML::Key << "AssetType" << YAML::Value << "Model";
        Output << YAML::Key << "AssetID" << YAML::Value << InputScene->Models[i]->AssetID;


        Output << YAML::Key << "AssetPositionX" << YAML::Value << InputScene->Models[i]->ModelPosition[0];
        Output << YAML::Key << "AssetPositionY" << YAML::Value << InputScene->Models[i]->ModelPosition[1];
        Output << YAML::Key << "AssetPositionZ" << YAML::Value << InputScene->Models[i]->ModelPosition[2];

        Output << YAML::Key << "AssetRotationX" << YAML::Value << InputScene->Models[i]->ModelRotation[0];
        Output << YAML::Key << "AssetRotationY" << YAML::Value << InputScene->Models[i]->ModelRotation[1];
        Output << YAML::Key << "AssetRotationZ" << YAML::Value << InputScene->Models[i]->ModelRotation[2];

        Output << YAML::Key << "AssetScaleX" << YAML::Value << InputScene->Models[i]->ModelScale[0];
        Output << YAML::Key << "AssetScaleY" << YAML::Value << InputScene->Models[i]->ModelScale[1];
        Output << YAML::Key << "AssetScaleZ" << YAML::Value << InputScene->Models[i]->ModelScale[2];


        Output << YAML::Key << "FlipTextures" << YAML::Value << InputScene->Models[i]->FlipTextures;


        Output<<YAML::Key<<"AttachedScripts";
        Output<<YAML::Key<<YAML::BeginMap;
        for (unsigned long i = 0; i < InputScene->Models[i]->AttachedScriptIndexes_.size(); i++) {
            Output<<YAML::Key<<i<<YAML::Value<<InputScene->Models[i]->AttachedScriptIndexes_[i];
        }
        Output<<YAML::EndMap;


        Output << YAML::EndMap;
        AssetIndex++;
    }

    //---- Write Directional Lights ----//
    for (int i = 0; (long)i < (long)InputScene->DirectionalLights.size(); i++) {

        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;


        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->DirectionalLights[i]->UserDefinedName;
        Output << YAML::Key << "AssetType" << YAML::Value << "DirectionalLight";


        Output << YAML::Key << "AmbientRed" << YAML::Value << InputScene->DirectionalLights[i]->Ambient[0];
        Output << YAML::Key << "AmbientGreen" << YAML::Value << InputScene->DirectionalLights[i]->Ambient[1];
        Output << YAML::Key << "AmbientBlue" << YAML::Value << InputScene->DirectionalLights[i]->Ambient[2];
        
        Output << YAML::Key << "DiffuseRed" << YAML::Value << InputScene->DirectionalLights[i]->Diffuse[0];
        Output << YAML::Key << "DiffuseGreen" << YAML::Value << InputScene->DirectionalLights[i]->Diffuse[1];
        Output << YAML::Key << "DiffuseBlue" << YAML::Value << InputScene->DirectionalLights[i]->Diffuse[2];

        Output << YAML::Key << "SpecularRed" << YAML::Value << InputScene->DirectionalLights[i]->Specular[0];
        Output << YAML::Key << "SpecularGreen" << YAML::Value << InputScene->DirectionalLights[i]->Specular[1];
        Output << YAML::Key << "SpecularBlue" << YAML::Value << InputScene->DirectionalLights[i]->Specular[2];


        Output << YAML::Key << "PosX" << YAML::Value << InputScene->DirectionalLights[i]->Pos[0];
        Output << YAML::Key << "PosY" << YAML::Value << InputScene->DirectionalLights[i]->Pos[1];
        Output << YAML::Key << "PosZ" << YAML::Value << InputScene->DirectionalLights[i]->Pos[2];

        Output << YAML::Key << "RotX" << YAML::Value << InputScene->DirectionalLights[i]->Rot[0];
        Output << YAML::Key << "RotY" << YAML::Value << InputScene->DirectionalLights[i]->Rot[1];
        Output << YAML::Key << "RotZ" << YAML::Value << InputScene->DirectionalLights[i]->Rot[2];


        Output << YAML::EndMap;
        AssetIndex++;
    }

    //---- Write Point Lights ----//
    for (int i = 0; (long)i < (long)InputScene->PointLights.size(); i++) {

        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;


        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->PointLights[i]->UserDefinedName;
        Output << YAML::Key << "AssetType" << YAML::Value << "PointLight";


        Output << YAML::Key << "AmbientRed" << YAML::Value << InputScene->PointLights[i]->Ambient[0];
        Output << YAML::Key << "AmbientGreen" << YAML::Value << InputScene->PointLights[i]->Ambient[1];
        Output << YAML::Key << "AmbientBlue" << YAML::Value << InputScene->PointLights[i]->Ambient[2];
        
        Output << YAML::Key << "DiffuseRed" << YAML::Value << InputScene->PointLights[i]->Diffuse[0];
        Output << YAML::Key << "DiffuseGreen" << YAML::Value << InputScene->PointLights[i]->Diffuse[1];
        Output << YAML::Key << "DiffuseBlue" << YAML::Value << InputScene->PointLights[i]->Diffuse[2];

        Output << YAML::Key << "SpecularRed" << YAML::Value << InputScene->PointLights[i]->Specular[0];
        Output << YAML::Key << "SpecularGreen" << YAML::Value << InputScene->PointLights[i]->Specular[1];
        Output << YAML::Key << "SpecularBlue" << YAML::Value << InputScene->PointLights[i]->Specular[2];


        Output << YAML::Key << "PosX" << YAML::Value << InputScene->PointLights[i]->Pos[0];
        Output << YAML::Key << "PosY" << YAML::Value << InputScene->PointLights[i]->Pos[1];
        Output << YAML::Key << "PosZ" << YAML::Value << InputScene->PointLights[i]->Pos[2];


        Output << YAML::Key << "RolloffConstant" << YAML::Value << InputScene->PointLights[i]->RolloffConstant;
        Output << YAML::Key << "RolloffLinear" << YAML::Value << InputScene->PointLights[i]->RolloffLinear;
        Output << YAML::Key << "RolloffQuadratic" << YAML::Value << InputScene->PointLights[i]->RolloffQuadratic;


        Output << YAML::EndMap;
        AssetIndex++;
    }

    //---- Write Spot Lights ----//
    for (int i = 0; (long)i < (long)InputScene->SpotLights.size(); i++) {

        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;


        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->SpotLights[i]->UserDefinedName;
        Output << YAML::Key << "AssetType" << YAML::Value << "SpotLight";


        Output << YAML::Key << "AmbientRed" << YAML::Value << InputScene->SpotLights[i]->Ambient[0];
        Output << YAML::Key << "AmbientGreen" << YAML::Value << InputScene->SpotLights[i]->Ambient[1];
        Output << YAML::Key << "AmbientBlue" << YAML::Value << InputScene->SpotLights[i]->Ambient[2];
        
        Output << YAML::Key << "DiffuseRed" << YAML::Value << InputScene->SpotLights[i]->Diffuse[0];
        Output << YAML::Key << "DiffuseGreen" << YAML::Value << InputScene->SpotLights[i]->Diffuse[1];
        Output << YAML::Key << "DiffuseBlue" << YAML::Value << InputScene->SpotLights[i]->Diffuse[2];

        Output << YAML::Key << "SpecularRed" << YAML::Value << InputScene->SpotLights[i]->Specular[0];
        Output << YAML::Key << "SpecularGreen" << YAML::Value << InputScene->SpotLights[i]->Specular[1];
        Output << YAML::Key << "SpecularBlue" << YAML::Value << InputScene->SpotLights[i]->Specular[2];


        Output << YAML::Key << "PosX" << YAML::Value << InputScene->SpotLights[i]->Pos[0];
        Output << YAML::Key << "PosY" << YAML::Value << InputScene->SpotLights[i]->Pos[1];
        Output << YAML::Key << "PosZ" << YAML::Value << InputScene->SpotLights[i]->Pos[2];

        Output << YAML::Key << "RotX" << YAML::Value << InputScene->SpotLights[i]->Rot[0];
        Output << YAML::Key << "RotY" << YAML::Value << InputScene->SpotLights[i]->Rot[1];
        Output << YAML::Key << "RotZ" << YAML::Value << InputScene->SpotLights[i]->Rot[2];


        Output << YAML::Key << "RolloffConstant" << YAML::Value << InputScene->SpotLights[i]->RolloffConstant;
        Output << YAML::Key << "RolloffLinear" << YAML::Value << InputScene->SpotLights[i]->RolloffLinear;
        Output << YAML::Key << "RolloffQuadratic" << YAML::Value << InputScene->SpotLights[i]->RolloffQuadratic;

        Output << YAML::Key << "CutOff" << YAML::Value << InputScene->SpotLights[i]->CutOff;
        Output << YAML::Key << "OuterCutOff" << YAML::Value << InputScene->SpotLights[i]->OuterCutOff;


        Output << YAML::EndMap;
        AssetIndex++;
    }


    // End Writing
    Output << YAML::EndMap;
    Output << YAML::EndMap;


    // Check For Errors
    if (!Output.good()) {
        std::string LogError = "Scene Serialization Error: " + std::string(Output.GetLastError()) + std::string("\n");
        SystemUtils_->Logger_->Log(LogError.c_str(), 8);
    }

    return std::string(Output.c_str());

}

