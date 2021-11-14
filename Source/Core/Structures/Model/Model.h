//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Structures/Meshes/Mesh.h"
#include "Core/Structures/Textures/2DTexture.h"
#include "Core/Structures/Vertex/Vertex.h"
#include "Core/Loader/Image/FileIO.h"


struct ImageFileObject {

    // Declare Member Variables
    BYTE *MemoryBuffer;
    struct stat Buffer;
    int Result;


    // Load File Into Mem
    bool LoadImage(const char* FilePath) { // Loads Image Into Memory Buffer, Returns True On Success, False On Failure

        // Get File Stats
        Result = stat(FilePath, &Buffer);
        if (Result == 0) {

            MemoryBuffer = (BYTE*)malloc(Buffer.st_size * sizeof(BYTE));
            if (MemoryBuffer) {

                FILE *Stream = fopen(FilePath, "rb");
                if (Stream) {

                    // Read File Data
                    fread(MemoryBuffer, sizeof(BYTE), Buffer.st_size, Stream);
                    fclose(Stream);

                    return true;

                }
            }
        }

        // Return Fail
        return false;

    }
    
    // Free Memory
    void FreeMemory() {
        free(MemoryBuffer);
    }


};

class ERS_OBJECT_MODEL {


    public:

        // Model Data
        std::vector<ERS_OBJECT_MESH> Meshes;
        std::vector<ERS_OBJECT_TEXTURE_2D> Textures_Loaded;
        std::string Directory;

        bool GammaCorrection;
        long AssetID_;

        // Logger
        LoggerClass *Logger_;


        // Load Model From File
        void LoadModelFromFile(long AssetID, LoggerClass *Logger);

        // Draw Model
        void Draw(ERS_OBJECT_SHADER &Shader);


    private:

        void ProcessNode(aiNode *Node, const aiScene *Scene);

        ERS_OBJECT_MESH ProcessMesh(aiMesh *Mesh, const aiScene *Scene);

        std::vector<ERS_OBJECT_TEXTURE_2D> LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, std::string TypeName);



};


