// In-Memory Image Loading Test

#include <iostream>
#include <fstream>
#include <map>

#include "FreeImage.h"


struct FileObject {

    // File Data
    size_t FileSize;
    char* Buffer;

    // Load File
    void LoadFile(const char* FilePath) {

        // Open File
        std::ifstream File(FilePath, std::ios::ate | std::ios::binary);

        // Get File Size, Init Buffer
        FileSize = (size_t) File.tellg();
        Buffer = NULL;

        // Jump To File Beginning, Read
        File.seekg(0);
        File.read(Buffer, FileSize);
        File.close();

    }

};




int main() {

    // Init FreeImage
    FreeImage_Initialise();

    // Load Test.png
    std::cout<<"Loading Image: 'Assets/Test.png' From Disk\n";

    FileObject FileObj;
    FileObj.LoadFile("Assets/Test.png");
    char* ImageData = FileObj.Buffer;
    size_t ImageLength = FileObj.FileSize;

    // Load Image Into Memory
    std::cout<<"Loading Image Into FreeImage Memory Object (FIMEMORY*)\n";
    FIMEMORY* InMemoryData = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(ImageData), ImageLength);
    
    // Identifying Image Format
    std::cout<<"Getting Image Format From FIMEMORY Object\n";
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(InMemoryData);
    std::cout<<"Identified Format To Be: "<<Format<<std::endl;


    // De-Init FreeImage
    FreeImage_DeInitialise();

}
