//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSMesh Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#pragma once


#include <vector>
#include <string>

#include "ShaderManager.h"
#include "2DTexture.h"
#include "Vertex.h"





// Holds The Mesh Object
class ERS_OBJECT_MESH {

    private:

        // OpenGL Handles
        unsigned int VBO;
        unsigned int EBO;

        // Delcare Methods
        void SetupMesh();

    public:

        // Setup Mesh Data
        std::vector<ERS_OBJECT_VERTEX> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<ERS_OBJECT_TEXTURE_2D> Textures;

        // Setup OpenGL Handel
        unsigned int VAO;

        // Define Helper Vars
        bool _HasInitialized = false;


        // Setup Mesh Constructor
        ERS_OBJECT_MESH(std::vector<ERS_OBJECT_VERTEX> Vertices, std::vector<unsigned int> Indices, std::vector<ERS_OBJECT_TEXTURE_2D> Textures) {

            // Populate Data
            this->Vertices = Vertices;
            this->Indices = Indices;
            this->Textures = Textures;

            // Initialize The Mesh
            SetupMesh();

            // Update Helper Bool
            _HasInitialized = true;

        }

        void Draw(ERS_OBJECT_SHADER &Shader);

};
