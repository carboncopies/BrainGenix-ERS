//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GetExecutablePath.h>


namespace BrainGenix {
namespace ERS {
namespace Module {



#ifndef __APPLE__
static std::string GetWhereAmIPath(int (*PathGetter)(char*, int, int*), bool ReturnDirectory) {
    int DirectoryNameLength = 0;
    int Length = PathGetter(nullptr, 0, &DirectoryNameLength);
    if (Length <= 0) {
        return "Unable To Get Binary Path";
    }

    std::string Path(static_cast<size_t>(Length), '\0');
    Length = PathGetter(&Path[0], Length, &DirectoryNameLength);
    if (Length <= 0) {
        return "Unable To Get Binary Path";
    }

    Path.resize(static_cast<size_t>(Length));
    if (ReturnDirectory) {
        if (DirectoryNameLength <= 0) {
            return "";
        }
        Path.resize(static_cast<size_t>(DirectoryNameLength));
    }

    return Path;
}
#endif



std::string GetExecutablePath() {

    #ifdef __APPLE__
        char buf [PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        if(!_NSGetExecutablePath(buf, &bufsize))
            puts(buf);
        return std::string(buf);
    #else

        return GetWhereAmIPath(wai_getExecutablePath, false);
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

        return GetWhereAmIPath(wai_getExecutablePath, true);
    #endif
}




} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
