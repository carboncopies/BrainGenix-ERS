//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides asset import functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-18
*/

#include <GUI_ImportAsset.h>


// Asset Importer Constructor
GUI_ImportAsset::GUI_ImportAsset(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Shared Pointer
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing Asset Importer GUI", 5);

    // Instantiate
    Window_ImportProgressBar_ = std::make_unique<Window_ImportProgressBar>(SystemUtils_);
    AssetImportBackend_ = std::make_unique<ERS_CLASS_ImportAsset>(SystemUtils_);

}


// Asset Importer Destructor
GUI_ImportAsset::~GUI_ImportAsset() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Asset Importer GUI Destructor Called", 6);

}


// Draw
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
    // close
    ImGuiFileDialog::Instance()->Close();
    }


    // Update Window Stats
    std::cout<<AssetImportBackend_->HasJobFinished()<<std::endl;
    if (Window_ImportProgressBar_->Enabled_) {
        Window_ImportProgressBar_->UpdateTotalItems(AssetImportBackend_->GetTotalItemsImported(), AssetImportBackend_->GetTotalItemsToImport());
        Window_ImportProgressBar_->UpdateJobState(AssetImportBackend_->HasJobFinished());
    }

    Window_ImportProgressBar_->Draw();


}

// Open File Dialog
void GUI_ImportAsset::OpenFileDialog() {

    // Open Dialog
    ImGuiFileDialog::Instance()->OpenDialog("ImportModel", "Import", ".gltf,.obj,.fbx,.ply,.blend,.*", ".", "", 0);


}