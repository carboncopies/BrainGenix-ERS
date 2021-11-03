//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing textures.
    Additonal Notes: None
    Date Created: 2021-11-03
*/


#include "Core/Loader/Decoder/Image/ImageDecoder.cpp"

#include "Core/Renderer/VisualRenderer/TextureManager.h"



void TextureManager::Initialize(LoggerClass *Logger) {

    // Create Pointers
    Logger_ = Logger;

    // Log Init
    Logger_->Log("Initializing Texture Manager", 5);

    // Init Image Manager Instance
    ImageDecoder_.Initialize(Logger_);

}

ERSTexture TextureManager::CreateTextureFromFile(const char* FilePath) {

    // Log Texture
    Logger_->Log(std::string(std::string("Loading ERSTexture From File At: '") + std::string(FilePath) + std::string(".")).c_str(), 4);

    // Load Image
    ERSImage Image = ImageDecoder_.LoadImageFromFile(FilePath);

    // Create Texture Struct
    ERSTexture Texture;
    Texture.InitializeTexture(&Image);

    return Texture;

}