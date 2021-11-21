//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for loading/compiling shaders.
    Additonal Notes: None
    Date Created: 2021-09-28
*/
 

#include "FileIO.h"


//FIXME: REPLACE READFILE CONTENTS WITH COMMENTED OUT STUFF BELOW!
std::string ReadFile(const std::string& FileName, LoggerClass *Logger_) {

    // Open File
    if (Logger_ != nullptr) {
        Logger_->Log(std::string(std::string("Opening File '") + std::string(FileName) + std::string("'")).c_str(), 4);
    }

    std::ifstream File(FileName, std::ios::ate | std::ios::binary);

    // Check If File Open
    if (!File.is_open()) {
        Logger_->Log("Error Opening File", 10);
    }


    size_t FileSize = (size_t) File.tellg();
    std::vector<char> Buffer(FileSize);

    // Jump To File Beginning
    File.seekg(0);
    File.read(Buffer.data(), FileSize);
    File.close();


    // Convert Vector To String
    std::string OutputString(Buffer.begin(), Buffer.end());
    return OutputString;


}



// struct ImageFileObject {

//     // Declare Member Variables
//     BYTE *MemoryBuffer;
//     struct stat Buffer;
//     int Result;


//     // Load File Into Mem
//     bool LoadImage(const char* FilePath) { // Loads Image Into Memory Buffer, Returns True On Success, False On Failure

//         // Get File Stats
//         Result = stat(FilePath, &Buffer);
//         if (Result == 0) {

//             MemoryBuffer = (BYTE*)malloc(Buffer.st_size * sizeof(BYTE));
//             if (MemoryBuffer) {

//                 FILE *Stream = fopen(FilePath, "rb");
//                 if (Stream) {

//                     // Read File Data
//                     fread(MemoryBuffer, sizeof(BYTE), Buffer.st_size, Stream);
//                     fclose(Stream);

//                     return true;

//                 }
//             }
//         }

//         // Return Fail
//         return false;

//     }
    
//     // Free Memory
//     void FreeMemory() {
//         free(MemoryBuffer);
//     }


// };