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

    // Append Model Into Vector Of Models
    //Models_.push_back(Scene);

    Scene_ = Scene;

}

// Render All Models In Buffer
void SceneManager::Render(ERS_OBJECT_SHADER Shader) {
    
    // Iterate Through Models
    for (long i = 0; i < Scene_.Models_.size(); i++) {

        // Get Model Pointer
        ERS_OBJECT_MODEL *Model = &Models_[i];

        // Set Shader Pointer
        Shader.SetMat4("model", Model->GetMat4());

        // Call Draw
        Model->Draw(Shader);
        

    }

}