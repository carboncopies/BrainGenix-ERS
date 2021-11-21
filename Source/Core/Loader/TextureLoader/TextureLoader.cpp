//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the 2d texture struct.
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#include <TextureLoader.h>



// Texture Loader Constructor
TextureLoader::TextureLoader(LoggerClass* Logger) {

    // Create Local Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Texture Loader Class", 5);

    // Create Instance Of ImageDecoder
    ImageDecoder_.Initialize(Logger_);
    

}

// Texture Loader Destructor
TextureLoader::~TextureLoader() {

    // Log Destructor Call
    Logger_->Log("TextureLoader Destructor Called", 6);

    // Deinit ImageDecoder
    ImageDecoder_.Cleanup();

}


// Load Texture Overloaded Functions
ERS_OBJECT_TEXTURE_2D TextureLoader::LoadTexture(const char* Path, bool FlipImage) { // File Version

        // Log Texture Load
        Logger_->Log(std::string(std::string("Loading Texture At Filepath: ") + std::string(Path)).c_str(), 4);

        // Create Texture Object
        ERS_OBJECT_TEXTURE_2D Texture;

        // Load Image
        FIBITMAP* ImageData = ImageDecoder_.LoadImageFromFile(Path);
        if (FlipImage) {
            FreeImage_FlipVertical(ImageData);
        }

        // Set Properties
        float Width = FreeImage_GetWidth(ImageData);
        float Height = FreeImage_GetHeight(ImageData);
        float Channels = FreeImage_GetLine(ImageData) / FreeImage_GetWidth(ImageData);


        // Generate Texture
        glGenTextures(1, &Texture.ID);
        glBindTexture(GL_TEXTURE_2D, Texture.ID);

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


        // Unload Texture RAM
        FreeImage_Unload(ImageData);


        // Return Texture
        return Texture;



}

ERS_OBJECT_TEXTURE_2D TextureLoader::LoadTexture(long AssetID, bool FlipImage) { // Database Version



}