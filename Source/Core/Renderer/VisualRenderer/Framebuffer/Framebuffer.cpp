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


// Framebuffer manager Quads
float FramebufferManager::QuadVertices_[] = {

    // Positions   // Texture Coordinates
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

// Framebuffer manager Constructor
FramebufferManager::FramebufferManager(LoggerClass *Logger, ShaderLoader *ShaderLoader, float Width, float Height) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Framebuffer Manager", 5);


    // Create Screen Quad
    Logger_->Log("Generating Screen Quad VAO", 4);
    glGenVertexArrays(1, &ScreenQuadVAO_);

    Logger_->Log("Generating Screen Quad VBO", 4);
    glGenBuffers(1, &ScreenQuadVBO_);

    glBindVertexArray(ScreenQuadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, ScreenQuadVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices_), &QuadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));

    // Load Screen Shaders
    Logger_->Log("Loading Screen Shaders", 5);
    ScreenShader_ = ShaderLoader_->LoadShaderFromFile("Shaders/ScreenShader.vert", "Shaders/ScreenShader.frag");
    ScreenShader_.MakeActive();
    ScreenShader_.SetInt("ScreenTexture", 0);


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

    // Create Render Buffer
    Logger_->Log("Creating Render Buffer Object", 5);
    glGenRenderbuffers(1, &RenderBufferObject_);
    glBindRenderbuffer(GL_RENDERBUFFER, RenderBufferObject_);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height); // RESIZE THIS WITH THE WINDOW!


    // Attach Texture To Framebuffer
    Logger_->Log("Attaching Texture To Framebuffer", 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderTexture_, 0);

    // Attach Renderbuffer to Depth And Stencil Attachment
    Logger_->Log("Attaching Render Buffer Object To Depth Stencil", 5);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderBufferObject_);


    // Check Framebuffer Status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

        // Log Error
        Logger_->Log("Failed To Initialize Framebuffer", 9);
    }


    // Bind To Framebuffer
    Logger_->Log("Binding To Framebuffer", 5);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);




}

// Framebuffer manager Destructor
FramebufferManager::~FramebufferManager() {

    // Log Destructor Called
    Logger_->Log("Framebuffer Manager Destructor Called", 6);

    // Destroy Framebuffer
    Logger_->Log("Destroying Framebuffer Object", 5);
    glDeleteFramebuffers(1, &FramebufferObject_);  

}


// FramebufferManager Start Render Pass


// FramebufferManeger End Render Pass