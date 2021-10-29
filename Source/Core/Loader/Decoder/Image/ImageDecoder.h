//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Additonal Notes: None
    Date Created: 2021-10-28
*/  


// Image Decoder Class
class ImageDecoder {

    private:

        LoggerClass Logger_;

    public:
        
        // Initialize Image Loader
        void Initialize(LoggerClass Logger);

        // Load Images From Local Disk
        FIBITMAP* LoadImageFromFile(const char* FilePath);

        // Decode Images In Memory
        void DecodeImage();

        // Cleanup
        void Cleanup();

};