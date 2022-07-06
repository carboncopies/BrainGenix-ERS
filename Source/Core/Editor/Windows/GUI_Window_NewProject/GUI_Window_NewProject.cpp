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


void GUI_Window_NewProject::Draw() {

    if (Enabled_ && !LastWindowState_) {
        ImGuiFileDialog::Instance()->OpenDialog("New Project", "New Project", ".ERS", ".", "", 0);
    }

    if (Enabled_) {

        // Draw File Dialog
        if (ImGuiFileDialog::Instance()->Display("New Project", ImGuiWindowFlags_None, ImVec2(400, 200))) {


            if (ImGuiFileDialog::Instance()->IsOk())
            {
               
                std::string Path = ImGuiFileDialog::Instance()->GetCurrentPath();
                Path += "/";
                SystemUtils_->Logger_->Log(std::string("Newing Project At Path '") + Path + "'", 5);
                
                std::string Command;
                
#if defined(_WIN32)
                Command += "";
#elif defined(__APPLE__)
                Command += "./";
#else
                Command += "./";
#endif
                Command += "BrainGenix-ERS -ProjectDirectory ";
                Command += '"' + Path + '"' + " &";
                std::system(Command.c_str());

                // Quit System
                SystemUtils_->Logger_->Log("Shutting Down This Editor Window Now", 5);
                *SystemUtils_->SystemShouldRun_ = false;
        

            }

        ImGuiFileDialog::Instance()->Close();
        }




    }

    LastWindowState_ = Enabled_;


}
