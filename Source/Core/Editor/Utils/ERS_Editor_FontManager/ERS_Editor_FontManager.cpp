//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides font loading/selecting functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#include <ERS_Editor_FontManager.h>


// ERS_CLASS_FontManager Constructor
ERS_CLASS_FontManager::ERS_CLASS_FontManager(std::shared_ptr<LoggerClass> Logger, const char* FontsDirPath) {

    // Create Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Font Manager", 5);

    // Copy Vars
    FontsDirectoryPath_ = FontsDirPath;

    // Index Fonts
    IndexFonts();

}

// ERS_CLASS_FontManager Destructor
ERS_CLASS_FontManager::~ERS_CLASS_FontManager() {
    
    // Log Destructor Call
    Logger_->Log("Font Manager Destructor Called", 6);

}

// Check String Endings (From: https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c)
bool ERS_CLASS_FontManager::EndsWith(const std::string& Input, const std::string& Ending) {
    if (Ending.size() > Input.size()) return false;
    return std::equal(Input.begin() + Input.size() - Ending.size(), Input.end(), Ending.begin());
}

// Index Fonts Function
void ERS_CLASS_FontManager::IndexFonts() {

    // Clear Vectors
    FontPathList_.clear();
    FontNameList_.clear();

    // Log Indexing
    Logger_->Log(std::string(std::string("Indexing Fonts In Dir: ") + std::string(FontsDirectoryPath_)).c_str(), 4);


    // Get List Of Files At Path
    for (const auto &Entry : std::filesystem::recursive_directory_iterator(std::string(FontsDirectoryPath_))) {

        // Get File Path        
        std::string FilePath{Entry.path().u8string()};

        // Check Extension
        if ((EndsWith(FilePath, ".ttf")) || (EndsWith(FilePath, ".otf"))) {

            // Append Path To PathList
            FontPathList_.push_back(FilePath);

            // Strip File Extension
            std::string FontName = FilePath.substr(0, strlen(FilePath.c_str())-4);

            // Strip Path
            int LastSlashIndex = FontName.find_last_of("/");
            FontName = FontName.substr(LastSlashIndex+1, strlen(FontName.c_str())-LastSlashIndex);

            // Append Font Name To FontNameList
            FontNameList_.push_back(FontName); 


            // Log Font Found
            std::string LogText = std::string("Indexed Font: ") + FilePath;
            Logger_->Log(LogText.c_str(), 3);

        }
    
    }

}

// Use Font Function
void ERS_CLASS_FontManager::UseFont(int FontIndex) {

    // Get Font Path From Dir
    const char* FontPath = FontPathList_[FontIndex].c_str();

    // Log Font Adjustment
    Logger_->Log(std::string(std::string("Changing Font To: ") + std::string(FontPath)).c_str(), 4);

    // Load, Apply Font
    ImGuiIO& Io = ImGui::GetIO();
    Io.Fonts->Clear();
    Io.Fonts->AddFontFromFileTTF(FontPath, FontSize_);
    Io.Fonts->Build();
    ImGui_ImplOpenGL3_CreateFontsTexture();

}

// Use Font Function
void ERS_CLASS_FontManager::UseFont(std::string Font) {

    // Index to Find Font
    int Index;
    bool FoundFont = false;
    for (Index = 0; Index < FontNameList_.size(); Index++) {
        if (FontNameList_[Index] == Font) {
            FoundFont = true;
            break;
        }
    }

    // Apply Font
    if (FoundFont) {

        // Get Font Path From Dir
        const char* FontPath = FontPathList_[Index].c_str();

        // Log Font Adjustment
        Logger_->Log(std::string(std::string("Changing Font To: ") + std::string(FontPath)).c_str(), 4);

        // Load, Apply Font
        ImGuiIO& Io = ImGui::GetIO();
        Io.Fonts->Clear();
        Io.Fonts->AddFontFromFileTTF(FontPath, FontSize_);
        Io.Fonts->Build();
        
    } else {
        Logger_->Log("Failed To Find Target Font, Skipping", 5);
    }

}

// Set Font Size
void ERS_CLASS_FontManager::SetFontSize(float FontSize) {

    // Set Font Size
    FontSize_ = FontSize;

}

// CheckUpdate
void ERS_CLASS_FontManager::CheckUpdateFont() {

    // If Font Is To Be Updated
    if (UpdateFont_) {
        UseFont(FontSelector_);
        UpdateFont_ = false;
    }

}

// Font Selector Window
void ERS_CLASS_FontManager::FontSelectorWindow(bool *WindowEnabled) {

    // If Window Enabled
    if (*WindowEnabled) {

        // Draw Window
        ImGuiWindowFlags Flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        if (ImGui::Begin("Font Selector", WindowEnabled, Flags)) {
            ImGui::SetWindowSize(ImVec2(0,0));

                // Font Selector Radio Button List
                ImGui::BeginChild("Font Radio Buttons", ImVec2(300, 400), true);

                    for (int i = 0; i < FontNameList_.size(); i++) {
                        ImGui::RadioButton(FontNameList_[i].c_str(), &FontSelector_, i);
                    }

                ImGui::EndChild();

                // Dividing Line
                ImGui::Separator();

                // Font Size Slider
                ImGui::SliderFloat("Font Size", &FontSize_, 5.0f, 30.0f);

                // Divider
                ImGui::Separator();

                // Reload, Apply, Close Buttons
                if (ImGui::Button("Reload")) {
                    IndexFonts();
                }
                ImGui::SameLine();

                if (ImGui::Button("Apply")) {
                    UpdateFont_ = true;
                }
                ImGui::SameLine();

                if (ImGui::Button("Close")) {
                    *WindowEnabled = false;
                }


            ImGui::End();
        }

    }

}