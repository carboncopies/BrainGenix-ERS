//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_GUI_FUNCTION_DuplicatePointLight.h>


void GUI_Windowutil_DuplicatePointLight(ERS_CLASS_SceneManager* SceneManager, int SceneIndex, int PointLightIndex) {

    // Get Current PointLight
    ERS_STRUCT_PointLight NewPointLight = *SceneManager->Scenes_[SceneIndex]->PointLights[PointLightIndex];

    // Update Name
    std::string CurrentName = NewPointLight.Name;
    std::string NewName = CurrentName + std::string(" - Copy");
    NewPointLight.Name = NewName;


    // Add To SceneManager
    SceneManager->Scenes_[SceneIndex]->PointLights.push_back(std::make_shared<ERS_STRUCT_PointLight>(NewPointLight));

}