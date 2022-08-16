//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ImportModelDirectory.h>


GUI_Window_ImportModelDirectory::GUI_Window_ImportModelDirectory(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Importer GUI", 5);

    GUI_Window_ImportProgressBar_ = std::make_unique<GUI_Window_ImportProgressBar>(SystemUtils_);

}


GUI_Window_ImportModelDirectory::~GUI_Window_ImportModelDirectory() {

    SystemUtils_->Logger_->Log("Asset Importer GUI Destructor Called", 6);

}

// Check String Endings (From: https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c)
bool EndsWith(const std::string& Input, const std::string& Ending) {
    if (Ending.size() > Input.size()) return false;
    return std::equal(Input.begin() + Input.size() - Ending.size(), Input.end(), Ending.begin());
}


void GUI_Window_ImportModelDirectory::Draw() {

    if (Enabled_ && !AlreadyOpen_) {
        OpenFileDialog();
        AlreadyOpen_ = true;
        GUI_Window_ImportProgressBar_->Enabled_ = true;
    }

    // Draw File Dialog
    if (ImGuiFileDialog::Instance()->Display("Import Model Directory", ImGuiWindowFlags_None, ImVec2(800, 500))) {


        if (ImGuiFileDialog::Instance()->IsOk())
        {
            // Get List Of Files From Selection, Convert To Vector
            std::vector<std::string> FilePaths;
            std::string Path = ImGuiFileDialog::Instance()->GetCurrentPath();
            Path += "/";

            for (const auto &Entry : std::filesystem::recursive_directory_iterator(Path)) {
                std::string FilePath{Entry.path().u8string()};
                if (EndsWith(FilePath, ".fbx") || EndsWith(FilePath, ".dae") || EndsWith(FilePath, ".obj") || EndsWith(FilePath, ".gltf") || EndsWith(FilePath, ".glb")) {
                    FilePaths.push_back(FilePath);
                }

            }

            // Add To Queue, Launch Import
            ProjectUtils_->ModelImporter_->AddToImportQueue(FilePaths);
            GUI_Window_ImportProgressBar_->Enabled_ = true;

        }

    ImGuiFileDialog::Instance()->Close();
    AlreadyOpen_ = false;
    Enabled_ = false;
    }


    // Update Window Stats
    if (GUI_Window_ImportProgressBar_->Enabled_ && Enabled_) {
        GUI_Window_ImportProgressBar_->UpdateTotalItems(ProjectUtils_->ModelImporter_->GetTotalItemsImported(), ProjectUtils_->ModelImporter_->GetTotalItemsToImport());
        GUI_Window_ImportProgressBar_->UpdateJobState(ProjectUtils_->ModelImporter_->HasJobFinished());
    }

    

}

void GUI_Window_ImportModelDirectory::OpenFileDialog() {

    ImGuiFileDialog::Instance()->OpenDialog("Import Model Directory", "Import Model Directory", nullptr, "~", "", 0);


}