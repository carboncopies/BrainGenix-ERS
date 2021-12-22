//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSMesh Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>

// Internal Libraries (BG convention: use <> instead of "")
#include <Shader.h>
#include <2DTexture.h>
#include <Vertex.h>





// Holds The Mesh Object
class ERS_OBJECT_MESH {

    private:

        // OpenGL Handles
        unsigned int VBO;
        unsigned int EBO;



    public:

        // Delcare Methods
        void SetupMesh();

        // Setup Mesh Data
        std::vector<ERS_OBJECT_VERTEX> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<ERS_OBJECT_TEXTURE_2D> Textures;
        
        
        std::vector<int> TextureReferences_;
        std::vector<unsigned int> TextureIDs;
        std::vector<std::string> TextureNames;
        bool UseNewSystem = false;
        
        
        long NumberIndices;
        
        // Setup OpenGL Handel
        unsigned int VAO;

        // Define Helper Vars
        bool _HasInitialized = false;




        void Draw(std::shared_ptr<ERS_OBJECT_SHADER> Shader);

};
