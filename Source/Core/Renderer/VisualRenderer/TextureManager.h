//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing textures.
    Additonal Notes: None
    Date Created: 2021-11-03
*/

#pragma once


#include "Core/Loader/Decoder/Image/ImageDecoder.h"



// Texture Struct (Could be modified later to be a material by adding multiple textures)
struct ERSTexture{

    // OpenGL References
    unsigned int Texture;




    void BindTexture() {

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, Texture);

    }

};


// Handles The Creation And Deletion Of Textures
class TextureManager {

    private:

        // Pointers
        LoggerClass *Logger_;

        // Instances
        ImageDecoder ImageDecoder_;


    public:

        void Initialize(LoggerClass *Logger);

        ERSTexture CreateTextureFromFile(const char* FilePath);


};



#include "Core/Renderer/VisualRenderer/TextureManager.cpp"