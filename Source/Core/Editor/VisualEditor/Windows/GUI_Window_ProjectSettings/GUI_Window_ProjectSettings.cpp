//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#include <GUI_Window_ProjectSettings.h>


// Constructor
Window_ProjectSettings::Window_ProjectSettings(std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS GUI Window Project Settings", 5);

}

// Destructor
Window_ProjectSettings::~Window_ProjectSettings() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Window Project Settings Destructor Called", 6);

}


// Draw The Window, To Be Called Every Frame
void Window_ProjectSettings::Draw() {

    // Begin Window
    if (Enabled_) {
        ImGui::Begin("Project Settings", &Enabled_);
        ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);


        // Copy Project Info Into Vars ImGui Can Understand
        strcpy(ProjectNameBuffer, ProjectUtils_->ProjectManager_->Project_.ProjectName.c_str());
        strcpy(ProjectCreationDateBuffer, ProjectUtils_->ProjectManager_->Project_.ProjectCreationDate.c_str());
        strcpy(ProjectModificationDateBuffer, ProjectUtils_->ProjectManager_->Project_.ProjectModificationDate.c_str());
        strcpy(ProjectDescriptionBuffer, ProjectUtils_->ProjectManager_->Project_.ProjectDescription.c_str());
        strcpy(ProjectLicenseNameBuffer, ProjectUtils_->ProjectManager_->Project_.ProjectLicense.c_str());
        IsProjectFree = !ProjectUtils_->ProjectManager_->Project_.IsLicenseProprietary;

        // Add Project Metadata
        ImGui::InputTextWithHint("Project Name", "Enter Project Title", ProjectNameBuffer, 512);
        ImGui::InputTextMultiline("Project Description", ProjectDescriptionBuffer, 16384);

        ImGui::Separator();
        ImGui::InputTextWithHint("Project License", "Enter License Name Here", ProjectLicenseNameBuffer, 128);
        ImGui::Checkbox("Is License Free", &IsProjectFree);
        ImGui::SameLine();

        ImGui::HelpMarker("Checking this box indicates that your project and components are free and open source software.");

        // Check If Not Free, Present Warning
        if (!IsProjectFree) {
            ImGui::Separator();
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "WARNING: This project is not free and open source software!");
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "You may be subject to additional licensing restrictions and other nasty things.");
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "Try contacting the developers to see if they will change the license.");            
        }

        ImGui::Separator();

        ImGui::InputTextWithHint("Project Creation Date", "", ProjectCreationDateBuffer, 64, ImGuiInputTextFlags_ReadOnly);
        ImGui::InputTextWithHint("Project Modification Date", "", ProjectModificationDateBuffer, 64, ImGuiInputTextFlags_ReadOnly);



        ProjectUtils_->ProjectManager_->Project_.ProjectName = std::string(ProjectNameBuffer);
        ProjectUtils_->ProjectManager_->Project_.ProjectDescription = std::string(ProjectDescriptionBuffer);
        ProjectUtils_->ProjectManager_->Project_.ProjectLicense = std::string(ProjectLicenseNameBuffer);
        ProjectUtils_->ProjectManager_->Project_.IsLicenseProprietary = !IsProjectFree;


        ImGui::End();

    }

}