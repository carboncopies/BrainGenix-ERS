//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Additonal Notes: None
    Date Created: 2021-10-28
*/  

#include "ImageDecoder.h"

// Initialize The Class
void ImageDecoder::Initialize(LoggerClass *Logger) {

    // Make Reference To Logger
    Logger_ = Logger;

    // Initialize System
    Logger_->Log("Initializing Image Decoding Subsystem", 5);

    Logger_->Log("Initializing FreeImage", 4);
    FreeImage_Initialise();

}

// Loads And Decodes Images From Disk Into Memory
FIBITMAP* ImageDecoder::LoadImageFromFile(const char* FilePath) {

    // Load Image
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileType(FilePath, 0);
    FIBITMAP* ImageData = FreeImage_Load(Format, FilePath);


    // Return Data
    return ImageData;

}

// Clean Up
void ImageDecoder::Cleanup() {

    // Deinit FreeImage
    FreeImage_DeInitialise();

}