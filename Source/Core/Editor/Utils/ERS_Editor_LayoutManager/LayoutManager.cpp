//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <LayoutManager.h>

#include <sstream>


ERS_CLASS_LayoutManager::ERS_CLASS_LayoutManager(BG::Common::Logger::LoggingSystem* Logger, const char* LayoutDirectory) {

    Logger_ = Logger;
    LayoutDirectory_ = LayoutDirectory;
    Logger_->Log("Initializing Layout Manager", 5);

 }


ERS_CLASS_LayoutManager::~ERS_CLASS_LayoutManager() {

    Logger_->Log("Layout Manager Destructor Called", 6);

}

static std::string ERS_FUNCTION_SanitizeLayoutFileStem(std::string LayoutName) {

    if (LayoutName.empty()) {
        return std::string("Layout");
    }

    for (unsigned long i = 0; i < LayoutName.size(); i++) {
        char Character = LayoutName[i];
        bool IsAlphaNumeric = ((Character >= 'a') && (Character <= 'z')) || ((Character >= 'A') && (Character <= 'Z')) || ((Character >= '0') && (Character <= '9'));

        if (!IsAlphaNumeric && (Character != '-') && (Character != '_')) {
            LayoutName[i] = '_';
        }
    }

    return LayoutName;
}

static bool ERS_FUNCTION_ReadLayoutIniFile(const ghc::filesystem::path& FilePath, std::string* Output) {

    std::ifstream InputFile(FilePath.u8string(), std::ios::binary);
    if (!InputFile.is_open()) {
        return false;
    }

    std::ostringstream Buffer;
    Buffer << InputFile.rdbuf();
    *Output = Buffer.str();

    return true;
}

static bool ERS_FUNCTION_IsAbsoluteLayoutPath(const std::string& FilePath) {

    if (FilePath.empty()) {
        return false;
    }

    if ((FilePath[0] == '/') || (FilePath[0] == '\\')) {
        return true;
    }

    return (FilePath.size() > 1) && (FilePath[1] == ':');
}

void ERS_CLASS_LayoutManager::LoadLayouts() {

    LayoutFiles_.clear();
    LayoutNames_.clear();
    Layouts_.clear();
    Index = 0;

    ghc::filesystem::path LayoutDirectoryPath(LayoutDirectory_);
    if (!ghc::filesystem::exists(LayoutDirectoryPath)) {
        ghc::filesystem::create_directories(LayoutDirectoryPath);
    }

    for (const auto& Entry : ghc::filesystem::directory_iterator(LayoutDirectoryPath)) {

        if (!ghc::filesystem::is_regular_file(Entry.path())) {
            continue;
        }

        std::string Extension = Entry.path().extension().u8string();
        if ((Extension != std::string(".yaml")) && (Extension != std::string(".yml"))) {
            continue;
        }

        // Get File Path
        std::string FilePath{ Entry.path().u8string() };

        // Load YAML::Node
        YAML::Node LayoutNode;
        try {
            LayoutNode = YAML::LoadFile(FilePath.c_str());
        } catch (const YAML::Exception& Exception) {
            Logger_->Log(std::string(std::string("Failed To Load Layout File '") + FilePath + std::string("': ") + Exception.what()).c_str(), 7);
            continue;
        }
        
        // Build Temp Layout
        ERS_STRUCT_EditorLayout Layout;
        Layout.index = Index;

        // Parse Out Display Name From File
        std::string LayoutName = Entry.path().stem().u8string();
        if (LayoutNode["DisplayName"]) {
            LayoutName = LayoutNode["DisplayName"].as<std::string>();
        }
        Layout.name = LayoutName;

        // Parse Out Ini String From File Or Referenced Ini Asset
        std::string IniStr;
        if (LayoutNode["ImGuiIni"]) {
            IniStr = LayoutNode["ImGuiIni"].as<std::string>();
        } else if (LayoutNode["ImGuiIniPath"]) {
            std::string IniPathString = LayoutNode["ImGuiIniPath"].as<std::string>();
            ghc::filesystem::path IniPath(IniPathString);
            if (!ERS_FUNCTION_IsAbsoluteLayoutPath(IniPathString)) {
                IniPath = LayoutDirectoryPath / IniPath;
            }

            if (!ERS_FUNCTION_ReadLayoutIniFile(IniPath, &IniStr)) {
                Logger_->Log(std::string(std::string("Failed To Read Layout Ini File '") + IniPath.u8string() + std::string("'")).c_str(), 7);
                continue;
            }
        } else {
            Logger_->Log(std::string(std::string("Skipping Layout Without ImGuiIni Data: ") + FilePath).c_str(), 5);
            continue;
        }

        Layout.IniString = IniStr;

        // Add To Names and Layouts Vector
        LayoutFiles_.push_back(LayoutNode);
        LayoutNames_.push_back(LayoutName);
        Layouts_.push_back(Layout);

        // Log Layout Indexed
        Logger_->Log(std::string(std::string("Indexed Layout: ") + FilePath).c_str(), 1);

        Index++;
    }


    Logger_->Log(std::string(std::string("Found ") + std::to_string(LayoutNames_.size()) + std::string(" Layouts")).c_str(), 1);

}

void ERS_CLASS_LayoutManager::SaveLayout(std::string LayoutName) {

    if (LayoutName.empty()) {
        LayoutName = std::string("Layout");
    }

    ghc::filesystem::path LayoutDirectoryPath(LayoutDirectory_);
    if (!ghc::filesystem::exists(LayoutDirectoryPath)) {
        ghc::filesystem::create_directories(LayoutDirectoryPath);
    }

    // Save the Ini String
    std::string IniStr;
    size_t settings_size = 0;
    const char* Settings = ImGui::SaveIniSettingsToMemory(&settings_size);
    IniStr = std::string(Settings, settings_size);

    bool ExistingLayoutFound = false;
    for (unsigned long i = 0; i < LayoutNames_.size(); i++) {
        if (LayoutNames_[i] == LayoutName) {
            Layouts_[i].IniString = IniStr;
            ExistingLayoutFound = true;
            break;
        }
    }

    if (!ExistingLayoutFound) {
        // Add To Names Vector
        LayoutNames_.push_back(LayoutName);

        // Construct the New Layout Struct
        ERS_STRUCT_EditorLayout newLayout;
        newLayout.index = Index++;
        newLayout.name = LayoutName;
        newLayout.IniString = IniStr;
        Layouts_.push_back(newLayout);
    }

    ActiveLayoutName_ = LayoutName;

    // Save YAML Node
    YAML::Node Layout;
    Layout["ImGuiIni"] = IniStr;
    Layout["DisplayName"] = LayoutName;

    // Export the YAML string
    YAML::Emitter LayoutYAML;
    LayoutYAML << YAML::BeginMap;

    // Set Constant Info
    LayoutYAML << YAML::Key << "DisplayName" << YAML::Value << LayoutName;
    LayoutYAML << YAML::Key << "ImGuiIni" << YAML::Value << IniStr;

    // Stop Writing, Generate LayoutYAML
    LayoutYAML << YAML::EndMap;
    std::string YAMLstring = std::string(LayoutYAML.c_str());

    // Write the string into a YAML file in the directory
    ghc::filesystem::path LayoutPath = LayoutDirectoryPath / (ERS_FUNCTION_SanitizeLayoutFileStem(LayoutName) + std::string(".yaml"));
    std::ofstream file(LayoutPath.u8string());

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

    if ((LayoutID < 0) || (LayoutID >= (int)Layouts_.size())) {
        Logger_->Log("Failed To Apply Layout, Index Out Of Bounds", 5);
        return;
    }

    // Get Layout Name
    std::string LayoutName = LayoutNames_[LayoutID];
    ERS_STRUCT_EditorLayout Layout = Layouts_[LayoutID];

    Logger_->Log(std::string(std::string("Applying Layout: ") + LayoutName).c_str(), 4);

    ImGui::LoadIniSettingsFromMemory(Layout.IniString.c_str());
    ActiveLayoutName_ = LayoutName;

}

std::string ERS_CLASS_LayoutManager::GetActiveLayoutName() {

    return ActiveLayoutName_;
}

std::vector<std::string> ERS_CLASS_LayoutManager::GetLayoutNames() {

    return LayoutNames_;
}

void ERS_CLASS_LayoutManager::CreateLayout(std::string Name) {

    SaveLayout(Name);
}
