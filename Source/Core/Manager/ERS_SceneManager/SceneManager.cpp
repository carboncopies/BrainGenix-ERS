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

    if (Scenes_.empty() || ActiveScene_ < 0 || (unsigned long)ActiveScene_ >= Scenes_.size()) {
        Logger_->Log("Cannot update LocRotScale because the active scene is invalid", 7);
        return;
    }

    if (Scenes_[ActiveScene_]->SceneObjects_.empty()) {
        Logger_->Log("Scene has no models");
        return;
    }

    ApplyLocRotScale(ActiveScene_, Scenes_[ActiveScene_]->SelectedObject, Pos, Rot, Scale);
}

bool ERS_CLASS_SceneManager::GetSelectedLocRotScale(glm::vec3& Pos, glm::vec3& Rot, glm::vec3& Scale, bool& HasRotation, bool& HasScale) {

    if (Scenes_.empty() || ActiveScene_ < 0 || (unsigned long)ActiveScene_ >= Scenes_.size()) {
        return false;
    }

    return GetLocRotScale(ActiveScene_, Scenes_[ActiveScene_]->SelectedObject, Pos, Rot, Scale, HasRotation, HasScale);
}

bool ERS_CLASS_SceneManager::GetLocRotScale(int SceneIndex, unsigned long SceneObjectIndex, glm::vec3& Pos, glm::vec3& Rot, glm::vec3& Scale, bool& HasRotation, bool& HasScale) {

    Pos = glm::vec3(0.0f);
    Rot = glm::vec3(0.0f);
    Scale = glm::vec3(1.0f);
    HasRotation = false;
    HasScale = false;

    if (SceneIndex < 0 || (unsigned long)SceneIndex >= Scenes_.size()) {
        Logger_->Log("Cannot read LocRotScale from invalid scene index", 7);
        return false;
    }

    ERS_STRUCT_Scene* Scene = Scenes_[SceneIndex].get();
    if (Scene->SceneObjects_.empty()) {
        Logger_->Log("Scene has no models");
        return false;
    }

    if (SceneObjectIndex >= Scene->SceneObjects_.size()) {
        Logger_->Log("Selected Scene Object is out of bounds.");
        return false;
    }

    auto& SelectedObject = Scene->SceneObjects_[SceneObjectIndex];

    if (SelectedObject.Type_ == "Model") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->Models.size()) {
            return false;
        }
        Pos = Scene->Models[Index]->ModelPosition;
        Rot = Scene->Models[Index]->ModelRotation;
        Scale = Scene->Models[Index]->ModelScale;
        HasRotation = true;
        HasScale = true;
    } else if (SelectedObject.Type_ == "PointLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->PointLights.size()) {
            return false;
        }
        Pos = Scene->PointLights[Index]->Pos;
    } else if (SelectedObject.Type_ == "DirectionalLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->DirectionalLights.size()) {
            return false;
        }
        Pos = Scene->DirectionalLights[Index]->Pos;
        Rot = Scene->DirectionalLights[Index]->Rot;
        HasRotation = true;
    } else if (SelectedObject.Type_ == "SpotLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->SpotLights.size()) {
            return false;
        }
        Pos = Scene->SpotLights[Index]->Pos;
        Rot = Scene->SpotLights[Index]->Rot;
        HasRotation = true;
    } else if (SelectedObject.Type_ == "SceneCamera") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->SceneCameras.size()) {
            return false;
        }
        Pos = Scene->SceneCameras[Index]->Pos_;
        Rot = Scene->SceneCameras[Index]->Rot_;
        HasRotation = true;
    } else {
        return false;
    }

    return true;
}

bool ERS_CLASS_SceneManager::ApplyLocRotScale(int SceneIndex, unsigned long SceneObjectIndex, glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale) {

    if (SceneIndex < 0 || (unsigned long)SceneIndex >= Scenes_.size()) {
        Logger_->Log("Cannot update LocRotScale on invalid scene index", 7);
        return false;
    }

    ERS_STRUCT_Scene* Scene = Scenes_[SceneIndex].get();
    if (Scene->SceneObjects_.empty()) {
        Logger_->Log("Scene has no models");
        return false;
    }

    if (SceneObjectIndex >= Scene->SceneObjects_.size()) {
        Logger_->Log("Selected Scene Object is out of bounds.");
        return false;
    }

    auto& SelectedObject = Scene->SceneObjects_[SceneObjectIndex];

    if (SelectedObject.Type_ == "Model") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->Models.size()) {
            return false;
        }
        Scene->Models[Index]->SetLocRotScale(Pos, Rot, Scale);
        Scene->Models[Index]->ApplyTransformations();
    } else if (SelectedObject.Type_ == "PointLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->PointLights.size()) {
            return false;
        }
        Scene->PointLights[Index]->Pos = Pos;
    } else if (SelectedObject.Type_ == "DirectionalLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->DirectionalLights.size()) {
            return false;
        }
        Scene->DirectionalLights[Index]->Pos = Pos;
        Scene->DirectionalLights[Index]->Rot = Rot;
    } else if (SelectedObject.Type_ == "SpotLight") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->SpotLights.size()) {
            return false;
        }
        Scene->SpotLights[Index]->Pos = Pos;
        Scene->SpotLights[Index]->Rot = Rot;
    } else if (SelectedObject.Type_ == "SceneCamera") {
        unsigned long Index = SelectedObject.Index_;
        if (Index >= Scene->SceneCameras.size()) {
            return false;
        }
        Scene->SceneCameras[Index]->Pos_ = Pos;
        Scene->SceneCameras[Index]->Rot_ = Rot;
    } else {
        return false;
    }

    return true;
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
