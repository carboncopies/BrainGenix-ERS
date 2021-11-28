//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the 2d texture struct.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ImageDecoder.h>
#include <2DTexture.h>


/**
 * @brief Loads ERS_OBJECT Textures Into Memory.
 * 
 */
class TextureLoader {

    private:

        /**
         * @brief Logging System Instance.
         * 
         */
        LoggerClass *Logger_;


        /**
         * @brief Image Loading/Decoding Class Instance.
         * 
         */
        ImageDecoder ImageDecoder_;


    public:

        /**
         * @brief Construct a new Texture Loader object.
         * 
         * @param Logger 
         */
        TextureLoader(LoggerClass* Logger);

        /**
         * @brief Destroy the Texture Loader object.
         * 
         */
        ~TextureLoader();



        /**
         * @brief Load a texture at the given file path. (For on file loading).
         * 
         * @param Path 
         * @return ERS_OBJECT_TEXTURE_2D 
         */
        ERS_OBJECT_TEXTURE_2D LoadTexture(const char* Path, bool FlipImage = false);

        /**
         * @brief Load a texture at the given asset id. (For database loading).
         * 
         * @param AssetID 
         * @return ERS_OBJECT_TEXTURE_2D 
         */
        ERS_OBJECT_TEXTURE_2D LoadTexture(long AssetID, bool FlipImage = false);


        // ADD FUNCTION TO BATCH LOAD TEXTURES


};