//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

class RenderLoopClass {


    private:
    
        // Declare Render Properties
        int RenderWidth;
        int RenderHeight;
        bool LocalWindowEnabled;

        // Declare Logger Instance
        LoggerClass Logger;

        // Declare GSInstance
        GraphicsSubsystem GS;

        // Frame Update Params
        unsigned int FrameCounter = 0;

    public:

        void InitializeRenderLoop(GraphicsSubsystem GSInstance, LoggerClass LoggerInstance) {

            // Log Initialization
            Logger.Log("Initializing Main Render Loop", 4);

            Logger = LoggerInstance;
            GS = GSInstance;


            // Extract Graphics Params
            Logger.Log("Reading Rendering Parameters", 2);
            RenderWidth = GS.RenderWidthPixels;
            RenderHeight = GS.RenderHeightPixels;
            LocalWindowEnabled = GS.LocalWindowEnabled;

        };

        void RenderLoop() {

            // Render Frame
            bgfx::frame();

            // Update Counter
            FrameCounter ++;

        }


};
