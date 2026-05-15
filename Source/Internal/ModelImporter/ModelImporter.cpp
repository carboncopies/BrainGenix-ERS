//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ModelImporter.h>


ERS_ModelImporter::ERS_ModelImporter(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Model Importer Subsystem", 5);

    // Setup Classes
    ModelWriter_ = std::make_unique<ERS_CLASS_ModelWriter>(SystemUtils_->Logger_.get(), SystemUtils_->ERS_IOSubsystem_.get());
    ModelLoader_ = std::make_unique<BrainGenix::ERS::Module::ExternalModelLoader>(SystemUtils_);

    SystemUtils_->Logger_->Log("Starting Asset Import Thread", 4);
    ImportThreadActive_ = true;
    ImportThread_ = std::thread(&ERS_ModelImporter::ImportThread, this);
    SystemUtils_->Logger_->Log("Started Asset Import Thread", 3);

    ERS_ModelWriter_ = std::make_unique<ERS_CLASS_ModelWriter>(
        SystemUtils->Logger_.get(),
        SystemUtils->ERS_IOSubsystem_.get()
    );


}


ERS_ModelImporter::~ERS_ModelImporter() {

    SystemUtils_->Logger_->Log("Asset Importer Backend Destructor Called", 6);

    SystemUtils_->Logger_->Log("Sending Halt Signal To Asset Import Thread", 4);
    {
        std::lock_guard<std::mutex> Lock(LockAssetImportQueue_);
        StopThread_ = true;
    }
    WorkAvailableCondition_.notify_all();

    {
        std::unique_lock<std::mutex> Lock(LockAssetImportQueue_);
        bool ImporterStopped = ImportThreadShutdownCondition_.wait_for(Lock, std::chrono::seconds(2), [this]() {
            return !ImportThreadActive_;
        });
        if (!ImporterStopped) {
            SystemUtils_->Logger_->Log("The asset import thread did not stop within 2 seconds. ERS will keep waiting for a clean shutdown instead of forcing termination.", 9);
        }
    }

    SystemUtils_->Logger_->Log("Joining Asset Import Thread", 3);
    if (ImportThread_.joinable()) {
        ImportThread_.join();
    }

}

// Item Import Thread
void ERS_ModelImporter::ImportThread() {

    // Name Thread
    SetThreadName("ImportManager");

    while (true) {
        std::string AssetPath;
        bool FlipTextures = false;

        {
            std::unique_lock<std::mutex> Lock(LockAssetImportQueue_);
            WorkAvailableCondition_.wait(Lock, [this]() {
                return StopThread_ || !AssetImportQueue_.empty();
            });

            if (StopThread_) {
                break;
            }

            HasJobFinished_ = false;
            AssetPath = AssetImportQueue_[0];
            FlipTextures = AssetQueueFlipTextures_[0];
            AssetImportQueue_.erase(AssetImportQueue_.begin());
            AssetQueueFlipTextures_.erase(AssetQueueFlipTextures_.begin());
        }

        ERS_STRUCT_Model Model;
        ERS_STRUCT_ModelWriterData ModelData;
        ModelData.Model = &Model;
        ModelLoader_->LoadModel(AssetPath, ModelData);
        ModelWriter_->WriteModel(ModelData, FlipTextures);

        {
            std::lock_guard<std::mutex> Lock(LockAssetImportQueue_);
            TotalItemsProcessed_++;
            if (AssetImportQueue_.empty()) {
                HasJobFinished_ = true;
                TotalItemsToImport_ = 0;
                TotalItemsProcessed_ = 0;
            }
        }

    }

    {
        std::lock_guard<std::mutex> Lock(LockAssetImportQueue_);
        HasJobFinished_ = true;
        ImportThreadActive_ = false;
    }
    ImportThreadShutdownCondition_.notify_all();

}


void ERS_ModelImporter::AddToImportQueue(std::vector<std::string> AssetPaths, std::vector<bool> FlipTextures) {

    SystemUtils_->Logger_->Log("Appending Assets To Asset Import Queue", 5);
    {
        std::lock_guard<std::mutex> Lock(LockAssetImportQueue_);
        HasJobFinished_ = false;
        for (int i = 0; (long)i < (long)AssetPaths.size(); i++) {

            std::string LogStr = std::string("Appending Asset: '") + AssetPaths[i] + std::string("' To Import Queue");
            SystemUtils_->Logger_->Log(LogStr.c_str(), 4);
            AssetImportQueue_.push_back(AssetPaths[i]);
            AssetQueueFlipTextures_.push_back(FlipTextures[i]);
            TotalItemsToImport_ += 1;

        }
    }
    WorkAvailableCondition_.notify_one();

}
long ERS_ModelImporter::GetTotalItemsToImport() {
    return TotalItemsToImport_;
}
long ERS_ModelImporter::GetTotalItemsImported() {
    return TotalItemsProcessed_;
}
bool ERS_ModelImporter::HasJobFinished() {
    std::lock_guard<std::mutex> Lock(LockAssetImportQueue_);
    return HasJobFinished_;
}