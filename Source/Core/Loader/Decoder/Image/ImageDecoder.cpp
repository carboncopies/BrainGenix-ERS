//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Additonal Notes: None
    Date Created: 2021-10-28
*/  

#include "FreeImage.h"

#include "Core/Loader/Decoder/Image/ImageDecoder.h"


// Initialize The Class
void ImageDecoder::Initialize(LoggerClass Logger) {

    // Make Reference To Logger
    Logger_ = Logger;

    // Initialize System
    Logger_.Log("Initializing Image Decoding Subsystem", 4);

    Logger_.Log("Initializing FreeImage", 3);
    FreeImage_Initialise();

}

// Loads And Decodes Images From Disk Into Memory
FIBITMAP* ImageDecoder::LoadImageFromFile(const char* FilePath) {

    // Load Image
    return FreeImage_Load(FIF_JPEG, FilePath, JPEG_DEFAULT);


}

// Clean Up
void ImageDecoder::Cleanup() {

    // Deinit FreeImage
    FreeImage_DeInitialise();

}