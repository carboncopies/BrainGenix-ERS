//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SceneDecoderManager.h>




bool ERS_FUNCTION_DecodeScene(YAML::Node SceneData, ERS_STRUCT_Scene *Scene, ERS_STRUCT_SystemUtils *SystemUtils, ERS_CLASS_ModelLoader* ModelLoader, bool LogEnable) {

    SystemUtils->Logger_->Log("Decoding ERS Scene", 5, LogEnable);

    // Extract Current Version
    int Version = 0;
    SystemUtils->Logger_->Log("Identifying Scene Format Version", 4, LogEnable);
    if (SceneData["SceneFormatVersion"]) {
        Version = SceneData["SceneFormatVersion"].as<int>();
    } else {
        SystemUtils->Logger_->Log("Unable To Find Metadata Tag For 'SceneFormatVersion', Unable To Identify Version", 9);
        return false;
    }

    // Attempt Decoding With Known Decoding Systems
    if (Version == 1) {
        return ERS_FUNCTION_DecodeSceneV1(SceneData, Scene, SystemUtils, ModelLoader, LogEnable);
    } else if (Version == 2) {
        return ERS_FUNCTION_DecodeSceneV2(SceneData, Scene, SystemUtils, ModelLoader, LogEnable);        
    } else if (Version == 3) {
        return ERS_FUNCTION_DecodeSceneV3(SceneData, Scene, SystemUtils, ModelLoader, LogEnable);
    }

}