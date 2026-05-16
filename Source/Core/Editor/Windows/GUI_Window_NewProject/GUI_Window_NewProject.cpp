//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_NewProject.h>


GUI_Window_NewProject::GUI_Window_NewProject(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Seting Up New Project Window Dialog", 5);

}


GUI_Window_NewProject::~GUI_Window_NewProject() {

    SystemUtils_->Logger_->Log("New Project Window Dialog Destructor Called", 6);

}


std::string GUI_Window_NewProject::GetNewProjectTemplatePath() {

    std::string FallbackTemplatePath = "EditorAssets/Projects/NewProject/";
    if (SystemUtils_ == nullptr || SystemUtils_->LocalSystemConfiguration_ == nullptr) {
        return FallbackTemplatePath;
    }

    YAML::Node TemplatePath = (*SystemUtils_->LocalSystemConfiguration_)["NewProjectTemplateDirectory"];
    if (!TemplatePath) {
        return FallbackTemplatePath;
    }

    std::string ConfiguredPath = TemplatePath.as<std::string>();
    if (ConfiguredPath == "") {
        return FallbackTemplatePath;
    }

    return ConfiguredPath;

}


void GUI_Window_NewProject::Draw() {

    if (Enabled_ && !LastWindowState_) {
        ImGuiFileDialog::Instance()->OpenDialog("New Project", "New Project", nullptr, "~", "", 0);

    }

    if (Enabled_) {

        // Draw File Dialog
        if (ImGuiFileDialog::Instance()->Display("New Project", ImGuiWindowFlags_None, ImVec2(800, 500))) {


            if (ImGuiFileDialog::Instance()->IsOk())
            {
               
                std::string Path = ImGuiFileDialog::Instance()->GetCurrentPath();
                Path += "/";
                SystemUtils_->Logger_->Log(std::string("Creating New Project In Target Directory '") + Path + "'", 5);
    
                ghc::filesystem::path TemplateProjectPath(GetNewProjectTemplatePath());
                if (TemplateProjectPath.is_relative()) {
                    TemplateProjectPath = ghc::filesystem::current_path() / TemplateProjectPath;
                }

                ghc::filesystem::path TargetProjectPath(Path);
                bool ProjectTemplateCopied = false;

                if (!ghc::filesystem::exists(TemplateProjectPath) || !ghc::filesystem::is_directory(TemplateProjectPath)) {
                    SystemUtils_->Logger_->Log(std::string("Could Not Create New Project, Template Directory Does Not Exist: '") + TemplateProjectPath.u8string() + "'", 8);
                } else {
                    ProjectTemplateCopied = true;
                    for (const auto &Entry : ghc::filesystem::recursive_directory_iterator(TemplateProjectPath)) {
                        if (!ghc::filesystem::is_regular_file(Entry.path())) {
                            continue;
                        }

                        ghc::filesystem::path RelativePath = ghc::filesystem::relative(Entry.path(), TemplateProjectPath);
                        ghc::filesystem::path TargetFile = TargetProjectPath / RelativePath;
                        ghc::filesystem::create_directories(TargetFile.parent_path());
                        SystemUtils_->Logger_->Log(std::string("Copying File '") + Entry.path().u8string() + "' To New Project Directory", 4);
                        ghc::filesystem::copy_file(Entry.path(), TargetFile);

                    }
                }

                if (ProjectTemplateCopied) {

                    std::string Command;
#if defined(_WIN32)
                    Command += "start /B ";
#elif defined(__APPLE__)
                    Command += "./";
#else
                    Command += "./";
#endif
                    Command += "ERS -ProjectDirectory ";
                    Command += '"' + Path + '"' + " &";
                    int Status = std::system(Command.c_str());

                    // Quit System
                    if (Status != -1) {
                        SystemUtils_->Logger_->Log("Shutting Down This Editor Window Now, Launching Editor For That Project", 5);
                        *SystemUtils_->SystemShouldRun_ = false;
                    } else {
                        SystemUtils_->Logger_->Log("Failed To Launch New ERS Instance!", 8);
                    }
                }

            }

        ImGuiFileDialog::Instance()->Close();
        }




    }

    LastWindowState_ = Enabled_;


}
