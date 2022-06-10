//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_LayoutManager.h>
#include <filesystem>


ERS_CLASS_LayoutManager::ERS_CLASS_LayoutManager(ERS_CLASS_LoggingSystem* Logger, const char* LayoutDirectory) {

    Logger_ = Logger;
    Logger_->Log("Initializing Layout Manager", 5);

    LayoutDirectory_ = LayoutDirectory;

 }


ERS_CLASS_LayoutManager::~ERS_CLASS_LayoutManager() {

    Logger_->Log("Layout Manager Destructor Called", 6);

}

bool ERS_CLASS_LayoutManager::IndexConfigs() {

    LayoutFiles_ = *new std::vector<YAML::Node>;

    // Create List Of Files
    for (const auto& Entry : std::filesystem::directory_iterator(std::string(LayoutDirectory_))) {

        // Get File Path        
        std::string FilePath{ Entry.path().u8string() };

        // Load YAML::Node
        YAML::Node Layout = YAML::LoadFile(FilePath.c_str());
        LayoutFiles_.push_back(Layout);

        // Parse Out Display Name From File Path
        // TODO
        std::string LayoutName;

        LayoutName = Layout["DisplayName"].as<std::string>();
        
        //FilePath = FilePath.substr(strlen(ThemePath_) + 1);
        //FilePath = FilePath.substr(0, strlen(FilePath.c_str()) - 5);

        // Add To Names Vector
        LayoutNames_.push_back(LayoutName);

        // Log Layout Indexed
        Logger_->Log(std::string(std::string("Indexed Layout: ") + FilePath).c_str(), 1);

    }


    Logger_->Log(std::string(std::string("Found ") + std::to_string(LayoutNames_.size()) + std::string(" Layouts")).c_str(), 1);

}

void ERS_CLASS_LayoutManager::SaveLayout() {



}

void ERS_CLASS_LayoutManager::LoadLayout() {



}