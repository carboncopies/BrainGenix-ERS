//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the 2d texture struct.
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#pragma once

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>

class TextureLoader {

    private:

        // Member Vars
        LoggerClass *Logger_;


    public:

        /**
         * @brief Construct a new Texture Loader object
         * 
         * @param Logger 
         */
        TextureLoader(LoggerClass* Logger);

        /**
         * @brief Destroy the Texture Loader object
         * 
         */
        ~TextureLoader();

        /**
         * @brief Load a texture at the given file path. (For on file loading)
         * 
         * @param Path 
         * @return ERS_OBJECT_TEXTURE_2D 
         */
        ERS_OBJECT_TEXTURE_2D LoadTexture(const char* Path);

        /**
         * @brief Load a texture at the given asset id. (For database loading)
         * 
         * @param AssetID 
         * @return ERS_OBJECT_TEXTURE_2D 
         */
        ERS_OBJECT_TEXTURE_2D LoadTexture(long AssetID);

};