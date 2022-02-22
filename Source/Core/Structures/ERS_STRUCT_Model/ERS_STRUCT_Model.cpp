//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#include "ERS_STRUCT_Model.h"


void ERS_STRUCT_Model::Draw(std::shared_ptr<ERS_STRUCT_Shader> Shader) {

    // Only Draw When Fully Ready
    if (FullyReady) {

        glBindTexture(GL_TEXTURE_2D, 1);
        glActiveTexture(1);

        // Draw All Meshes
        for (unsigned int i=0; i<Meshes.size(); i++) {
            Meshes[i].Draw(Shader);
        }


        glBindTexture(GL_TEXTURE_2D, 1);
        glActiveTexture(1);


    }

}


void ERS_STRUCT_Model::SetPosition(double X, double Y, double Z) {

    glm::vec3 Position = glm::vec3(X, Y, Z);
    ModelPosition = Position;

}

void ERS_STRUCT_Model::SetPosition(glm::vec3 Position) {

    ModelPosition = Position;

}

void ERS_STRUCT_Model::SetRotation(double X, double Y, double Z) {

    ModelRotation = glm::vec3((float)X, (float)Y, (float)Z);

}

void ERS_STRUCT_Model::SetRotation(glm::vec3 Rotation) {

    ModelRotation = Rotation;

}


void ERS_STRUCT_Model::SetScale(double X, double Y, double Z) {

    glm::vec3 Scale = glm::vec3(X, Y, Z);
    ModelScale = Scale;

}

void ERS_STRUCT_Model::SetScale(glm::vec3 Scale) {

    ModelScale = Scale;

}


void ERS_STRUCT_Model::SetLocRotScale(double LocX, double LocY, double LocZ, double RotX, double RotY, double RotZ, double ScaleX, double ScaleY, double ScaleZ) {

    glm::vec3 Position = glm::vec3(LocX, LocY, LocZ);
    glm::vec3 Rotation = glm::vec3(RotX, RotY, RotZ);
    glm::vec3 Scale = glm::vec3(ScaleX, ScaleY, ScaleZ);

    ModelPosition = Position;
    ModelRotation = Rotation;
    ModelScale = Scale;

}


void ERS_STRUCT_Model::SetLocRotScale(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale) {

    ModelPosition = Position;
    ModelRotation = Rotation;
    ModelScale = Scale;

}


bool ERS_STRUCT_Model::ApplyTransformations() {

    // Reset ModelLocRotScale
    ModelLocRotScale_ = SourceModelLocRotScale_;


    // Apply Transforms
    ModelLocRotScale_ = glm::translate(ModelLocRotScale_, ModelPosition);
    ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[0]), glm::vec3(1, 0, 0));
    ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[1]), glm::vec3(0, 1, 0));
    ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[2]), glm::vec3(0, 0, 1));
    ModelLocRotScale_ = glm::scale(ModelLocRotScale_, ModelScale);

    
    return true;

}

glm::mat4 ERS_STRUCT_Model::GetMat4() {

    return ModelLocRotScale_;

}