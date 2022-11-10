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
        std::cout<<"Failed to Load File 'Config.yaml' Is ERS Being Run In The Right Working Directory?"<<std::endl;

        std::cout<<"\n";
        std::cout<<"Current Executable Path Is: '"<<GetExecutablePath()<<"'"<<std::endl;
        std::cout<<"Current Executable Directory Is: '"<<GetExecutablePath()<<"'"<<std::endl;
        std::cout<<"\n";

        std::cout<<"-- Current Working Directory's Files --"<<std::endl;
        for (const auto & entry : ghc::filesystem::directory_iterator(".")) {
            std::cout << entry.path() << " ";
        }
        std::cout<<"\n-- End Of File List --\n";

        std::cout<<"Fatal Error - Exiting!\n";
        return false;
    }

}



} // Close Namespace: Module
} // Close Namespace: ERS
} // Close Namespace: BrainGenix
