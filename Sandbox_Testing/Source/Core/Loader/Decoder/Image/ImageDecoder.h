//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing image decoding functionality.
    Additonal Notes: None
    Date Created: 2021-10-28
*/  


// Image Struct
struct ERSImage {

    // Hold Image Properties
    FIBITMAP* ImageData = nullptr;

    int Width = 0;
    int Height = 0;
    int Channels = 0;

    // Image Data Destructor
    // ~ImageData() {
    //     FreeImage_Unload(ImageData);
    // }

};



// Image Decoder Class
class ImageDecoder 

    private:

        LoggerClass *Logger_;

    public:
        
        // Initialize Image Loader
        void Initialize(LoggerClass Logger);

        // Load Images From Local Disk
        ERSImage LoadImageFromFile(const char* FilePath);

        // Decode Images In Memory
        void DecodeImage();

        // Cleanup
        void Cleanup();

};