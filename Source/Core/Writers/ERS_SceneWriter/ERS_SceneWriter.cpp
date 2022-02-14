//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// FIXME: Make template textures added to their own map so they can be reused.
// FIXME: Make dynamic/static models that can each be rotated/translated (dynamically or statically). Then make updateposition functions, etc.

#include <ERS_SceneWriter.h>

SceneWriter::SceneWriter(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing SceneWriter Subsystem", 5);

}

SceneWriter::~SceneWriter() {

    SystemUtils_->Logger_->Log("SceneWriter Destructor Called", 6);

}

void SceneWriter::ProcessScene(std::shared_ptr<ERS_STRUCT_Scene> InputScene, long AssetID) {

    // Convert Scene To YAML Encoded String
    std::string SceneByteString = ProcessScene(InputScene); 

    // Copy Into System IOData Struct
    std::shared_ptr<ERS_STRUCT_IOData> SceneData = std::make_shared<ERS_STRUCT_IOData>();

    SceneData->Data.reset(new unsigned char[SceneByteString.size()]);
    SceneData->Size_B = SceneByteString.size();
    memcpy(SceneData->Data.get(), SceneByteString.c_str(), SceneByteString.size());

    // Write To Storage
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(AssetID, SceneData);

}

std::string SceneWriter::ProcessScene(std::shared_ptr<ERS_STRUCT_Scene> InputScene) {

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
    for (int i = 0; i < InputScene->Models.size(); i++) {

        // Begin Asset Tag
        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;

        // Write Asset Metadata
        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->Models[AssetIndex]->Name;
        Output << YAML::Key << "AssetType" << YAML::Value << "Model";
        Output << YAML::Key << "AssetID" << YAML::Value << InputScene->Models[AssetIndex]->AssetID;

        // Write Asset Position Data
        Output << YAML::Key << "AssetPositionX" << YAML::Value << InputScene->Models[AssetIndex]->ModelPosition[0];
        Output << YAML::Key << "AssetPositionY" << YAML::Value << InputScene->Models[AssetIndex]->ModelPosition[1];
        Output << YAML::Key << "AssetPositionZ" << YAML::Value << InputScene->Models[AssetIndex]->ModelPosition[2];

        Output << YAML::Key << "AssetRotationX" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[0];
        Output << YAML::Key << "AssetRotationY" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[1];
        Output << YAML::Key << "AssetRotationZ" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[2];

        Output << YAML::Key << "AssetScaleX" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[0];
        Output << YAML::Key << "AssetScaleY" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[1];
        Output << YAML::Key << "AssetScaleZ" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[2];

        // Write Asset Texture Data
        Output << YAML::Key << "FlipTextures" << YAML::Value << InputScene->Models[AssetIndex]->FlipTextures;

        // End Map
        Output << YAML::EndMap;

        AssetIndex++;
    }

    for (int i = 0; i < InputScene->Lights.size(); i++) {

        Output << YAML::Key << AssetIndex;
        Output << YAML::BeginMap;


        Output << YAML::Key << "AssetName" << YAML::Value << InputScene->Lights[AssetIndex]->UserDefinedName;
        Output << YAML::Key << "AssetType" << YAML::Value << "Light";
        Output << YAML::Key << "LightType" << YAML::Value << InputScene->Lights[AssetIndex]->LightType;
        Output << YAML::Key << "AdditionalNotes" << YAML::Value << InputScene->Lights[AssetIndex]->UserAdditionalNotes;


        Output << YAML::Key << "PosX" << YAML::Value << InputScene->Lights[AssetIndex]->PosX;
        Output << YAML::Key << "PosY" << YAML::Value << InputScene->Lights[AssetIndex]->PosY;
        Output << YAML::Key << "PosZ" << YAML::Value << InputScene->Lights[AssetIndex]->PosZ;

        Output << YAML::Key << "AssetRotationX" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[0];
        Output << YAML::Key << "AssetRotationY" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[1];
        Output << YAML::Key << "AssetRotationZ" << YAML::Value << InputScene->Models[AssetIndex]->ModelRotation[2];

        Output << YAML::Key << "AssetScaleX" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[0];
        Output << YAML::Key << "AssetScaleY" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[1];
        Output << YAML::Key << "AssetScaleZ" << YAML::Value << InputScene->Models[AssetIndex]->ModelScale[2];


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

