// In-Memory Image Loading Test

#include <iostream>
#include <fstream>

#include "FreeImage.h"


char* LoadFile(const char* FilePath) {

    // Open File
    std::ifstream File(FilePath, std::ios::ate | std::ios::binary);

    // Get File Size, Init Buffer
    size_t FileSize = (size_t) File.tellg();
    char* Buffer = NULL;

    // Jump To File Beginning, Read
    File.seekg(0);
    File.read(Buffer, FileSize);
    File.close();

    // Return Buffer
    return Buffer;
}





int main() {

    // Init FreeImage
    FreeImage_Initialise();

    // Load Test.png
    std::cout<<"Loading Image: 'Assets/Test.png' From Disk\n";
    char* FileData = LoadFile("Assets/Test.png");
    long ImageLength = std::size(FileData);

    FIMEMORY* InMemoryData = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(FileData), ImageLength);

    // De-Init FreeImage
    FreeImage_DeInitialise();

}
