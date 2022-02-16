//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_ImportAsset.h>


GUI_ImportAsset::GUI_ImportAsset(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Importer GUI", 5);

    Window_ImportProgressBar_ = std::make_unique<Window_ImportProgressBar>(SystemUtils_);
    AssetImportBackend_ = std::make_unique<ERS_CLASS_ImportAsset>(SystemUtils_);

}


GUI_ImportAsset::~GUI_ImportAsset() {

    SystemUtils_->Logger_->Log("Asset Importer GUI Destructor Called", 6);

}


void GUI_ImportAsset::Draw() {

    // Draw File Dialog
    if (ImGuiFileDialog::Instance()->Display("ImportModel")) 
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            // Get List Of Files From Selection, Convert To Vector
            std::vector<std::string> FilePaths;
            std::map<std::string, std::string> selection = ImGuiFileDialog::Instance()->GetSelection(); // multiselection
            for (const auto& elem:selection) {
                FilePaths.push_back(elem.second);
            }

            // Add To Queue, Launch Import
            AssetImportBackend_->AddToImportQueue(FilePaths);
            Window_ImportProgressBar_->Enabled_ = true;

        }

    ImGuiFileDialog::Instance()->Close();
    }


    // Update Window Stats
    if (Window_ImportProgressBar_->Enabled_) {
        Window_ImportProgressBar_->UpdateTotalItems(AssetImportBackend_->GetTotalItemsImported(), AssetImportBackend_->GetTotalItemsToImport());
        Window_ImportProgressBar_->UpdateJobState(AssetImportBackend_->HasJobFinished());
    }

    Window_ImportProgressBar_->Draw();


}

void GUI_ImportAsset::OpenFileDialog() {

    ImGuiFileDialog::Instance()->OpenDialog("ImportModel", "Import", ".*", ".", "", 0);

}