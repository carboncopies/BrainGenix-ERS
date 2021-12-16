//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a single I/O interface for asset loading/saving.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-19
*/

#include <ERS_InputOutputSubsystem.h>


// Constructor
ERS_CLASS_InputOutputSubsystem::ERS_CLASS_InputOutputSubsystem(std::shared_ptr<LoggerClass> Logger, YAML::Node SystemConfiguration) {

    // Copy Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Input/Output Subsystem", 5);

    // Get Database Loading / File Loading Config
    Logger_->Log("Reading Configuration For 'BOOL' 'UseDatabaseLoading'", 1);
    try {
        UseDatabase_ = SystemConfiguration["UseDatabaseLoading"].as<bool>();
    } 
    catch(YAML::TypedBadConversion<bool>) { // Config Param Doesn't Exist
        Logger_->Log("Configuration Error, Parameter 'UseDatabaseLoading' Is Not In Config, System Will Default To False", 8);
        UseDatabase_ = false;
    }

    // If Using DB Loading, Get DB Params
    if (UseDatabase_) {
        Logger_->Log("Database Loading Enabled, Reading Config For Database Parameters", 5);

        /*

            DATABASE LOADING STUFF HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        */

    } else {
        Logger_->Log("Database Lading Disabled, Reading Config For Asset Path", 5);

        try {
            Logger_->Log("Reading Configuration For 'STRING' 'AssetPath'", 1);
            AssetPath_ = SystemConfiguration["AssetPath"].as<std::string>();
        } catch (YAML::TypedBadConversion<std::string>) {
            Logger_->Log("Configuration Error, Parameter 'AssetPath' Is Not In Config, System Will Exit", 10);
            exit(1);
        }

    }


    // Index Already Used AssetIDs
    IndexUsedAssetIDs();


}



// Destructor
ERS_CLASS_InputOutputSubsystem::~ERS_CLASS_InputOutputSubsystem() {

    // Log Destructor Call
    Logger_->Log("Input/Output Subsystem Destructor Called", 6);

}


// Index Asset IDs
void ERS_CLASS_InputOutputSubsystem::IndexUsedAssetIDs() {

    // Log Start
    Logger_->Log("Indexing Used Asset IDs");
    UsedAssetIDs_ = std::vector<long>();

    // If Using Database Loading
    if (UseDatabase_) {

        // Do Database Indexing here...

    } else { // Default To Regular File Loading

        // Get List Of Files At Path
        for (const auto &Entry : std::filesystem::recursive_directory_iterator(std::string(AssetPath_))) {

            // Get File Path        
            std::string FilePath{Entry.path().u8string()};

            // Convert To Long, Throw Log Message If Not Number
            long ID = (long)FilePath.substr(0, FilePath.find_last_of(".")).c_str();

            // Append To Used IDs
            UsedAssetIDs_.push_back(ID);

            // Log Checked Out ID
            Logger_->Log(std::string(std::string("AssetID '") + std::to_string(ID) + std::string("' In Use")).c_str(), 3);

        }

    }

    // Summarize Checked Out IDs
    Logger_->Log(std::string(std::string("Identified ") + std::to_string(UsedAssetIDs_.size()) + std::string(" Asset IDs Are In Use")).c_str(), 4);

}

// Read Assets From File/DB, Return Bytes
bool ERS_CLASS_InputOutputSubsystem::ReadAsset(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> OutputData) {


    // Start Clock To Measure File Metadata
    auto StartTime = std::chrono::high_resolution_clock::now();
    bool ReadSuccess = false;
    float FileSize = 0;


    // If Database Loading
    if (UseDatabase_) {

        // Load From DB
        

    } else {

        // Generate File Path
        std::string FilePath = AssetPath_ + std::to_string(AssetID) + std::string(".ERS");

        struct stat Buffer;
        int FileStatus = stat(FilePath.c_str(), &Buffer);
        FileSize = Buffer.st_size;


        if (FileStatus == 0) {

            // Allocate Memory
            OutputData->Data = (unsigned char*)malloc(Buffer.st_size * sizeof(unsigned char));
            if (OutputData->Data) {

                FILE *Stream = fopen(FilePath.c_str(), "rb");
                if (Stream) {

                    fread(OutputData->Data, sizeof(unsigned char), Buffer.st_size, Stream);
                    fclose(Stream);
                    OutputData->HasLoaded = true;
                    ReadSuccess = true;

                } else {
                    Logger_->Log(std::string(std::string("Error Loading Asset '") + std::to_string(AssetID) + std::string("', Failed To Open Filestream")).c_str(), 9);
                    OutputData->HasLoaded = false;
                    ReadSuccess = false;
                }

            } else {
                Logger_->Log(std::string(std::string("Error Loading Asset '") + std::to_string(AssetID) + std::string("', Memory Allocation Failed")).c_str(), 9);            
                OutputData->HasLoaded = false;
                ReadSuccess = false;
            }

        
        } else {
            Logger_->Log(std::string(std::string("Error Loading Asset '") + std::to_string(AssetID) + std::string("', File Not Found")).c_str(), 9);
            OutputData->HasLoaded = false;
            ReadSuccess = false;
        }

    }


    // Measure End Time, Calculate Metadata
    auto FinishTime = std::chrono::high_resolution_clock::now();
    float Duration = std::chrono::duration<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(FinishTime - StartTime)).count();

    OutputData->LoadTime_s = Duration;
    OutputData->Size_B = FileSize;
    OutputData->Size_KB = FileSize / 1000;
    OutputData->Size_MB = FileSize / 1000000;
    OutputData->Size_GB = FileSize / 1000000000;

    OutputData->LoadSpeed_KBs = (FileSize / 1000) / Duration;
    OutputData->LoadSpeed_MBs = (FileSize / 1000000) / Duration; 
    OutputData->LoadSpeed_GBs = (FileSize / 1000000000) / Duration; 

    // Return Data
    return ReadSuccess;

}

// Write Data
bool ERS_CLASS_InputOutputSubsystem::WriteAsset(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> InputData) {

// Start Clock To Measure File Metadata
    auto StartTime = std::chrono::high_resolution_clock::now();
    bool Success = false;

    // If Database Loading
    if (UseDatabase_) {

        // Load From DB
        

    } else {

        // Generate File Path
        std::string FilePath = AssetPath_ + std::to_string(AssetID) + std::string(".ERS");

        // Check Filesize
        if (InputData->Size_B > 0) {

            FILE *Stream = fopen(FilePath.c_str(), "wb");

            if (Stream) {

                fwrite(InputData->Data, 1, sizeof(unsigned char)*InputData->Size_B, Stream);
                fclose(Stream);
                Success = true;

            } else {
                Logger_->Log(std::string(std::string("Error Writing Asset '") + std::to_string(AssetID) + std::string("', Failed To Open Filestream")).c_str(), 9);
                Success = false;
            }

        } else {
            Logger_->Log(std::string(std::string("Error Writing Asset '") + std::to_string(AssetID) + std::string("', Indicated 'Size_B' Is Invalid")).c_str(), 9);
            Success = false;
        }

    }


    // Measure End Time, Calculate Metadata
    auto FinishTime = std::chrono::high_resolution_clock::now();
    float Duration = std::chrono::duration<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(FinishTime - StartTime)).count();

    InputData->WriteTime_s = Duration;

    InputData->WriteSpeed_KBs = (InputData->Size_B / 1000) / Duration;
    InputData->WriteSpeed_MBs = (InputData->Size_B / 1000000) / Duration; 
    InputData->WriteSpeed_GBs = (InputData->Size_B / 1000000000) / Duration; 


    // Return Data
    return Success;

}