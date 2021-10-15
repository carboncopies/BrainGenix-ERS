//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main rendering system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/  

#pragma once

// Declare Renderer Class
class MainRenderer {

    private:

        // Delcare Private Vars
        LoggerClass Logger_;
        YAML::Node SystemConfiguration_;

        // Declare Class Instances
        VisualRenderer sERSVisualRenderer_;
        
        // Delcare Class Variables
        bool SystemShutdownInvoked_;

    public:

        // Main init Call
        void InitRenderer(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle);

        // Update Rendered Output
        void UpdateRender();

        // Destructor
        void CleanUp();

};