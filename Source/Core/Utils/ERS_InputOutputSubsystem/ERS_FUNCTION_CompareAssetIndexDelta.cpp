//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_CompareAssetIndexDelta.h>




// Delta Function
void ERS_FUNCTION_CompareIndexDelta(std::shared_ptr<LoggerClass> Logger_, std::shared_ptr<std::vector<long>> UsedAssetIDIndex, std::shared_ptr<ERS_CLASS_AssetIndexIOM> AssetIndexIOM) {

    // Log Delta Function Call
    Logger_->Log("Comparing Indexed Assets With Asset Metadata Index", 4);

    // Make Copy Of Used Asset ID Index To Check Against
    std::vector<long> RemainingAssetIDs = *UsedAssetIDIndex;

    // Iterate Through All Asset Index Metadata
    for (long i = 0; i < AssetIndexIOM->AssetIDsFound_.size(); i++) {



    }

    // Log Comparison Finish
    Logger_->Log("Finished Comparing Index With Metadata", 5);

}
