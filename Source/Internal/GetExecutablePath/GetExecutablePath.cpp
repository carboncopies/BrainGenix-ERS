//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GetExecutablePath.h>


namespace BrainGenix {
namespace ERS {
namespace Module {





std::string GetExecutablePath() {

    #ifdef __APPLE__
        char buf [PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        if(!_NSGetExecutablePath(buf, &bufsize))
            puts(buf);
        return std::string(buf);
    #else

        char* Path = NULL;
        int Length, DirectoryNameLength;
        Length = wai_getExecutablePath(Path, 0, &DirectoryNameLength);
        
        if (Path == NULL) {
            return "Unable To Get Binary Path";
        }

        return std::string(Path);
    #endif
}


std::string GetExecutableDirectory() {
    #ifdef __APPLE__
        char buf [PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        if(!_NSGetExecutablePath(buf, &bufsize))
            puts(buf);
        return std::string(buf).substr(0, std::string(buf).find_last_of("/"));
    #else

        char* Path = NULL;
        int Length, DirectoryNameLength;
        Length = wai_getModulePath(Path, 0, &DirectoryNameLength);
        

        if (Path == NULL) {
            return "Unable To Get Binary Path";
        }

        return std::string(Path);
    #endif
}




} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
