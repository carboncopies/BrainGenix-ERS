//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ArgumentParser.h>


ERS_CLASS_ArgumentParser::ERS_CLASS_ArgumentParser(ERS_CLASS_LoggingSystem* Logger) {

    Logger_ = Logger;
    Logger_->Log("Initialiizng Argument Parser Subsystem", 4);

    ArgumentPairs_.clear();
    Arguments_.clear();
    ArgumentString_ = "";

}

ERS_CLASS_ArgumentParser::~ERS_CLASS_ArgumentParser() {

    Logger_->Log("Argument Parser Destructor Called", 6);

}



