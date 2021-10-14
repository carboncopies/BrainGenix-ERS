//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the logger system used by the rest of the system.
    Additonal Notes: None
    Date Created: 2021-05-31
*/




class LoggerClass {

    // Define "Local" Variables And Functions //
    private: 

        // Define Local Vars //
        YAML::Node LocalSystemConfiguration;


        bool PrintLogOutput;
        bool ColorizeLog;
        bool ReplaceLevelWithText;
        int MinimumLogLevel = 5;

        int LogLevelTargetWidth = 5;
        int LogTimeTargetWidth = 19;
        const char* InsertString = "                                                         ";


        //-----------------------------------------------------------------------------------//
        // NOTE: LOG LEVELS ARE AS FOLLOWS:                                                  //
        // The smaller the number, the less important the information.                       //
        // Log lvl 0 is the least important, and is just debugging information essentially.  //
        //-----------------------------------------------------------------------------------//

    public: 


        // Define Initialization Function //
        void InitializeLogger(YAML::Node SystemConfiguration);

        // Log An Item //
        void Log(const char* LogItem, int LogLevel=5);

        // Add ANSI Text Color Codes Based On Log Level
        void ColorizeText(std::string Message, int LogLevel);

};