//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Windowutil_DuplicateModel.h>


void GUI_Windowutil_DuplicateModel(std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, int SceneIndex, int ModelIndex) {

    // Get Current Model
    ERS_STRUCT_Model NewModel = *SceneManager->Scenes_[SceneIndex]->Models[ModelIndex];

    // Update Name
    std::string CurrentName = NewModel.Name;
    std::string NewName = CurrentName + std::string(" - Copy");
    NewModel.Name = NewName;


    // Add To SceneManager
    SceneManager->Scenes_[SceneIndex]->Models.push_back(std::make_shared<ERS_STRUCT_Model>(NewModel));

}