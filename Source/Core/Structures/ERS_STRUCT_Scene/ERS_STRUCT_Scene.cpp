//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Scene.h>



void ERS_STRUCT_Scene::IndexSceneObjects() {

    // Clear The Vector
    SceneObjects_.erase(SceneObjects_.begin(), SceneObjects_.end());


    // Add Models
    for (unsigned long i = 0; i < Models.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("Model");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[M] ") + Models[i]->Name;
        SceneObjects_.push_back(SceneObject);
    }
    
    // Add Lights
    for (unsigned long i = 0; i < SpotLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("SpotLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + SpotLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }
    for (unsigned long i = 0; i < DirectionalLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("DirectionalLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + DirectionalLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }
    for (unsigned long i = 0; i < PointLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("PointLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + PointLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }

}