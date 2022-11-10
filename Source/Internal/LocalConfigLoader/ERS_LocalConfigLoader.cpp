//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_LocalConfigLoader.h>


namespace BrainGenix {
namespace ERS {
namespace Module {



bool LoadLocalConfiguration(std::string Path, YAML::Node& Configuration) {

    // Attempt Load
    try {
        Configuration = YAML::LoadFile("Config.yaml");
        return true;
    } catch (YAML::BadFile&) {

        // Try And Change Into Executable Path And See There - Otherwise Give Up
        try {
            std::string ValidExecuatblePath = GetExecutableDirectory();
            if (ValidExecuatblePath == "" || ValidExecuatblePath == "Unable To Get Binary Path") {
                throw YAML::BadFile();
            }
            chdir(ValidExecuatblePath.c_str());
            Configuration = YAML::LoadFile("Config.yaml");
        } catch (YAML::BadFile&) {

            // Build Error Message
            std::string Output;
            Output += "Failed to Load File 'Config.yaml' Is ERS Being Run In The Right Working Directory?\n";
            Output += "\n";
            Output += "Current Executable Path Is: '" + GetExecutablePath() + "'\n";
            Output += "Current Executable Directory Is: '" + GetExecutablePath() + "'\n";
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
            chdir("~/Library/Logs");
            mkdir("com.Carboncopies.BrainGenix.ERS");
            chdir("com.Carboncopies.BrainGenix.ERS");
#endif


            // Dump Error To File For Reading Even If No Console Is Present
            std::ofstream FileStream("Log.txt");
            FileStream << Output;
            FileStream.close();

            return false;
    
        }
    }

}



} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
