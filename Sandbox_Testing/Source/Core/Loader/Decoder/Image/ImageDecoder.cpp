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
    Logger_->Log("Initializing Image Decoding Subsystem", 5);

    Logger_->Log("Initializing FreeImage", 4);
    FreeImage_Initialise();

}

// Loads And Decodes Images From Disk Into Memory
ERSImage ImageDecoder::LoadImageFromFile(const char* FilePath) {

    // Create Struct
    ERSImage ImageStruct{};

    // Load Image
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileType(FilePath, 0);
    ImageStruct.ImageData = FreeImage_Load(Format, FilePath);


    // Set Properties
    ImageStruct.Width = FreeImage_GetWidth(ImageStruct.ImageData);
    ImageStruct.Height = FreeImage_GetHeight(ImageStruct.ImageData);
    ImageStruct.Channels = FreeImage_GetColorsUsed(ImageStruct.ImageData);
    std::cout<<FreeImage_GetColorsUsed(ImageStruct.ImageData)<<"\n";

    // Return Data
    return ImageStruct;

}

// Clean Up
void ImageDecoder::Cleanup() {

    // Deinit FreeImage
    FreeImage_DeInitialise();

}