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
        LoggerClass Logger;
        YAML::Node SystemConfiguration;

        // Declare Class Instances
        VisualRenderer sERSVisualRenderer;

    public:

        // Main init Call
        void InitRenderer(LoggerClass sERSLogger, YAML::Node sERSConfig);

        // Update Rendered Output
        void UpdateRender();

        // Destructor
        void CleanUp();

};