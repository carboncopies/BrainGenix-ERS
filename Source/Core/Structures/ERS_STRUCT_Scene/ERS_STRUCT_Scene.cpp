//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_STRUCT_Scene.h>



void ERS_STRUCT_Scene::IndexSceneObjects(ERS_STRUCT_Scene* Scene) {

    // Clear The Vector
    SceneObjects_.erase(SceneObjects_.begin(), SceneObjects_.end());


    // Add Models
    for (unsigned long i = 0; i < Scene->Models.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("Model");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[M] ") + Scene->Models[i]->Name;
        SceneObjects_.push_back(SceneObject);
    }
    
    // Add Lights
    for (unsigned long i = 0; i < Scene->SpotLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("SpotLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + Scene->SpotLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }
    for (unsigned long i = 0; i < Scene->DirectionalLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("DirectionalLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + Scene->DirectionalLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }
    for (unsigned long i = 0; i < Scene->PointLights.size(); i++) {
        ERS_STRUCT_SceneObject SceneObject;
        SceneObject.Type_ = std::string("PointLight");
        SceneObject.Index_ = i;
        SceneObject.Label_ = std::string("[L] ") + Scene->PointLights[i]->UserDefinedName;
        SceneObjects_.push_back(SceneObject);
    }

}