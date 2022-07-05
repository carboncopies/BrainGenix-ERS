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

ERS_CLASS_ArgumentParser::ParseArguments(int NumberArguments, char** ArgumentValues) {

    Logger_->Log("Argument Parser Invoked, Populating Internal State With Argument Data", 5);

    // Clear Args
    Logger_->Log("Clearing Internal State", 2);
    ArgumentPairs_.clear();
    Arguments_.clear();
    ArgumentString_ = "";
    Logger_->Log("Finished Clearing Internal State", 1);

    // Populate Argument List, Argument String
    Logger_->Log("Creating Argument Vector", 3);
    for (int i = 0; i < NumberArguments; i++) {

        std::string CurrentArgument = std::string(ArgumentValues[i]);
        ArgumentString_ += CurrentArgument + " ";
        Arguments_.push_back(CurrentArgument);

    }
    Logger_->Log("Finished Creating Argument Vector", 2);

    

    // Create Internal Argument Pairs
    Logger_->Log("Creating Argument Pair Vector", 4);
    std::vector<std::string> TmpArguments = Arguments_;
    TmpArguments.erase(TmpArguments.begin());
    for (unsigned int i = 0; i < (TmpArguments.size() / 2); i++) {
        
        // Should Skip Every Other Argument
        int Index = i*2;

        

    }
    Logger_->Log("Finished Creating Argument Pair Vector", 3);




//

}
