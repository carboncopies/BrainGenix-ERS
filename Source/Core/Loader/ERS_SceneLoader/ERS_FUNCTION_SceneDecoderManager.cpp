//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_SceneDecoderManager.h>




bool ERS_FUNCTION_DecodeScene(YAML::Node SceneData, ERS_STRUCT_Scene *Scene, ERS_STRUCT_SystemUtils *SystemUtils, bool LogEnable) {

    SystemUtils->Logger_->Log("Decoding ERS Scene", 5, LogEnable);

    // Extract Current Version
    int Version;
    SystemUtils->Logger_->Log("Identifying Scene Format Version", 4, LogEnable);
    if (SceneData["SceneFormatVersion"])

}