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

// Structure To Hold 2D ERS Texture
struct ERS_OBJECT_TEXTURE_2D {

    // Set OpenGL Handles
    unsigned int ID;
    
    // Set Metadata
    std::string Type;
    std::string Path;

    // Texutre Init Function
    void InitializeTexture(FIBITMAP* Image) {

        // Generate Texture
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // Set Texture Properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Generate Texture Map
        unsigned char *ImageData = FreeImage_GetBits(Image);

        if (Image->Channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->Width, Image->Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, ImageData);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Image->Width, Image->Height, 0, GL_BGR, GL_UNSIGNED_BYTE, ImageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deallocate Image Data
        Image->CleanUp();

    }

};
