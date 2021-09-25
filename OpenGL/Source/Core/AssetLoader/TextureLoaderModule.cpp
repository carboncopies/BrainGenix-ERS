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
#include <string>
#include <sstream>


unsigned int LoadTexture (LoggerClass Logger, const char* ImagePath, std::string &Directory) {


    // Update Filepath
    const char* Filename = ImagePath;
    const char* FilePath = std::string(std::string(Directory) + "/" + std::string(Filename)).c_str();

    // Initialize GL Textures
    unsigned int TextureID;
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    // Flip Texture
    stbi_set_flip_vertically_on_load(true);

    // Load Image
    Logger.Log(std::string("Loading Texture Image '" + std::string(ImagePath) + "'").c_str(), 2);
    int width, height, nrChannels;
    unsigned char *Data = stbi_load(FilePath, &width, &height, &nrChannels, 0);

    // If Image Loaded
    if (Data) {

        // Check Image Format
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set Texture Wrapping Params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set Texture Filter Params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    } else {
        Logger.Log("Texture Image Load/Decode Failure", 8);
    }

    // Free Image Source Memory
    stbi_image_free(Data);

    // Return Texture ID
    return TextureID;

}