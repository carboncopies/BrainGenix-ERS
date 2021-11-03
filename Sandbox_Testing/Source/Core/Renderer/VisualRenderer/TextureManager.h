//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing textures.
    Additonal Notes: None
    Date Created: 2021-11-03
*/

#pragma once

// Texture Struct (Could be modified later to be a material by adding multiple textures)
struct ERSTexture{

    // OpenGL References
    unsigned int Texture;
    
    // Status Bools
    bool _TextureInitialized = false;


    void InitializeTexture(ERSImage *Image) {

        // Generate Texture
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        


    }


};