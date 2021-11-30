//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides theme loading functionality..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
*/

#include <Theme.h>


// ThemeManager Constructor
ThemeManager::ThemeManager(LoggerClass *Logger, const char* ThemePath) {

    // Create Local Pointers
    Logger_ = Logger;
    ThemePath_ = ThemePath;

    // Log Initialization
    Logger_->Log("Initializing Theme Manager", 5);

    // Find Themes
    LoadThemes();

    // Default To Dark Mode
    int Index;
    for (Index = 0; Index < ThemeNames_.size(); Index++) {
        if (ThemeNames_[Index] == "Dark") {
            break;
        }
    }
    ApplyThemes(Index);

}

// ThemeManager Destructor
ThemeManager::~ThemeManager() {

    // Log Destructor Call
    Logger_->Log("ThemeManager Destructor Called", 6);

}

// Load Themes
void ThemeManager::LoadThemes() {

    // Clear Vectors
    ThemeNames_ = *new std::vector<std::string>;
    ThemeFiles_ = *new std::vector<YAML::Node>;

    // Create List Of Files
    for (const auto &Entry : std::filesystem::directory_iterator(std::string(ThemePath_))) {

        // Get File Path        
        std::string FilePath = Entry.path();

        // Load YAML::Node
        YAML::Node Theme = YAML::LoadFile(FilePath.c_str());
        ThemeFiles_.push_back(Theme);

        // Parse Out Name From File Path
        FilePath = FilePath.substr(strlen(ThemePath_)+1);
        FilePath = FilePath.substr(0, strlen(FilePath.c_str())-5);

        // Add To Names Vector
        ThemeNames_.push_back(FilePath);

        // Log Theme Loaded
        Logger_->Log(std::string(std::string("Loaded Editor Theme: ") + FilePath).c_str(), 1);

    }


    // Log Number Of Themes Found
    Logger_->Log(std::string(std::string("Found ") + std::to_string(ThemeNames_.size()) + std::string(" Themes")).c_str(), 1);

}

// Read Color
ImVec4 ThemeManager::ReadColor(const char* NodeName, YAML::Node Target) {

    // Log Read
     Logger_->Log(std::string(std::string("Reading Theme For Value: '") + std::string(NodeName) + std::string("'")).c_str(), 1);

    // Get Subnode
    YAML::Node Subnode = Target[NodeName];

    // Create New Color
    ImVec4 Color;

    // Get Values And Push Into Color
    Color.x = Subnode[0].as<float>()/255.0f;
    Color.y = Subnode[1].as<float>()/255.0f;
    Color.z = Subnode[2].as<float>()/255.0f;
    Color.w = Subnode[3].as<float>()/255.0f;

    // Return Value
    return Color;

}

// Apply Theme
void ThemeManager::ApplyThemes(int ThemeID) {

    // Get Theme Name
    std::string ThemeName = ThemeNames_[ThemeID];
    YAML::Node ThemeNode = ThemeFiles_[ThemeID];

    // Log Theme Loading
    Logger_->Log(std::string(std::string("Applying Theme: ") + ThemeName).c_str(), 4);


    // Background Color
    Logger_->Log("Reading Theme For Value: 'EditorBackgroundColor'", 1);
    YAML::Node ColorsNode = ThemeNode["EditorBackgroundColor"];

    ClearColor_.x = ColorsNode[0].as<float>()/255.0f;
    ClearColor_.y = ColorsNode[1].as<float>()/255.0f;
    ClearColor_.z = ColorsNode[2].as<float>()/255.0f;
    ClearColor_.w = 1.0f;



    // Setup Style
    ImGuiStyle& Style = ImGui::GetStyle();

    // Hardcoded Transparency
    Style.Alpha = 1.0f;

    Logger_->Log("Reading Theme For Value: 'FrameRounding'", 1);
    Style.FrameRounding = ThemeNode["FrameRounding"].as<float>();

    Style.Colors[ImGuiCol_Text] = ReadColor("TextColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'DisabledTextColor'", 1);
    Style.Colors[ImGuiCol_TextDisabled] = ReadColor("DisabledTextColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'WindowBackgroundColor'", 1);
    Style.Colors[ImGuiCol_WindowBg] = ReadColor("WindowBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ChildBackgroundColor'", 1);
    Style.Colors[ImGuiCol_ChildBg] = ReadColor("ChildBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'PopupBackgroundColor'", 1);
    Style.Colors[ImGuiCol_PopupBg] = ReadColor("PopupBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'BorderColor'", 1);
    Style.Colors[ImGuiCol_Border] = ReadColor("BorderColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'BorderShadowColor'", 1);
    Style.Colors[ImGuiCol_BorderShadow] = ReadColor("BorderShadowColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'FrameBackgroundColor'", 1);
    Style.Colors[ImGuiCol_FrameBg] = ReadColor("FrameBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'FrameBackgroundHoveredColor'", 1);
    Style.Colors[ImGuiCol_FrameBgHovered] = ReadColor("FrameBackgroundHoveredColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'FrameBackgroundActiveColor'", 1);
    Style.Colors[ImGuiCol_FrameBgActive] = ReadColor("FrameBackgroundActiveColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'TitleBackgroundColor'", 1);
    Style.Colors[ImGuiCol_TitleBg] = ReadColor("TitleBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'TitleBackgroundCollapsedColor'", 1);
    Style.Colors[ImGuiCol_TitleBgCollapsed] = ReadColor("TitleBackgroundCollapsedColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'TitleBackgroundActiveColor'", 1);
    Style.Colors[ImGuiCol_TitleBgActive] = ReadColor("TitleBackgroundActiveColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'TitleBarColor'", 1);
    Style.Colors[ImGuiCol_MenuBarBg] = ReadColor("TitleBarColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ScrollbarBackgroundColor'", 1);
    Style.Colors[ImGuiCol_ScrollbarBg] = ReadColor("ScrollbarBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ScrollbarBackgroundColor'", 1);
    Style.Colors[ImGuiCol_ScrollbarBg] = ReadColor("ScrollbarBackgroundColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ScrollbarGrabColor'", 1);
    Style.Colors[ImGuiCol_ScrollbarGrab] = ReadColor("ScrollbarGrabColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ScrollbarHoveredColor'", 1);
    Style.Colors[ImGuiCol_ScrollbarGrabHovered] = ReadColor("ScrollbarHoveredColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'ScrollbarActiveColor'", 1);
    Style.Colors[ImGuiCol_ScrollbarGrabActive] = ReadColor("ScrollbarActiveColor", ThemeNode);

    Logger_->Log("Reading Theme For Value: 'CheckmarkColor'", 1);
    Style.Colors[ImGuiCol_CheckMark] = ReadColor("CheckmarkColor", ThemeNode);


    Style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    Style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    Style.Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    Style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    Style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    Style.Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    Style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    Style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    Style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    Style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    Style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    Style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    Style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    Style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    Style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    Style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);


}

