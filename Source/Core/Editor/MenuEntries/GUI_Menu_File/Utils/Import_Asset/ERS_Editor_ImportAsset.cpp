//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_ImportAsset.h>


ERS_CLASS_ImportAsset::ERS_CLASS_ImportAsset(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Importer Backend", 5);

    SystemUtils_->Logger_->Log("Starting Asset Import Thread", 4);
    ImportThread_ = std::thread(&ERS_CLASS_ImportAsset::ImportThread, this);
    SystemUtils_->Logger_->Log("Started Asset Import Thread", 3);

}


ERS_CLASS_ImportAsset::~ERS_CLASS_ImportAsset() {

    SystemUtils_->Logger_->Log("Asset Importer Backend Destructor Called", 6);

    SystemUtils_->Logger_->Log("Sending Halt Signal To Asset Import Thread", 4);
    BlockThread_.lock();
    StopThread_ = true;
    BlockThread_.unlock();

    SystemUtils_->Logger_->Log("Joining Asset Import Thread", 3);
    ImportThread_.join();

}

// Item Import Thread
void ERS_CLASS_ImportAsset::ImportThread() {

    // Create Importer Instance
    std::unique_ptr<ERS_CLASS_ModelImporter> AssetImporter = std::make_unique<ERS_CLASS_ModelImporter>(SystemUtils_);

    while (true) {

        // Check Control Variables
        BlockThread_.lock();
        if (StopThread_) {
            BlockThread_.unlock();
            break;
        }
        BlockThread_.unlock();

        // Check Queue, Import As Needed
        LockAssetImportQueue_.lock();
        if (AssetImportQueue_.size() > 0) {

            HasJobFinished_ = false;
            std::string AssetPath = AssetImportQueue_[0];
            AssetImportQueue_.erase(AssetImportQueue_.begin());
            LockAssetImportQueue_.unlock();


            AssetImporter->ImportModel(AssetPath);

            LockAssetImportQueue_.lock();
            TotalItemsProcessed_++;
            LockAssetImportQueue_.unlock();
        } else {
            
            HasJobFinished_ = true;
            TotalItemsToImport_ = 0;
            TotalItemsProcessed_ = 0;
            LockAssetImportQueue_.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

    }

}

void ERS_CLASS_ImportAsset::AddToImportQueue(std::vector<std::string> AssetPaths) {

    SystemUtils_->Logger_->Log("Appending Assets To Asset Import Queue", 5);
    LockAssetImportQueue_.lock();

    for (int i = 0; i < AssetPaths.size(); i++) {

        std::string LogStr = std::string("Appending Asset: '") + AssetPaths[i] + std::string("' To Import Queue");
        SystemUtils_->Logger_->Log(LogStr.c_str(), 4);
        AssetImportQueue_.push_back(AssetPaths[i]);
        TotalItemsToImport_ += 1;

    }

    LockAssetImportQueue_.unlock();

}



long ERS_CLASS_ImportAsset::GetTotalItemsToImport() {
    return TotalItemsToImport_;
}

long ERS_CLASS_ImportAsset::GetTotalItemsImported() {
    return TotalItemsProcessed_;
}

bool ERS_CLASS_ImportAsset::HasJobFinished() {
    LockAssetImportQueue_.lock();
    bool Out = HasJobFinished_;
    LockAssetImportQueue_.unlock();
    return Out;
}