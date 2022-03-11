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
    Scenes_[ActiveScene_]->Models[Scenes_[ActiveScene_]->SelectedModel]->SetLocRotScale(Pos, Rot, Scale);
    Scenes_[ActiveScene_]->Models[Scenes_[ActiveScene_]->SelectedModel]->ApplyTransformations();
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

void ERS_CLASS_SceneManager::Render(ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {
    

    // Update If Meshes Are Transparent Or Not
    for (unsigned long i = 0; i < Scenes_[ActiveScene_]->Models.size(); i++) {
        Scenes_[ActiveScene_]->Models[i]->UpdateMeshTransparency();
    }

    // Get List Of Transparent/Opaque Meshes
    std::vector<ERS_STRUCT_Mesh*> OpaqueMeshes;
    std::vector<glm::mat4> OpaqueModelMatrices;
    std::vector<ERS_STRUCT_Mesh*> TransparentMeshes;
    std::vector<glm::mat4> TransparentModelMatrices;

    for (unsigned long i = 0; i < Scenes_[ActiveScene_]->Models.size(); i++) {

        ERS_STRUCT_Model *Model = Scenes_[ActiveScene_]->Models[i].get();
        glm::mat4 ModelMatrix = Model->GetMat4();
        for (unsigned int i = 0; i < Model->Meshes.size(); i++) {

            ERS_STRUCT_Mesh* Mesh = &Model->Meshes[i];
            if (Mesh->HasTransparency_) {
                TransparentMeshes.push_back(Mesh);
                TransparentModelMatrices.push_back(ModelMatrix);
            } else {
                OpaqueMeshes.push_back(Mesh);
                OpaqueModelMatrices.push_back(ModelMatrix);
            }

        }

    }

    // Draw All Opaque Meshes
    for (unsigned long i = 0; i < OpaqueMeshes.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->DefaultTexture_);
        glActiveTexture(OpenGLDefaults->DefaultTexture_);
        Shader->SetMat4("model", OpaqueModelMatrices[i]);
        OpaqueMeshes[i]->Draw(OpenGLDefaults, Shader);
    }

    // Depth Sort Transparent Meshes
    std::vector<ERS_STRUCT_Mesh*> SortedTransparentMeshes;
    std::vector<glm::mat4> SortedTransparentModelMatrices;
    for (unsigned long i = 0; i < TransparentMeshes.size(); i++) {
        
        ERS_STRUCT_Mesh* Mesh = TransparentMeshes[i];
        std::cout<<glm::to_string(TransparentModelMatrices[i])<<std::endl;
    }

    // Disable Depth Filtering
    glDisable(GL_DEPTH_TEST);

    // Render Transparent Meshes In Right Order
    for (unsigned long i = 0; i < TransparentMeshes.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->DefaultTexture_);
        glActiveTexture(OpenGLDefaults->DefaultTexture_);
        Shader->SetMat4("model", TransparentModelMatrices[i]);
        TransparentMeshes[i]->Draw(OpenGLDefaults, Shader);
    }

    // Enable Depth Filtering
    glEnable(GL_DEPTH_TEST);


    // TODO: Update rendering process
    // should be based around the idea that the models are used to get the meshes to be rendered
    // the meshes are then compiled into two lists to be rendered
    // firstly, there are opaque meshes which are rendered normally (With the depth testing enabled)
    // next, there's the transparent meshes which are sorted by distance on another thread while the opaque meshes are rendering
    // then, these are rendered via depth peeling.

    // A later method would be to implement support for OIT or something fancy like that but this will work for now.  



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


