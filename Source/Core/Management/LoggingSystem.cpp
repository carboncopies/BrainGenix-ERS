//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the logger system used by the rest of the system.
    Additonal Notes: None
    Date Created: 2021-05-31
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <iomanip>


class LoggerClass {

    // Define "Local" Variables And Functions //
    private: 

        // Define Local Vars //
        bool PrintLogOutput;
        int MinimumLogLevel = 5;


        //-----------------------------------------------------------------------------------//
        // NOTE: LOG LEVELS ARE AS FOLLOWS:                                                  //
        // The smaller the number, the less important the information.                       //
        // Log lvl 0 is the least important, and is just debugging information essentially.  //
        //-----------------------------------------------------------------------------------//


        // Returns A String Of The Current UTC Time //
        std::string Get_UTC_Time() { 
            
            // Get UTC String //
            time_t CurrentTime = std::time(0);
            char* UTCString = ctime(&CurrentTime);

            // Remove New Line From String //
            if (UTCString[strlen(UTCString) - 1] == '\n') {
                UTCString[strlen(UTCString) - 1] = '\0';
            }

            return UTCString;
        }

        // Create Function That Gets Callstack? //
        // Returns callstack as std::string?


    // Define Functions //
    public: 


        // Define Initialization Function //
        void InitializeLogger(YAML::Node SystemConfiguration) { // ** NOTE: THIS SHOULD TAKE A CONFIG DICT FROM YAML IN THE FUTRE ** //

            // Update Local Config Parameters //
            PrintLogOutput = SystemConfiguration["EnablePrintOutput"].as<bool>();
            MinimumLogLevel = SystemConfiguration["SetMinimumLogLevel"].as<int>();

            // Print Log Key //
            if (PrintLogOutput) {
                std::cout << "[Level] [Time] [Message]\n";
            };

        };

        // Log An Item //
        void Log(const char* LogItem, int LogLevel=5) {

            // Get Current Time In YYYY-MM-DD-HH-MM-SS Format
            std::time_t RawCurrentTime;
            std::tm* TimeInformation;
            char TimeBuffer [80];

            std::time(&RawCurrentTime);
            TimeInformation = std::localtime(&RawCurrentTime);

            std::strftime(TimeBuffer, 80, "%Y-%m-%d_%H-%M-%S", TimeInformation);
            std::string CurrentTime = std::string(TimeBuffer);

            // Create Output Strings //
            std::string Output;

            // Pad Strings
            std::string LogLevelPadded = std::to_string(LogLevel);
            std::string CurrentTimePadded = std::string(CurrentTime);

            


            // Combine Strings //
            Output += "[" + LogLevelPadded + "] ";
            Output += "[" + CurrentTime + "] ";
            Output += std::string(LogItem) + "\n";

            // Check Log Level Before Printing It //
            if (LogLevel >= MinimumLogLevel) {

                // If Log Print Enabled //
                if (PrintLogOutput) {
                    std::cout << Output;
                };

            };

        }

};