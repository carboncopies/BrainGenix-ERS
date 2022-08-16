//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_ImportModel.h>


GUI_Window_ImportModel::GUI_Window_ImportModel(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Importer GUI", 5);

    GUI_Window_ImportProgressBar_ = std::make_unique<GUI_Window_ImportProgressBar>(SystemUtils_);
    AssetImportBackend_ = std::make_unique<ERS_CLASS_ImportAsset>(SystemUtils_);

}


GUI_Window_ImportModel::~GUI_Window_ImportModel() {

    SystemUtils_->Logger_->Log("Asset Importer GUI Destructor Called", 6);

}


void GUI_Window_ImportModel::Draw() {

    // Draw File Dialog
    if (ImGuiFileDialog::Instance()->Display("Import Model", ImGuiWindowFlags_None, ImVec2(800, 500))) {


        if (ImGuiFileDialog::Instance()->IsOk())
        {
            // Get List Of Files From Selection, Convert To Vector
            std::vector<std::string> FilePaths;
            std::map<std::string, std::string> selection = ImGuiFileDialog::Instance()->GetSelection(); // multiselection
            for (const auto& elem:selection) {
                FilePaths.push_back(elem.second);
            }

            // Add To Queue, Launch Import
            //AssetImportBackend_->AddToImportQueue(FilePaths);
            ProjectUtils_->
            GUI_Window_ImportProgressBar_->Enabled_ = true;

        }

    ImGuiFileDialog::Instance()->Close();
    }


    // Update Window Stats
    if (GUI_Window_ImportProgressBar_->Enabled_) {
        GUI_Window_ImportProgressBar_->UpdateTotalItems(AssetImportBackend_->GetTotalItemsImported(), AssetImportBackend_->GetTotalItemsToImport());
        GUI_Window_ImportProgressBar_->UpdateJobState(AssetImportBackend_->HasJobFinished());
    }

    GUI_Window_ImportProgressBar_->Draw();


}

void GUI_Window_ImportModel::OpenFileDialog() {

    ImGuiFileDialog::Instance()->OpenDialog("Import Model", "Import Model", ".*", ".", "", 0);


}