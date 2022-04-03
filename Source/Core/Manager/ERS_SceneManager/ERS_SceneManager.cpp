//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_SceneManager.h>


ERS_CLASS_SceneManager::ERS_CLASS_SceneManager(ERS_CLASS_LoggingSystem* Logger) {

    Logger_ = Logger;

    Logger_->Log("Initializing ERS_CLASS_SceneManager Instance", 5);

}

ERS_CLASS_SceneManager::~ERS_CLASS_SceneManager() {

    Logger_->Log("Destructor Called For ERS_CLASS_SceneManager Class", 6);

}

void ERS_CLASS_SceneManager::UpdateLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale) {

    unsigned long SelectedObject = Scenes_[ActiveScene_]->SelectedObject;

    if (Scenes_[ActiveScene_]->SceneObjects_[SelectedObject].Type_ == std::string("Model")) {
        unsigned long Index = Scenes_[ActiveScene_]->SceneObjects_[SelectedObject].Index_;
        Scenes_[ActiveScene_]->Models[Index]->SetLocRotScale(Pos, Rot, Scale);
        Scenes_[ActiveScene_]->Models[Index]->ApplyTransformations();
    } else if (Scenes_[ActiveScene_]->SceneObjects_[Scenes_[ActiveScene_]->SelectedObject].Type_ == std::string("PointLight")) {
        unsigned long Index = Scenes_[ActiveScene_]->SceneObjects_[SelectedObject].Index_;
        Scenes_[ActiveScene_]->PointLights[Index]->Pos = Pos;
    } else if (Scenes_[ActiveScene_]->SceneObjects_[Scenes_[ActiveScene_]->SelectedObject].Type_ == std::string("DirectionalLight")) {
        unsigned long Index = Scenes_[ActiveScene_]->SceneObjects_[SelectedObject].Index_;
        Scenes_[ActiveScene_]->DirectionalLights[Index]->Pos = Pos;
        Scenes_[ActiveScene_]->DirectionalLights[Index]->Rot = Rot;
    } else if (Scenes_[ActiveScene_]->SceneObjects_[Scenes_[ActiveScene_]->SelectedObject].Type_ == std::string("SpotLight")) {
        unsigned long Index = Scenes_[ActiveScene_]->SceneObjects_[SelectedObject].Index_;
        Scenes_[ActiveScene_]->SpotLights[Index]->Pos = Pos;
        Scenes_[ActiveScene_]->SpotLights[Index]->Rot = Rot;
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

    // Iterate Through Scenes, Check Name Against Target
    int TargetSceneIndex;
    bool TargetSceneFound = false;

    for (TargetSceneIndex = 0; (long)TargetSceneIndex < (long)Scenes_.size(); TargetSceneIndex++) {

        // Get Scene Name
        std::string SceneName = Scenes_[TargetSceneIndex]->SceneName;

        // Check Scene Name
        if (SceneName == TargetSceneName) {
            TargetSceneFound = true;
            break;
        }

    }

    // Check Success/Fail
    if (!TargetSceneFound) {

        // Log Error
        Logger_->Log(std::string(std::string("Failed To Set Active Scene To: ") + TargetSceneName + std::string(" Because It Isn't In The Scenes_ Vector")).c_str(), 7); 

        return false;
    } 

    // Update Target Scene
    ActiveScene_ = TargetSceneIndex;

    return true;
    

}

void ERS_CLASS_SceneManager::AddPointLight() {

    std::shared_ptr<ERS_STRUCT_PointLight> Light = std::make_shared<ERS_STRUCT_PointLight>();

    Light->UserDefinedName = "New Point Light";
    Light->Ambient = glm::vec3(0.0f);
    Light->Diffuse = glm::vec3(0.5f);
    Light->Specular = glm::vec3(0.5f);

    Light->RolloffConstant = 1.0f;
    Light->RolloffLinear = 0.09f;
    Light->RolloffQuadratic = 0.064f;

    Scenes_[ActiveScene_]->PointLights.push_back(Light);
    Scenes_[ActiveScene_]->IndexSceneObjects();

}

void ERS_CLASS_SceneManager::AddDirectionalLight() {

    std::shared_ptr<ERS_STRUCT_DirectionalLight> Light = std::make_shared<ERS_STRUCT_DirectionalLight>();

    Light->UserDefinedName = "New Directional Light";
    Light->Ambient = glm::vec3(0.0f);
    Light->Diffuse = glm::vec3(0.5f);
    Light->Specular = glm::vec3(0.5f);

    Scenes_[ActiveScene_]->DirectionalLights.push_back(Light);
    Scenes_[ActiveScene_]->IndexSceneObjects();

}

void ERS_CLASS_SceneManager::AddSpotLight() {

    std::shared_ptr<ERS_STRUCT_SpotLight> Light = std::make_shared<ERS_STRUCT_SpotLight>();

    Light->UserDefinedName = "New Spot Light";
    Light->Ambient = glm::vec3(0.0f);
    Light->Diffuse = glm::vec3(0.5f);
    Light->Specular = glm::vec3(0.5f);
    
    Light->RolloffConstant = 1.0f;
    Light->RolloffLinear = 0.09f;
    Light->RolloffQuadratic = 0.064f;

    Light->CutOff = 0.970f;
    Light->OuterCutOff = 0.960f;

    Scenes_[ActiveScene_]->SpotLights.push_back(Light);
    Scenes_[ActiveScene_]->IndexSceneObjects();

}