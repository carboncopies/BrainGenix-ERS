//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_GetExecutablePath.h>


namespace BrainGenix {
namespace ERS {
namespace Module {



std::string GetExecutablePath() {

    char* Path = NULL;
    int Length, DirectoryNameLength;
    Length = wai_getExecutablePath(Path, 0, &DirectoryNameLength);
    
    if (Path == NULL) {
        return "";
    }

    return std::string(Path);
}


std::string GetExecutableDirectory() {
    char* Path = NULL;
    int Length, DirectoryNameLength;
    Length = wai_getModulePath(Path, 0, &DirectoryNameLength);

    if (Path == NULL) {
        return "";
    }

    return std::string(Path);
}




} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
