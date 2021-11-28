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


//FIXME!!!! MODIFY CLASS TO USE CONSTRUCTORS AND DESTRUCTORS!


/**
 * @brief Class for decoding images.
 * 
 */
class ImageDecoder {

    private:

        LoggerClass *Logger_; /**<Pointer To Logging System*/

    public:
        
        /**
         * @brief Initialize Image Decoder.
         * 
         * @param Logger 
         */
        void Initialize(LoggerClass *Logger);

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

        /**
         * @brief Destructor... *WIP*
         * 
         */
        void Cleanup();

};

