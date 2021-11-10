// In-Memory Image Loading Test

#include <iostream>
#include <fstream>
#include <map>

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>

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


struct ImageFileObject {

    // Declare Member Variables
    BYTE *MemoryBuffer;
    struct stat Buffer;
    int Result;


    // Load File Into Mem
    bool LoadImage(const char* FilePath) { // Loads Image Into Memory Buffer, Returns True On Success, False On Failure

        // Get File Stats
        Result = stat(FilePath, &Buffer);
        if (Result == 0) {

            MemoryBuffer = (BYTE*)malloc(Buffer.st_size * sizeof(BYTE));
            if (MemoryBuffer) {

                FILE *Stream = fopen(FilePath, "rb");
                if (Stream) {

                    // Read File Data
                    fread(MemoryBuffer, sizeof(BYTE), Buffer.st_size, Stream);
                    fclose(Stream);

                    return true;

                }
            }
        }

        // Return Fail
        return false;

    }


};


int main() {

    // Init FreeImage
    FreeImage_Initialise();

    // Load Test.png
    std::cout<<"Loading Image: 'Assets/Test.png' From Disk\n";

    const char* Path = "Assets/Test.png";


    ImageFileObject Obj;
    std::cout<<Obj.LoadImage(Path)<<std::endl;









    // Load Image Into Memory
    std::cout<<"Loading Image Into FreeImage Memory Object (FIMEMORY*)\n";
    FIMEMORY* InMemoryData = FreeImage_OpenMemory(Obj.MemoryBuffer, Obj.Buffer.st_size);
    
    // Identifying Image Format
    std::cout<<"Getting Image Format From FIMEMORY Object\n";
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(InMemoryData);
    std::cout<<"Identified Format To Be: "<<Format<<std::endl;


    // De-Init FreeImage
    FreeImage_DeInitialise();

}
