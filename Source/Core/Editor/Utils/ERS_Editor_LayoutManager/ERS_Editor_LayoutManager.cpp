//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_LayoutManager.h>
#include <filesystem>
#include <imgui.h>
#include <fstream>

struct Layout {
    int index;
    std::string name;
    std::string IniString;
};

ERS_CLASS_LayoutManager::ERS_CLASS_LayoutManager(ERS_CLASS_LoggingSystem* Logger, const char* LayoutDirectory) {

    Logger_ = Logger;
    LayoutDirectory_ = LayoutDirectory;
    Logger_->Log("Initializing Layout Manager", 5);

 }


ERS_CLASS_LayoutManager::~ERS_CLASS_LayoutManager() {

    Logger_->Log("Layout Manager Destructor Called", 6);

}

void ERS_CLASS_LayoutManager::LoadLayouts() {

    LayoutFiles_ = *new std::vector<YAML::Node>;

    // Create List Of Files
    for (const auto& Entry : std::filesystem::directory_iterator(std::string(LayoutDirectory_))) {

        // Get File Path
        std::string FilePath{ Entry.path().u8string() };

        // Load YAML::Node
        YAML::Node Layout = YAML::LoadFile(FilePath.c_str());
        LayoutFiles_.push_back(Layout);

        // Parse Out Display Name From File Path
        std::string LayoutName;
        LayoutName = Layout["DisplayName"].as<std::string>();

        // Add To Names Vector
        LayoutNames_.push_back(LayoutName);

        // Log Layout Indexed
        Logger_->Log(std::string(std::string("Indexed Layout: ") + FilePath).c_str(), 1);

    }


    Logger_->Log(std::string(std::string("Found ") + std::to_string(LayoutNames_.size()) + std::string(" Layouts")).c_str(), 1);

}

void ERS_CLASS_LayoutManager::SaveLayout(std::string LayoutName) {

    std::string IniString;

    size_t settings_size = 0;
    IniString = static_cast<std::string> (ImGui::SaveIniSettingsToMemory(&settings_size));

    // Save YAML file
    YAML::Node Layout;
    Layout["ImGuiIni"] = IniString;

    // Set the layout name
    Layout["DisplayName"] = LayoutName;

    LayoutFiles_.push_back(Layout);

    // Add To Names Vector
    LayoutNames_.push_back(LayoutName);

    // Export the YAML string
    YAML::Emitter LayoutYAML;
    LayoutYAML << YAML::BeginMap;

    // Set Constant Info
    LayoutYAML << YAML::Key << "DisplayName" << YAML::Value << LayoutName;
    LayoutYAML << YAML::Key << "ImGuiIni" << YAML::Value << IniString;

    // Stop Writing, Generate LayoutYAML
    LayoutYAML << YAML::EndMap;
    std::string YAMLstring = std::string(LayoutYAML.c_str());

    // Write the string into a YAML file in the directory
    std::ofstream file(std::string(LayoutDirectory_) + "/" + LayoutName + ".yaml");

    if (!file.fail())
        file << YAMLstring;

    file.close();

}

void ERS_CLASS_LayoutManager::ApplyLayout(std::string LayoutName) {

    int Index;
    bool HasFoundLayout = false;
    for (Index = 0; (long)Index < (long)LayoutNames_.size(); Index++) {
        if (LayoutNames_[Index] == std::string(LayoutName)) {
            HasFoundLayout = true;
            break;
        }
    }

    if (HasFoundLayout) {
        ApplyLayout(Index);
    }
    else {
        Logger_->Log("Failed To Find Layout, Skipping", 5);
    }

}

void ERS_CLASS_LayoutManager::ApplyLayout(int LayoutID) {

    // Get Layout Name
    std::string LayoutName = LayoutNames_[LayoutID];
    YAML::Node LayoutNode = LayoutFiles_[LayoutID];

    Logger_->Log(std::string(std::string("Applying Layout: ") + LayoutName).c_str(), 4);

    ImGui::LoadIniSettingsFromMemory(LayoutNode["ImGuiIni"].as<const char*>());

}
