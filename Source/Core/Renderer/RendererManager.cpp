//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "RendererManager.h"


// FIXME! MAKE MORE CLEAN LOOKING OR SOMETHING
void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}



// RendererManager Constructor
RendererManager::RendererManager(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating RendererManager Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;


    // Initialize Systems
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    // Instantiate Renderers
    Logger_->Log("Instantiating Renderers", 5);
    VisualRenderer_ = new VisualRenderer(SystemConfiguration, Logger, SystemShouldRun);


    // TODO: FINISH REFACTORING VISUALRENDERER
    // REFACTOR FRAMEBUFFERMANAGER TO ALLOW EACH VIEWPORT TO HAVE IT's OWN RESOLUTION
    // REFACTOR VISUALRENDERER INTO VIEWPORTMANAGER TO ALLOW FOR MULTIPLE VIEWPORTS, JUST CREATE ONE FOR NOW
    // ADD VIEWPORT TO IMGUI
    // CHECK TRELLO!

    // Setup Framebuffer
    FramebufferManager_ = new FramebufferManager(Logger_, ShaderLoader_, WindowWidth_, WindowHeight_);

    // Setup IOManager
    Logger_->Log("Initializing Input/Output Manager", 5);
    IOManager_ = new IOManager(Logger_, &Camera_, FramebufferManager_);


}

// RendererManager Destructor
RendererManager::~RendererManager() {

    // Log Destructor Call
    Logger_->Log("RendererManager Destructor Called", 6);

}


// Initialize Window
void RendererManager::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    // Bring Window To Front
    glfwMakeContextCurrent(Window_);

}



void RendererManager::UpdateLoop(float DeltaTime) { 

    // Call Updates
    VisualRenderer_->UpdateLoop(DeltaTime);


}




