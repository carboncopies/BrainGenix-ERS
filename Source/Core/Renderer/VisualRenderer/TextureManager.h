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


    void InitializeTexture(ERSImage *Image) {

        // Generate Texture
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        // Set Texture Properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Generate Texture Map
        unsigned char *ImageData = FreeImage_GetBits(Image->ImageData);

        if (Image->Channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->Width, Image->Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, ImageData);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Image->Width, Image->Height, 0, GL_BGR, GL_UNSIGNED_BYTE, ImageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deallocate Image Data
        Image->CleanUp();



    }

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