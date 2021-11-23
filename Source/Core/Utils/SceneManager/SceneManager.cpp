//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene manager classes.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#include <SceneManager.h>


// Constructor For SceneManager Class
SceneManager::SceneManager(LoggerClass *Logger) {

    // Copy To Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing SceneManager Instance", 5);

}


// Destructor For SceneManager Class
SceneManager::~SceneManager() {

    // Log Destructor Call
    Logger_->Log("Destructor Called For SceneManager Class", 6);

}


// Add Model Functions (Overloaded)
void SceneManager::AddScene(ERS_OBJECT_SCENE Scene) {

    // Append Scene To Scenes Model
    Scenes_.push_back(Scene);

}

// Render All Models In Buffer
void SceneManager::Render(ERS_OBJECT_SHADER Shader) {
    
    // Iterate Through Models
    for (long i = 0; i < Scenes_[ActiveScene_].Models.size(); i++) {

        // Get Model Pointer
        ERS_OBJECT_MODEL *Model = &Scenes_[ActiveScene_].Models[i];

        // Set Shader Pointer
        Shader.SetMat4("model", Model->GetMat4());

        // Call Draw
        Model->Draw(Shader);
        

    }

}

// SetActiveScene (Overloaded, int Version)
bool SceneManager::SetActiveScene(int SceneIndex) {

    // Check SceneIndex Validity
    if (SceneIndex < 0 || SceneIndex > Scenes_.size()-1) {
        return false;
    }

    // Update SceneIndex
    ActiveScene_ = SceneIndex;

}

// SetActiveScene (Overloaded, std::string Version)
bool SceneManager::SetActiveScene(std::string TargetSceneName) {

    // Iterate Through Scenes, Check Name Against Target
    int TargetSceneIndex = 0;
    bool TargetSceneFound = false;

    for (TargetSceneIndex < Scenes_.size()-1; TargetSceneIndex++) {

        // Get Scene Name
        std::string SceneName = Scenes_[TargetSceneIndex].SceneName;

        // Check Scene Name
        if (SceneName == TargetSceneName) {
            TargetSceneFound = true;
            break;
        }

    }

    // Check Success/Fail
    if (!TargetSceneFound) {
        return false;
    } 

    // Update Target Scene
    ActiveScene_ = TargetSceneIndex;

    // Return Success
    return true;
    

}