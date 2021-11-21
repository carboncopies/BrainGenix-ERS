//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#pragma once


class VisualRenderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_; /**<Pointer to the system configuration YAML::Node*/
        LoggerClass *Logger_; /**<Pointer to the logging system instance*/

        // Control Values
        bool *SystemShouldRun_;


        ERS_OBJECT_SHADER Shader_;
        ERS_OBJECT_MODEL Model_;




        GLFWwindow* Window_;
        int WindowWidth_;
        int WindowHeight_;
        const char* WindowTitle_;

        int RenderWidth_;
        int RenderHeight_;

        
        // Timing
        float DeltaTime = 0.0f;
        float LastFrame = 0.0f;

        // Internal Functions
        void InitializeGLFW();
        void InitialzeOpenGL();

    public:

        // Constructor
        VisualRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun);


        // Destructor
        ~VisualRenderer();

        // Update Loop Func
        void UpdateLoop();

        

};
