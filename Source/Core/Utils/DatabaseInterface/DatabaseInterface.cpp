//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a simple class to interface with the ERS Databse schema.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-01-27
*/

#include <DatabaseInterface.h>



// Database Interface Constructor
DatabaseInterface::DatabaseInterface(LoggerClass *Logger) {

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