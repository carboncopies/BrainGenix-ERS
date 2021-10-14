//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 


 
// Define Visual Renderer Class
class VisualRenderer {

    private:

        // Declare Logger
        LoggerClass Logger;


        // Initialize Vulkan API
        void InitVulkan();

        // Destructor
        void CleanUp();

    public:

        // Initialize VisualRendering Subsystem
        void InitializeSystem(LoggerClass sERSLogger);

        // Main Loop For Visual Renderer
        void RenderLoop();



};