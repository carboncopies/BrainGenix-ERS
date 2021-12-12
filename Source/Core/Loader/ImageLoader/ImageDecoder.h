//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-10-28
*/  

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <FreeImage.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>



/**
 * @brief Class for decoding images.
 * 
 */
class ImageDecoder {

    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Logging System*/

    public:
        
        /**
         * @brief Construct a new Image Decoder object
         * 
         * @param Logger 
         */
        ImageDecoder(std::shared_ptr<LoggerClass> Logger);

        /**
         * @brief Destroy the Image Decoder object
         * 
         */
        ~ImageDecoder();


        /**
         * @brief Loads an image from a given file path, returns FIBITMAP*.
         * 
         * @param FilePath 
         * @return FIBITMAP* 
         */
        FIBITMAP* LoadImageFromFile(const char* FilePath);

        /**
         * @brief Decodes an image in-memory. *WIP*
         * 
         */
        void DecodeImage();



};

