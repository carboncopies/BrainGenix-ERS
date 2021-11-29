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
FramebufferManager::FramebufferManager(LoggerClass *Logger, ShaderLoader *ShaderLoader, float Width, float Height) {

    // Create Local Pointers
    Logger_ = Logger;
    ShaderLoader_ = ShaderLoader;

    // Log Initialization
    Logger_->Log("Initializing Framebuffer Manager", 5);



    // Load Screen Shaders
    Logger_->Log("Loading Screen Shaders", 5);
    ScreenShader_ = ShaderLoader_->LoadShaderFromFile("Shaders/ScreenShader.vert", "Shaders/ScreenShader.frag");
    
    // Make Screen Shaders Active
    Logger_->Log("Making Screen Shaders Active", 3);
    ScreenShader_.MakeActive();
    ScreenShader_.SetInt("screenTexture", 0);




    // Create Screen Quad
    Logger_->Log("Generating Screen Quad VAO", 4);
    glGenVertexArrays(1, &ScreenQuadVAO_);

    Logger_->Log("Generating Screen Quad VBO", 4);
    glGenBuffers(1, &ScreenQuadVBO_);


    // Framebuffer manager Quads
    float QuadVertices[] = {

        // Positions   // Texture Coordinates
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    glBindVertexArray(ScreenQuadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, ScreenQuadVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), &QuadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));


    // Create Framebuffer
    Logger_->Log("Creating Framebuffer Object", 4);
    glGenFramebuffers(1, &FramebufferObject_);

    // Bind To Framebuffer
    Logger_->Log("Binding To Framebuffer Object", 4);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject_);

    // Create RenderTexture
    Logger_->Log("Creating Render Texture", 4);
    glGenTextures(1, &RenderTexture_);
    glBindTexture(GL_TEXTURE_2D, RenderTexture_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // NOTE: THIS MUST HAPPEN ON RESIZE!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach Texture To Framebuffer
    Logger_->Log("Attaching Texture To Framebuffer", 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderTexture_, 0);

    // Create Render Buffer
    Logger_->Log("Creating Render Buffer Object", 5);
    glGenRenderbuffers(1, &RenderBufferObject_);
    glBindRenderbuffer(GL_RENDERBUFFER, RenderBufferObject_);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height); // RESIZE THIS WITH THE WINDOW!

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

    // Deallocate Screen Quad
    Logger_->Log("Destroying Screen Quad VAO/VBO", 4);
    glDeleteVertexArrays(1, &ScreenQuadVAO_);
    glDeleteBuffers(1, &ScreenQuadVBO_);

}


// FramebufferManager Start FB Render Pass
void FramebufferManager::StartFramebufferRenderPass() {

    // Bind To Framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferObject_);
    glEnable(GL_DEPTH_TEST);


}


// FramebufferManager Start Screen Render Pass
void FramebufferManager::StartScreenRenderPass(bool RenderToImGui) {

    // // If Not Rendering To ImGUI
    // if (!RenderToImGui) {

        // Use Default Framebuffer, And Render To It
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use ScreenShader
        ScreenShader_.MakeActive();

        // Render Quad
        glBindVertexArray(ScreenQuadVAO_);
        glBindTexture(GL_TEXTURE_2D, RenderTexture_);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    // } else {
    //     // Render FBO Into Viewport
    //     ImGui::Begin("Viewport");

    //         ImGui::BeginChild("Test");

    //             ImVec2 WindowSize = ImGui::GetWindowSize();
    //             ImGui::Image((ImTextureID)&RenderTexture_, WindowSize, ImVec2(0,1), ImVec2(1,0));

    //         ImGui::EndChild();


    //     ImGui::End();

    // }

}

void FramebufferManager::ResizeFramebuffer(int Width, int Height) {

    // Update Render Color Buffer Size
    glBindTexture(GL_TEXTURE_2D, RenderTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // Update RBO Size
    glBindRenderbuffer(GL_RENDERBUFFER, RenderBufferObject_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);

}