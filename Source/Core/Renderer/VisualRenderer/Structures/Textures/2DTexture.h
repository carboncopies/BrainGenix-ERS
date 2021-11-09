//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the 2d texture struct.
    Additonal Notes: None
    Date Created: 2021-11-04
*/

#pragma once

#include <string>
#include "FreeImage.h"

// Structure To Hold 2D ERS Texture
struct ERS_OBJECT_TEXTURE_2D {

    // Set OpenGL Handles
    unsigned int ID;
    
    // Set Metadata
    std::string Type;
    std::string Path;

    // Texutre Init Function
    void InitializeTexture(std::vector<char>* ImageDataBuffer, size_t ImageLength, bool FlipImage = true) {

        // Move this to a class
        FreeImage_Initialise();

        size_t Test = ImageLength;
        std::cout<<ImageDataBuffer<<std::endl;

        // Decode Image
        FIMEMORY* EncodedImageData = FreeImage_OpenMemory(reinterpret_cast<unsigned char*> (&ImageDataBuffer[0]), ImageLength);
        FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(EncodedImageData);
        FIBITMAP* ImageData = FreeImage_LoadFromMemory(Format, EncodedImageData);

        // Optionally Flip Image
        if (FlipImage) {
            FreeImage_FlipVertical(ImageData);
        }
    
        // Set Properties
        float Width = FreeImage_GetWidth(ImageData);
        float Height = FreeImage_GetHeight(ImageData);
        float Channels = FreeImage_GetLine(ImageData) / FreeImage_GetWidth(ImageData);


        // Generate Texture
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // Set Texture Properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Generate Texture Map
        unsigned char *OpenGLImageData = FreeImage_GetBits(ImageData);

        if (Channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, OpenGLImageData);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, OpenGLImageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deallocate Image Data
        FreeImage_Unload(ImageData);

        // Move This Later
        FreeImage_DeInitialise();

    }

};
