//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model manager classes.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#include <ModelManager.h>


// Constructor For ModelManager Class
ModelManager::ModelManager(LoggerClass *Logger) {

    // Copy To Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing ModelManager Instance", 5);

}


// Destructor For ModelManager Class
ModelManager::~ModelManager() {

    // Log Destructor Call
    Logger_->Log("Destructor Called For ModelManager Class", 6);

}


// Add Model Functions (Overloaded)
void ModelManager::AddModel(ERS_OBJECT_MODEL Model) {

    // Append Model Into Vector Of Models
    Models_.push_back(Model);

}

// Render All Models In Buffer
void ModelManager::RenderModels(ERS_OBJECT_SHADER Shader) {
    
    // Iterate Through Models
    for (long i = 0; i < Models_.size(); i++) {

        // Get Model Pointer
        ERS_OBJECT_MODEL *Model = &Models_[i];

        // Set Shader Pointer
        Shader.SetMat4("model", Model->GetMat4());

        // Call Draw
        Model->Draw(Shader);
        

    }

}