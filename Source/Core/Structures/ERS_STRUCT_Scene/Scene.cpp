//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <Scene.h>


static ERS_STRUCT_SceneObject ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType EntityType, unsigned long Index, const std::string& Label) {

    ERS_STRUCT_SceneObject SceneObject;
    SceneObject.EntityType_ = EntityType;
    SceneObject.Type_ = ERS_FUNCTION_GetSceneObjectTypeName(EntityType);
    SceneObject.Index_ = Index;
    SceneObject.EntityID_ = ERS_FUNCTION_CreateSceneEntityID(EntityType, Index);
    SceneObject.Label_ = Label;

    return SceneObject;
}



void ERS_STRUCT_Scene::IndexSceneObjects() {

    // Clear The Vector
    SceneObjects_.erase(SceneObjects_.begin(), SceneObjects_.end());


    // Add Models
    for (unsigned long i = 0; i < Models.size(); i++) {
        SceneObjects_.push_back(ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType::Model, i, std::string("[M] ") + Models[i]->Name));
    }
    
    // Add Lights
    for (unsigned long i = 0; i < SpotLights.size(); i++) {
        SceneObjects_.push_back(ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType::SpotLight, i, std::string("[LS] ") + SpotLights[i]->UserDefinedName));
    }
    for (unsigned long i = 0; i < DirectionalLights.size(); i++) {
        SceneObjects_.push_back(ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType::DirectionalLight, i, std::string("[LD] ") + DirectionalLights[i]->UserDefinedName));
    }
    for (unsigned long i = 0; i < PointLights.size(); i++) {
        SceneObjects_.push_back(ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType::PointLight, i, std::string("[LP] ") + PointLights[i]->UserDefinedName));
    }

    // Add Scene Cameras
    for (unsigned long i = 0; i < SceneCameras.size(); i++) {
        SceneObjects_.push_back(ERS_FUNCTION_CreateSceneObject(ERS_ENUM_SceneObjectType::SceneCamera, i, std::string("[C] ") + SceneCameras[i]->UserDefinedName_));
    }
    

}


ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::GetSceneObject(unsigned long SceneObjectIndex) {

    if (SceneObjectIndex >= SceneObjects_.size()) {
        return nullptr;
    }

    return &SceneObjects_[SceneObjectIndex];
}


const ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::GetSceneObject(unsigned long SceneObjectIndex) const {

    if (SceneObjectIndex >= SceneObjects_.size()) {
        return nullptr;
    }

    return &SceneObjects_[SceneObjectIndex];
}


ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::GetSelectedSceneObject() {

    if (SelectedObject < 0) {
        return nullptr;
    }

    return GetSceneObject(static_cast<unsigned long>(SelectedObject));
}


const ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::GetSelectedSceneObject() const {

    if (SelectedObject < 0) {
        return nullptr;
    }

    return GetSceneObject(static_cast<unsigned long>(SelectedObject));
}


ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::FindSceneObjectByEntityID(std::uint64_t EntityID) {

    for (unsigned long i = 0; i < SceneObjects_.size(); i++) {
        if (SceneObjects_[i].EntityID_ == EntityID) {
            return &SceneObjects_[i];
        }
    }

    return nullptr;
}


const ERS_STRUCT_SceneObject* ERS_STRUCT_Scene::FindSceneObjectByEntityID(std::uint64_t EntityID) const {

    for (unsigned long i = 0; i < SceneObjects_.size(); i++) {
        if (SceneObjects_[i].EntityID_ == EntityID) {
            return &SceneObjects_[i];
        }
    }

    return nullptr;
}
