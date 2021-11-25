//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <Mesh.h>
#include <2DTexture.h>


/**
 * @brief This structure creates a model object. The model object stores the mesh, textures, and positions. Please see the full list of attrbutes for more information.
 * 
 */
struct ERS_OBJECT_MODEL {

    // Model Data
    std::vector<ERS_OBJECT_MESH> Meshes;
    std::vector<ERS_OBJECT_TEXTURE_2D> Textures_Loaded;
    std::string Directory;

    std::string AssetPath_;

    bool GammaCorrection = false;
    bool HasTexturesLoaded = false;

    // Model Metadata
    glm::vec3 ModelPosition;
    glm::vec3 ModelRotation;
    glm::vec3 ModelScale;


    // Model Position Information
    glm::mat4 ModelLocRotScale_ = glm::mat4(1.0f);


    // Set The Position
    /**
     * @brief Set the Position object (Overloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetPosition(double X, double Y, double Z);
    /**
     * @brief Set the Position object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Position 
     */
    void SetPosition(glm::vec3 Position);


    // Set Rotation
    /**
     * @brief Set the Rotation object (OVerloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetRotation(double X, double Y, double Z);
    /**
     * @brief Set the Rotation object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Rotation 
     */
    void SetRotation(glm::vec3 Rotation);


    // Set Scale
    /**
     * @brief Set the Scale object (OVerloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetScale(double X, double Y, double Z);
    /**
     * @brief Set the Scale object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Scale 
     */
    void SetScale(glm::vec3 Scale);


    // Set LocRotScale
    /**
     * @brief Set the Loc Rot Scale object (Overloaded) Sets the location, rotation, and scale by taking three doubles for each category. (XYZ). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param LocX 
     * @param LocY 
     * @param LocZ 
     * @param RotX 
     * @param RotY 
     * @param RotZ 
     * @param ScaleX 
     * @param ScaleY 
     * @param ScaleZ 
     */
    void SetLocRotScale(double LocX, double LocY, double LocZ, double RotX, double RotY, double RotZ, double ScaleX, double ScaleY, double ScaleZ);
    /**
     * @brief Set the Loc Rot Scale object (Overloaded). Sets the location, rotation, and scale by taking three glm::vec3 variables for positiom, rotation, scale. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Position 
     * @param Rotation 
     * @param Scale 
     */
    void SetLocRotScale(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);

    /**
     * @brief Applies Transformatins Set By Using the Set (Loc/Rot/Scale) Methods.
     * 
     */
    void ApplyTransformations();


    /**
     * @brief Get the Mat 4 object
     * 
     * @return glm::mat4 
     */
    glm::mat4 GetMat4();

    /**
     * @brief Draw Model Using Shader
     * 
     * @param Shader 
     */
    void Draw(ERS_OBJECT_SHADER &Shader);


};



