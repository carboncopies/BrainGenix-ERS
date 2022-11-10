//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_GetExecutablePath.h>


namespace BrainGenix {
namespace ERS {
namespace Module {

#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <limits.h>

    int main(int argc, char **argv)
    {
    char buf [PATH_MAX];
    uint32_t bufsize = PATH_MAX;
    if(!_NSGetExecutablePath(buf, &bufsize))
        puts(buf);
    return 0;
    }
#endif




std::string GetExecutablePath() {

    char* Path = NULL;
    int Length, DirectoryNameLength;
    Length = wai_getExecutablePath(Path, 0, &DirectoryNameLength);
    
    if (Path == NULL) {
        return "Unable To Get Binary Path";
    }

    return std::string(Path);
}


std::string GetExecutableDirectory() {
    char* Path = NULL;
    int Length, DirectoryNameLength;
    Length = wai_getModulePath(Path, 0, &DirectoryNameLength);

    if (Path == NULL) {
        return "Unable To Get Binary Path";
    }

    return std::string(Path);
}




} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
