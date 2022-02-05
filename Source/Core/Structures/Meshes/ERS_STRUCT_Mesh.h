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
#include <memory>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <2DTexture.h>
#include <Vertex.h>





/**
 * @brief This struct contains a mesh object that is a part of the model struct. It is ment for ERS Internal use.
 * 
 */
class ERS_STRUCT_Mesh {

    private:

        unsigned int VBO;
        unsigned int EBO;



    public:

        // Delcare Methods
        void SetupMesh();

        // Setup Mesh Data
        std::vector<ERS_OBJECT_VERTEX> Vertices;
        std::vector<unsigned int> Indices;
        
        std::vector<int> TextureReferences_;
        std::vector<unsigned int> TextureIDs;
        std::vector<std::string> TextureNames;
        bool UseNewSystem = false;
        
        
        long NumberIndices;
        
        // Setup OpenGL Handel
        unsigned int VAO;

        // Define Helper Vars
        bool _HasInitialized = false;




        void Draw(std::shared_ptr<ERS_STRUCT_Shader> Shader);

};
