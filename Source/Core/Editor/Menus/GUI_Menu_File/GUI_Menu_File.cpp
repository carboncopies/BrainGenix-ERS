//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_File.h>

namespace {

std::string ERS_FUNCTION_NormalizePathString(ghc::filesystem::path Path) {

    std::string Output = ghc::filesystem::absolute(Path).u8string();
    while ((Output.size() > 1) && ((Output.back() == '/') || (Output.back() == '\\'))) {
        Output.pop_back();
    }
    return Output;

}

bool ERS_FUNCTION_IsSameOrChildPath(const ghc::filesystem::path& Path, const ghc::filesystem::path& PossibleParent) {

    std::string NormalizedPath = ERS_FUNCTION_NormalizePathString(Path);
    std::string NormalizedParent = ERS_FUNCTION_NormalizePathString(PossibleParent);

    if (NormalizedPath == NormalizedParent) {
        return true;
    }

    if (NormalizedParent.back() != '/') {
        NormalizedParent += "/";
    }

    return NormalizedPath.rfind(NormalizedParent, 0) == 0;

}

} // namespace


GUI_Menu_File::GUI_Menu_File(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;
    Windows_ = Windows;

    SystemUtils_->Logger_->Log("Editor Setting Up File Menu", 4);

    SceneWriter_ = std::make_unique<SceneWriter>(SystemUtils_);


}

GUI_Menu_File::~GUI_Menu_File() {

    SystemUtils_->Logger_->Log("Editor Destroying File Menu", 4);

}

void GUI_Menu_File::SaveCurrentProject() {

    SystemUtils_->Logger_->Log("Saving Project Data", 4);
    ProjectUtils_->ProjectManager_->WriteProject(1);

    SystemUtils_->Logger_->Log("Saving All Scenes", 4);
    for (int i = 0; (long)i < (long)SceneManager_->Scenes_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string("Saving Data For Scene ") + std::to_string(i), 3);
        SceneWriter_->ProcessScene(
            SceneManager_->Scenes_[i].get(),
            SceneManager_->Scenes_[i]->ScenePath
            );
    }

}

void GUI_Menu_File::DrawExportProjectDialog() {

    if (ImGuiFileDialog::Instance()->Display("Export Project", ImGuiWindowFlags_None, ImVec2(800, 500))) {

        if (ImGuiFileDialog::Instance()->IsOk()) {
            ghc::filesystem::path ExportDirectory = ImGuiFileDialog::Instance()->GetCurrentPath();
            SystemUtils_->Logger_->Log(std::string("Exporting Project To Directory '") + ExportDirectory.u8string() + "'", 5);

            SaveCurrentProject();
            ExportCurrentProject(ExportDirectory);
        }

        ImGuiFileDialog::Instance()->Close();
    }

}

ghc::filesystem::path GUI_Menu_File::GetCurrentProjectDirectory() {

    for (unsigned long i = 0; i < SystemUtils_->Arguments_.size(); i++) {
        if (SystemUtils_->Arguments_[i].first == std::string("ProjectDirectory")) {
            return ghc::filesystem::path(SystemUtils_->Arguments_[i].second);
        }
    }

    if (SystemUtils_->LocalSystemConfiguration_ != nullptr) {
        YAML::Node DefaultProjectDirectory = (*SystemUtils_->LocalSystemConfiguration_)["DefaultProjectDirectory"];
        if (DefaultProjectDirectory.IsDefined()) {
            return ghc::filesystem::path(DefaultProjectDirectory.as<std::string>());
        }
    }

    return ghc::filesystem::path();

}

bool GUI_Menu_File::ExportCurrentProject(ghc::filesystem::path ExportDirectory) {

    ghc::filesystem::path SourceDirectory = GetCurrentProjectDirectory();
    if (SourceDirectory.empty()) {
        SystemUtils_->Logger_->Log("Cannot Export Project, Current Project Directory Is Unknown", 8);
        return false;
    }

    SourceDirectory = ghc::filesystem::absolute(SourceDirectory);
    ExportDirectory = ghc::filesystem::absolute(ExportDirectory);

    if (!ghc::filesystem::exists(SourceDirectory) || !ghc::filesystem::is_directory(SourceDirectory)) {
        SystemUtils_->Logger_->Log(std::string("Cannot Export Project, Source Directory Does Not Exist: ") + SourceDirectory.u8string(), 8);
        return false;
    }

    if (ERS_FUNCTION_IsSameOrChildPath(ExportDirectory, SourceDirectory)) {
        SystemUtils_->Logger_->Log("Cannot Export Project Into The Active Project Directory", 8);
        return false;
    }

    try {
        ghc::filesystem::create_directories(ExportDirectory);

        std::string SourcePrefix = ERS_FUNCTION_NormalizePathString(SourceDirectory);
        if (SourcePrefix.back() != '/') {
            SourcePrefix += "/";
        }

        for (const auto& Entry : ghc::filesystem::recursive_directory_iterator(SourceDirectory)) {
            ghc::filesystem::path SourcePath = Entry.path();
            std::string SourcePathString = SourcePath.u8string();
            if (SourcePathString.rfind(SourcePrefix, 0) != 0) {
                continue;
            }

            std::string RelativePath = SourcePathString.substr(SourcePrefix.size());
            ghc::filesystem::path TargetPath = ExportDirectory / RelativePath;

            if (ghc::filesystem::is_directory(SourcePath)) {
                ghc::filesystem::create_directories(TargetPath);
            } else if (ghc::filesystem::is_regular_file(SourcePath)) {
                ghc::filesystem::create_directories(TargetPath.parent_path());
                ghc::filesystem::copy_file(SourcePath, TargetPath, ghc::filesystem::copy_options::overwrite_existing);
            }
        }
    } catch (const ghc::filesystem::filesystem_error& Error) {
        SystemUtils_->Logger_->Log(std::string("Failed To Export Project: ") + Error.what(), 8);
        return false;
    }

    SystemUtils_->Logger_->Log(std::string("Finished Exporting Project To '") + ExportDirectory.u8string() + "'", 4);
    return true;

}

void GUI_Menu_File::Draw() {

    // File Menu
    if (ImGui::BeginMenu("File")) {

        ImGui::MenuItem("New", "", &Windows_->GUI_Window_NewProject_->Enabled_);
        ImGui::MenuItem("Open", "", &Windows_->GUI_Window_OpenProject_->Enabled_);
        ImGui::Separator();


        ImGui::Separator();
        if (ImGui::MenuItem("Save")) {
            SaveCurrentProject();
        }
        if (ImGui::MenuItem("Export Project")) {
            ImGuiFileDialog::Instance()->OpenDialog("Export Project", "Export Project", nullptr, "~", "", 0);
        }

        ImGui::MenuItem("Project Settings", "", &Windows_->GUI_Window_ProjectSettings_->Enabled_);
        ImGui::MenuItem("About", "", &Windows_->GUI_Window_About_->Enabled_);

        ImGui::Separator();

        ImGui::MenuItem("Import Model", "", &Windows_->GUI_Window_ImportModel_->Enabled_);
        ImGui::MenuItem("Import Models In Directory", "", &Windows_->GUI_Window_ImportModelDirectory_->Enabled_);

        ImGui::Separator();

        // Exit Options
        if (ImGui::MenuItem("Exit")) {
            *SystemUtils_->SystemShouldRun_ = false;
        }

        
    ImGui::EndMenu();
    }

    DrawExportProjectDialog();


}
