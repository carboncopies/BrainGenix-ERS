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

    const char* AssetPath_;

    bool GammaCorrection = false;
    bool HasTexturesLoaded = false;


    // Model Position Information
    glm::mat4 ModelLocRotScale_ = glm::vec4(1.0f);


    // Set The Position
    /**
     * @brief Set the Position object (Overloaded). Accepts X,Y,Z Floats.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetPosition(double X, double Y, double Z);
    /**
     * @brief Set the Position object (Overloaded). Accepts glm::vec3(x,y,z).
     * 
     * @param Position 
     */
    void SetPosition(glm::vec3 Position);


    // Set Rotation
    /**
     * @brief Set the Rotation object (OVerloaded). Accepts X,Y,Z Floats.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetRotation(double X, double Y, double Z);
    /**
     * @brief Set the Rotation object (Overloaded). Accepts glm::vec3(x,y,z).
     * 
     * @param Rotation 
     */
    void SetRotation(glm::vec3 Rotation);


    // Set Scale
    /**
     * @brief Set the Scale object (OVerloaded). Accepts X,Y,Z Floats.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetScale(double X, double Y, double Z);
    /**
     * @brief Set the Scale object (Overloaded). Accepts glm::vec3(x,y,z).
     * 
     * @param Scale 
     */
    void SetScale(glm::vec3 Scale);



    // Draw Model
    void Draw(ERS_OBJECT_SHADER &Shader);


};



