//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for creating and managing the framebuffer.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-28
*/

#include <Framebuffer.h>



// Framebuffer manager Constructor
FramebufferManager::FramebufferManager(LoggerClass *Logger, float Width, float Height) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Framebuffer Manager", 5);


    // Create Framebuffer
    Logger_->Log("Creating Framebuffer Object", 4);
    glGenFramebuffers(1, &FramebufferObject_);

    // Bind To Framebuffer
    Logger_->Log("Binding To Framebuffer Object", 4);
    glBindBuffer(GL_FRAMEBUFFER, FramebufferObject_);


    // Create RenderTexture
    Logger_->Log("Creating Render Texture", 4);
    glGenTextures(1, &RenderTexture_);
    glBindTexture(GL_TEXTURE_2D, RenderTexture_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)Width, (int)Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach Texture To Framebuffer
    Logger_->Log("Attaching Texture To Framebuffer", 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderTexture_, 0);

    // Check Framebuffer Status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

        // Log Error
        Logger_->Log("Failed To Initialize Framebuffer", 9);
    }

}

// Framebuffer manager Destructor
FramebufferManager::~FramebufferManager() {

    // Log Destructor Called
    Logger_->Log("Framebuffer Manager Destructor Called", 6);

    // Destroy Framebuffer
    Logger_->Log("Destroying Framebuffer Object", 5);
    glDeleteFramebuffers(1, &FramebufferObject_);  

}