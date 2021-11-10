// In-Memory Image Loading Test

#include <iostream>
#include <fstream>
#include <map>

#include "FreeImage.h"


std::map<char*, long> LoadFile(const char* FilePath) {

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
    std::map<char*, long> Out;
    Out["one"] = *Buffer;
    Out["two"] = FileSize;
    return Out;
}





int main() {

    // Init FreeImage
    FreeImage_Initialise();

    // Load Test.png
    std::cout<<"Loading Image: 'Assets/Test.png' From Disk\n";
    std::map<char*, long> FileObject = LoadFile("Assets/Test.png");
    char* ImageData = &FileObject[0];
    long ImageLength = FileObject[1];

    FIMEMORY* InMemoryData = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(ImageData), ImageLength);

    // De-Init FreeImage
    FreeImage_DeInitialise();

}
