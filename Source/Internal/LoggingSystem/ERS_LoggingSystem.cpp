//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include "ERS_LoggingSystem.h"




ERS_LoggingSystem::ERS_LoggingSystem(YAML::Node SystemConfiguration) {

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


    // Get File Logging Configuration, Setup File Logging System
    if (SystemConfiguration["EnableLogFile"]) {
        EnableLogFile_ = SystemConfiguration["EnableLogFile"].as<bool>();
    }
    if (SystemConfiguration["LogFilePathPrefix"]) {
        LogFilePathPrefix_ = SystemConfiguration["LogFilePathPrefix"].as<std::string>();
    }

    std::string CurrentTime = GetFormattedTime();

    std::string LogFilePath = LogFilePathPrefix_ + CurrentTime + ".txt";
    if (EnableLogFile_) {
        //FileStream_.open(LogFilePath, std::ios_base::app);
        CreateLogFile();
    }

    // Print Log Key
    if (PrintLogOutput) {
        std::cout << "[ Level] [               Time] [Message]\n";
    }

}

ERS_LoggingSystem::~ERS_LoggingSystem() {

    Log("System Logger Destructor Called, Logger Shutting Down", 6);
    
    // Shutdown File Stream
    if (EnableLogFile_) {
        FileStream_.close();
    }
}

void ERS_LoggingSystem::CreateLogFile(){
    if (EnableLogFile_) {
        std::stringstream ss;
        ss << LogFilePathPrefix_ << GetFormattedTime() << ".txt";
        LogFilePath_ = ss.str();
        FileStream_.open(LogFilePath_, std::ios_base::app);        
    }
}

void ERS_LoggingSystem::WriteLineToFile(std::string Line) {

    //std::lock_guard<std::mutex> lock(LogMutex_);

    FileStream_ << Line;
}

void ERS_LoggingSystem::Log(std::string LogMessage, int LogLevel, bool Enable) {

    if (Enable) {
        LogItem(LogMessage.c_str(), LogLevel);
    }

}

void ERS_LoggingSystem::Log(const char* LogMessage, int LogLevel, bool Enable) {

    if (Enable) {
        LogItem(LogMessage, LogLevel);
    }

}



void ERS_LoggingSystem::LogItem(const char* LogItem, int LogLevel) {

    std::string CurrentTime = GetFormattedTime();
    
    // Create Output Strings
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

    // Combine Strings
    Output += "[" + LogLevelPadded + "] ";
    Output += "[" + CurrentTimePadded + "] ";
    Output += std::string(LogItem) + "\n";

    // Add To Log Output Vars
    std::unique_lock<std::mutex> Lock(LogBufferMutex_);
    LogBuffer_.push_back(Output);
    CurrentMessages_++;

    if (CurrentMessages_ > WriteThreshold_) {
        FlushLogBuffer();
        CurrentMessages_  = 0; 
    }

    LogMessages_.push_back(std::string(LogItem));
    LogLevels_.push_back(LogLevel);
    LogTimes_.push_back(CurrentTime);
    LogColors_.push_back(ColorLookup_[LogLevel]);
    FullLogMessages_.push_back(Output);

    // Check Log Level Before Printing It
    if (LogLevel >= MinimumLogLevel) {

        // If Log Print Enabled
        if (PrintLogOutput) {
            // If Colorize Enabled
            if (ColorizeLog) {
                ColorizeText(Output, LogLevel);
            } else {
                std::cout << Output;
            }
        }

        // Log To File
        if (EnableLogFile_) {
            FlushLogBuffer();
            CurrentMessages_  = 0; 
            //WriteLineToFile(Output);
        }
    }

}

std::string ERS_LoggingSystem::GetFormattedTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d_%H-%M-%S", timeInfo);
    return std::string(timeBuffer);
}

std::string ERS_LoggingSystem::GetLogLevelString(int LogLevel) {
    if (LogNameLookup_.count(LogLevel) > 0) {
        return LogNameLookup_[LogLevel];
    } else {
        return std::to_string(LogLevel);
    }
}

void ERS_LoggingSystem::FlushLogBuffer() {
    //std::unique_lock<std::mutex> Lock(LogBufferMutex_);

    for (const auto& logMessage : LogBuffer_) {
        if (EnableLogFile_) {
            WriteLineToFile(logMessage);
        }
    }

    LogBuffer_.clear();
    CurrentMessages_ = 0;
}

void ERS_LoggingSystem::LogPerformanceTest() {
    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        LogItem("Test message", 0);
    }
    auto endTime = std::chrono::steady_clock::now();
    auto timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Time elapsed: " << timeTaken.count() << std::endl;
}

void ERS_LoggingSystem::ColorizeText(std::string Message, int LogLevel) {

    ERS_RGBColor ColorValue = ColorLookup_[LogLevel];

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
