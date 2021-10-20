//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for loading/compiling shaders.
    Additonal Notes: None
    Date Created: 2021-09-28
*/
 
#include <fstream>

#include "Core/Loader/Shaders/ShaderLoader.h"


static std::vector<char> ReadFile(const std::string& FileName, LoggerClass Logger) {

    // Open File
    Logger.Log(std::string(std::string("Opening File '") + std::string(FileName) + std::string("'")).c_str(), 4);

    std::ifstream File(FileName, std::ios::ate | std::ios::binary);

    // Check If File Open
    if (!File.is_open()) {
        Logger.Log("Error Opening File", 10);
    }

    

    size_t FileSize = (size_t) File.tellg();
    std::vector<char> Buffer(FileSize);

    // Jump To File Beginning
    File.seekg(0);
    File.read(Buffer.data(), FileSize);
    File.close();

    return Buffer;


}