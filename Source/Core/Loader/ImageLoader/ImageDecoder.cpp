//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-10-28
*/  

#include "ImageDecoder.h"

// Initialize The Class
ImageDecoder::ImageDecoder(LoggerClass *Logger) {

    // Make Reference To Logger
    Logger_ = Logger;

    // Initialize System
    Logger_->Log("Initializing Image Decoding Subsystem", 5);

    Logger_->Log("Initializing FreeImage", 4);
    FreeImage_Initialise();

}

// Clean Up
ImageDecoder::~ImageDecoder() {

    // Deinit FreeImage
    FreeImage_DeInitialise();

}

// Loads And Decodes Images From Disk Into Memory
FIBITMAP* ImageDecoder::LoadImageFromFile(const char* FilePath) {

    // Load Image
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileType(FilePath, 0);
    FIBITMAP* ImageData = FreeImage_Load(Format, FilePath);


    // Return Data
    return ImageData;

}

