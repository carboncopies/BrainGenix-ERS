//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 


#include "Model.h"


// Draw Model
void ERS_OBJECT_MODEL::Draw(ERS_OBJECT_SHADER* Shader) {

    // Draw All Meshes
    for (unsigned int i=0; i<Meshes.size(); i++) {
        Meshes[i].Draw(Shader);
    }

}


// Set Position Functions
void ERS_OBJECT_MODEL::SetPosition(double X, double Y, double Z) {

    // Convert Doubles GLM Vec3
    glm::vec3 Position = glm::vec3(X, Y, Z);

    // Set Position to Pos
    ModelPosition = Position;

}

void ERS_OBJECT_MODEL::SetPosition(glm::vec3 Position) {

    // Set Position to Pos
    ModelPosition = Position;

}

// Set Rotation Functions
void ERS_OBJECT_MODEL::SetRotation(double X, double Y, double Z) {

    // Set Rotation to Pos
    ModelRotation = glm::vec3((float)X, (float)Y, (float)Z);

}

void ERS_OBJECT_MODEL::SetRotation(glm::vec3 Rotation) {

    // Set Rotation to Pos
    ModelRotation = Rotation;

}


// Set Scale Functions
void ERS_OBJECT_MODEL::SetScale(double X, double Y, double Z) {

    // Convert Doubles GLM Vec3
    glm::vec3 Scale = glm::vec3(X, Y, Z);

    // Set Scale to Pos
    ModelScale = Scale;

}

void ERS_OBJECT_MODEL::SetScale(glm::vec3 Scale) {

    // Set Scale to Pos
    ModelScale = Scale;

}


// Set LocRotScale Functions
void ERS_OBJECT_MODEL::SetLocRotScale(double LocX, double LocY, double LocZ, double RotX, double RotY, double RotZ, double ScaleX, double ScaleY, double ScaleZ) {

    // Calculate Loc, Rot, Scale Vecs
    glm::vec3 Position = glm::vec3(LocX, LocY, LocZ);
    glm::vec3 Rotation = glm::vec3(RotX, RotY, RotZ);
    glm::vec3 Scale = glm::vec3(ScaleX, ScaleY, ScaleZ);

    // Set Vecs
    ModelPosition = Position;
    ModelRotation = glm::normalize(Rotation);
    ModelScale = Scale;

}


void ERS_OBJECT_MODEL::SetLocRotScale(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale) {

    // Set Vecs
    ModelPosition = Position;
    ModelRotation = glm::normalize(Rotation);
    ModelScale = Scale;

}


// Apply Transformations
bool ERS_OBJECT_MODEL::ApplyTransformations() {

    // Check If Template Model
    //if (!IsTemplateModel) {

        // Reset ModelLocRotScale
        ModelLocRotScale_ = SourceModelLocRotScale_;

        // Apply Transforms
        ModelLocRotScale_ = glm::translate(ModelLocRotScale_, ModelPosition);
        ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[0]), glm::vec3(1, 0, 0));
        ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[1]), glm::vec3(0, 1, 0));
        ModelLocRotScale_ = glm::rotate(ModelLocRotScale_, glm::radians(ModelRotation[2]), glm::vec3(0, 0, 1));
        ModelLocRotScale_ = glm::scale(ModelLocRotScale_, ModelScale);

        // Return Success
        return true;

    //} else {

        // Return Failure
        //return false;

    //}

}

// Get Mat4
glm::mat4 ERS_OBJECT_MODEL::GetMat4() {

    // Return Mat4 Projection Matrix
    return ModelLocRotScale_;

}