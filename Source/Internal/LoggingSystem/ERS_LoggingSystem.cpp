//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include "ERS_LoggingSystem.h"



ERS_CLASS_LoggingSystem::ERS_CLASS_LoggingSystem(YAML::Node SystemConfiguration) {

    LocalSystemConfiguration = SystemConfiguration;

    PrintLogOutput = SystemConfiguration["EnablePrintOutput"].as<bool>();
    MinimumLogLevel = SystemConfiguration["SetMinimumLogLevel"].as<int>();
    ColorizeLog = SystemConfiguration["ColorizeLogOutput"].as<bool>();
    ReplaceLevelWithText = SystemConfiguration["UseTextLogLevel"].as<bool>();
    UseTextLogLevel_ = SystemConfiguration["UseTextLogLevel"].as<bool>();

    // Read Log Level Colors
    YAML::Node ColorsNode = SystemConfiguration["LogLevelColors"];
    for (YAML::const_iterator it=ColorsNode.begin(); it!=ColorsNode.end(); ++it) {
        ColorLookup_[it->first.as<int>()] = {
            it->second[0].as<int>(),
            it->second[1].as<int>(),
            it->second[2].as<int>()
        };
    }

    // Read Log Level Names
    YAML::Node NameNode = SystemConfiguration["LogLevelNames"];
    for (YAML::const_iterator it=NameNode.begin(); it!=NameNode.end(); ++it) {

        LogNameLookup_[it->first.as<int>()] = {
            it->second.as<std::string>()
        };

    }

    // Print Log Key
    if (PrintLogOutput) {
        std::cout << "[ Level] [               Time] [Message]\n";
    };


}

ERS_CLASS_LoggingSystem::~ERS_CLASS_LoggingSystem() {

    Log("System Logger Destructor Called, Logger Shutting Down", 6);

}


void ERS_CLASS_LoggingSystem::Log(std::string LogMessage, int LogLevel, bool Enable) {

    if (Enable) {
        LogItem(LogMessage.c_str(), LogLevel);
    }

}

void ERS_CLASS_LoggingSystem::Log(const char* LogMessage, int LogLevel, bool Enable) {

    if (Enable) {
        LogItem(LogMessage, LogLevel);
    }

}



void ERS_CLASS_LoggingSystem::LogItem(const char* LogItem, int LogLevel) {

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
    std::string LogLevelPadded;
    if (UseTextLogLevel_) {
        LogLevelPadded = LogNameLookup_[LogLevel];
    } else {
        LogLevelPadded = std::to_string(LogLevel);
    }
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


    // Add To Log Output Vars
    std::unique_lock<std::mutex> Lock(LogMutex_);

    LogMessages_.push_back(std::string(LogItem));
    LogLevels_.push_back(LogLevel);
    LogTimes_.push_back(CurrentTime);
    LogColors_.push_back(ColorLookup_[LogLevel]);
    FullLogMessages_.push_back(Output);

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

void ERS_CLASS_LoggingSystem::ColorizeText(std::string Message, int LogLevel) {

    ERS_STRUCT_RGBColor ColorValue = ColorLookup_[LogLevel];

    std::string RedString = std::to_string(ColorValue.Red);
    std::string GreenString = std::to_string(ColorValue.Green);
    std::string BlueString = std::to_string(ColorValue.Blue);

    std::string ColorPrefix = std::string("\x1b[38;2;") + RedString + std::string(";") + GreenString + std::string(";") + BlueString + std::string("m");
    std::string ColorSuffix = "\x1b[0m";

    // Colorize String
    std::string ColorString = ColorPrefix + Message + ColorSuffix;

    // Print Output To COUT
    std::cout << ColorString;
}