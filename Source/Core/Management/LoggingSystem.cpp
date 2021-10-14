//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the logger system used by the rest of the system.
    Additonal Notes: None
    Date Created: 2021-05-31
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <map>
#include <list>

#include "Core/Management/LoggingSystem.h"






// Define LoggerClass::InitializeLogger //
void LoggerClass::InitializeLogger(YAML::Node SystemConfiguration) { // ** NOTE: THIS SHOULD TAKE A CONFIG DICT FROM YAML IN THE FUTRE ** //

    // Make Local Copy Of System Config
    LocalSystemConfiguration = SystemConfiguration;

    // Update Local Config Parameters //
    PrintLogOutput = SystemConfiguration["EnablePrintOutput"].as<bool>();
    MinimumLogLevel = SystemConfiguration["SetMinimumLogLevel"].as<int>();
    ColorizeLog = SystemConfiguration["ColorizeLogOutput"].as<bool>();
    ReplaceLevelWithText = SystemConfiguration["UseTextLogLevel"].as<bool>();

    //ColorLookup = SystemConfiguration["LogLevelColors"]; <--- FIX ME!


    // Print Log Key //
    if (PrintLogOutput) {
        std::cout << "[Level] [               Time] [Message]\n";
    };

};

// Define LoggerClass::Log //
void LoggerClass::Log(const char* LogItem, int LogLevel) {

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

    // Create Pad Strings
    std::string LogLevelPadded = std::to_string(LogLevel);
    std::string CurrentTimePadded = CurrentTime;

    // Pad Log Level Column
    int CurrentLogLevelLength = LogLevelPadded.length();
    if (CurrentLogLevelLength < LogLevelTargetWidth) {
        LogLevelPadded.insert(0, InsertString, LogLevelTargetWidth - CurrentLogLevelLength);
    }

    // Pad Time Column
    int CurrentTimeLength = CurrentTimePadded.length();
    if (CurrentTimeLength < LogTimeTargetWidth) {
        CurrentTimePadded.insert(0, InsertString, LogTimeTargetWidth - CurrentTimeLength);
    }

    // Combine Strings //
    Output += "[" + LogLevelPadded + "] ";
    Output += "[" + CurrentTimePadded + "] ";
    Output += std::string(LogItem) + "\n";

    // Check Log Level Before Printing It //
    if (LogLevel >= MinimumLogLevel) {

        // If Log Print Enabled //
        if (PrintLogOutput) {

            // If Colorize Enabled
            if (ColorizeLog) {
                ColorizeText(Output, LogLevel);
            } else {
                std::cout << Output;
            }
        };

    };

}

// Define LoggerClass::ColorizeText
void LoggerClass::ColorizeText(std::string Message, int LogLevel) {

    // Get Color Value
    int ColorList [3] = {0,255,0};//LocalSystemConfiguration[LogLevel]

    std::string RedString = std::to_string(ColorList[0]);
    std::string GreenString = std::to_string(ColorList[1]);
    std::string BlueString = std::to_string(ColorList[2]);

    std::string ColorPrefix = std::string("\x1b[38;2;") + RedString + std::string(";") + GreenString + std::string(";") + BlueString + std::string("m");
    std::string ColorSuffix = "\x1b[0m";

    // Colorize String
    std::string ColorString = ColorPrefix + Message + ColorSuffix;

    // Print Output To COUT
    std::cout << ColorString;
}