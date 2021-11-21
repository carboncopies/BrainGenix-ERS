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

}

// Texture Loader Destructor
TextureLoader::~TextureLoader() {

    // Log Destructor Call
    Logger_->Log("TextureLoader Destructor Called", 6);

}


// Load Texture Overloaded Functions
ERS_OBJECT_TEXTURE_2D TextureLoader::LoadTexture(const char* Path) { // File Version



}

ERS_OBJECT_TEXTURE_2D TextureLoader::LoadTexture(long AssetID) { // Database Version



}