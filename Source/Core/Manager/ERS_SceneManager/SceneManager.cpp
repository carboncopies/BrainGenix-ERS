//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <SceneManager.h>


ERS_CLASS_SceneManager::ERS_CLASS_SceneManager(BG::Common::Logger::LoggingSystem* Logger) {

    Logger_ = Logger;

    Logger_->Log("Initializing ERS_CLASS_SceneManager Instance", 5);

}

ERS_CLASS_SceneManager::~ERS_CLASS_SceneManager() {

    Logger_->Log("Destructor Called For ERS_CLASS_SceneManager Class", 6);

}

void ERS_CLASS_SceneManager::UpdateLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale) {

    if (Scenes_[ActiveScene_]->SceneObjects_.empty()) {
        Logger_->Log("Scene has no models");
        return; 
    }

    unsigned long SelectedObject = Scenes_[ActiveScene_]->SelectedObject;

    if (SelectedObject >= Scenes_[ActiveScene_]->SceneObjects_.size()) {
        Logger_->Log("Selected Scene Object is out of bounds.");
        return; 
    }

    auto& selectedObject = Scenes_[ActiveScene_]->SceneObjects_[SelectedObject];

    if (selectedObject.Type_ == "Model") {
        unsigned long Index = selectedObject.Index_;
        Scenes_[ActiveScene_]->Models[Index]->SetLocRotScale(Pos, Rot, Scale);
        Scenes_[ActiveScene_]->Models[Index]->ApplyTransformations();
    } else if (selectedObject.Type_ == "PointLight") {
        unsigned long Index = selectedObject.Index_;
        Scenes_[ActiveScene_]->PointLights[Index]->Pos = Pos;
    } else if (selectedObject.Type_ == "DirectionalLight" || selectedObject.Type_ == "SpotLight") {
        unsigned long Index = selectedObject.Index_;
        Scenes_[ActiveScene_]->DirectionalLights[Index]->Pos = Pos;
        Scenes_[ActiveScene_]->DirectionalLights[Index]->Rot = Rot;
    } else if (selectedObject.Type_ == "SceneCamera") {
        unsigned long Index = selectedObject.Index_;
        Scenes_[ActiveScene_]->SceneCameras[Index]->Pos_ = Pos;
        Scenes_[ActiveScene_]->SceneCameras[Index]->Rot_ = Rot;
    }
}


bool ERS_CLASS_SceneManager::AddScene(ERS_STRUCT_Scene Scene) {

    // Check If Scene Isn't Ready
    if (!Scene.IsSceneLoaded) {

        // Log Issue
        Logger_->Log("Failed To Add Scene To Buffer, Scene Isn't Yet Loaded!", 6);

        return false;
    }

    // Append Scene To Scenes Model
    Scenes_.push_back(std::make_unique<ERS_STRUCT_Scene>(Scene));

    return true;

}

bool ERS_CLASS_SceneManager::SetActiveScene(int SceneIndex) {

    // Check SceneIndex Validity
    if (SceneIndex < 0 || (long)SceneIndex > (long)Scenes_.size()-1) {

        // Log Scene Switch Error
        Logger_->Log(std::string(std::string("Failed To Set Active Scene To Index: ") + std::to_string(SceneIndex) + std::string(" Because Scenes_ Only Has") + std::to_string(Scenes_.size()-1) + std::string(" Elements")).c_str(), 7); 

        return false;
    }

    // Update SceneIndex
    ActiveScene_ = SceneIndex;


    return true;

}

bool ERS_CLASS_SceneManager::SetActiveScene(std::string TargetSceneName) {

    // Create an unordered_map to store scene names and their indices
    std::unordered_map<std::string, int> SceneNameToIndex;

   // Populate the unordered_map with scene names and indices
    for (int i = 0; i < Scenes_.size(); i++) {
        SceneNameToIndex[Scenes_[i]->SceneName] = i;
    }

    // Find the target scene index in the unordered_map
    auto TargetName = SceneNameToIndex.find(TargetSceneName);

    // Check if the target scene was found
    if (TargetName == SceneNameToIndex.end()) {
        Logger_->Log(std::string("Failed To Set Active Scene To: " + TargetSceneName + " Because TargetName Isn't In The Scenes_ Vector").c_str(), 7); 
        return false;
    }

    // Update the ActiveScene_ wTargetNameh the target scene index
    ActiveScene_ = TargetName->second;

    return true;
}
