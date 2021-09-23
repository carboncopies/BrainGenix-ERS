//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for Texture importing.
    Additonal Notes: None
    Date Created: 2021-09-23
*/    


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


unsigned int LoadTexture (const char* ImagePath, LoggerClass Logger) {


    // Initialize GL Textures
    unsigned int Texture;
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set Texture Wrapping Params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set Texture Filter Params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load Image
    Logger.Log(std::string("Loading Texture Image '" + std::string(ImagePath) + "'").c_str(), 2);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(ImagePath, &width, &height, &nrChannels, 0);

    // If Image Loaded
    if (data) {

        // Push To OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        Logger.Log("Texture Image Load/Decode Failure", 8);
    }

    // Free Image Source Memory
    stbi_image_free(data);

    // Return Texture
    return Texture;

}