//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <DatabaseInterface.h>



// Database Interface Constructor
DatabaseInterface::DatabaseInterface(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {

    // Create Member Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Database Interface", 5);

}


// Database Interface Destructor
DatabaseInterface::~DatabaseInterface() {

    // Log Destructor Call
    Logger_->Log("Database Interface Destructor Called", 6);


}