//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_OpenProject.h>


GUI_Window_OpenProject::GUI_Window_OpenProject(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Seting Up Open Project Window Dialog", 5);

}


GUI_Window_OpenProject::~GUI_Window_OpenProject() {

    SystemUtils_->Logger_->Log("Open Project Window Dialog Destructor Called", 6);

}


void GUI_Window_OpenProject::Draw() {

    if (Enabled_ && !LastWindowState_) {
        ImGuiFileDialog::Instance()->OpenDialog("Open Project Folder", "Open Project Folder", ".*", ".", "", 0);
    }

    if (Enabled_) {

        // Draw File Dialog
        if (ImGuiFileDialog::Instance()->Display("Open Project Folder", ImGuiWindowFlags_None, ImVec2(400, 200))) {


            if (ImGuiFileDialog::Instance()->IsOk())
            {
                // Get List Of Files From Selection, Convert To Vector
                std::vector<std::string> FilePaths;
                std::map<std::string, std::string> selection = ImGuiFileDialog::Instance()->GetSelection(); // multiselection
                for (const auto& elem:selection) {
                    FilePaths.push_back(elem.second);
                }

                // Add To Queue, Launch Import


            }

        ImGuiFileDialog::Instance()->Close();
        }




    }

    LastWindowState_ = Enabled_;


}

void GUI_Window_OpenProject::OpenFileDialog() {

    


}