//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_LocalConfigLoader.h>


namespace BrainGenix {
namespace ERS {
namespace Module {


bool TryWorkingPath(std::string Path) {

    // Enter Folder
    chdir(Path.c_str());

    // Check If Good
    try {
        YAML::LoadFile("Config.yaml")
        return true;
    } catch {YAML::BadFile&} {
        return false;
    }

}

void ChuckErrorAndGiveUp() {

    // Build Error Message
    std::string Output;
    Output += "Failed to Load File 'Config.yaml' Is ERS Being Run In The Right Working Directory?\n";
    Output += "\n";
    Output += "Current Executable Path Is: '" + GetExecutablePath() + "'\n";
    Output += "Current Executable Directory Is: '" + GetExecutableDirectory() + "'\n";
    Output += "Current Directory Is: '" + std::string(ghc::filesystem::current_path()) + "'\n";
    Output += "\n";
    Output += "-- Current Working Directory's Files --\n";
    for (const auto & entry : ghc::filesystem::directory_iterator(".")) {
        Output += std::string(entry.path()) + " ";
    }
    Output += "\n-- End Of File List --\n";
    Output += "Fatal Error - Exiting!\n";

    // Dump Error To Console
    std::cout<<Output;

    // If OSX - Change Dir To Log Dump Folder
#if __APPLE__
    chdir(std::string(sago::getDesktopFolder()).c_str());
    mkdir("com.Carboncopies.BrainGenix.ERS", 0777);
    chdir("com.Carboncopies.BrainGenix.ERS");
#endif


    // Dump Error To File For Reading Even If No Console Is Present
    std::ofstream FileStream("Log.txt");
    FileStream << Output;
    FileStream.close();

}


bool LoadLocalConfiguration(std::string Path, YAML::Node& Configuration) {

    // Try a bunch of differet paths, chuck an error at the end and give up
    if (TryWorkingPath(".")) {
        Configuration = YAML::LoadFile("Config.yaml");
        return true;
    } else if (TryWorkingPath("../Resources")) {
        Configuration = YAML::LoadFile("Config.yaml");
        return true;
    } else if (TryWorkingPath(GetExecutableDirectory())) {
        Configuration = YAML::LoadFile("Config.yaml");
        return true;
    } else if (TryWorkingPath("../Resources")) {
        Configuration = YAML::LoadFile("Config.yaml");
        return true;
    } else {
        ChuckErrorAndGiveUp();
        return false;
    }



}



} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
