//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_BoundingBoxRenderer.h>



ERS_CLASS_BoundingBoxRenderer::ERS_CLASS_BoundingBoxRenderer( ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_Shader* BoundingBoxRendererShader) {

    SystemUtils_ = SystemUtils;
    BoundingBoxRendererShader_ = BoundingBoxRendererShader;

    SystemUtils_->Logger_->Log("Setting Up VisualRenderer BoundingBoxRenderer System", 5);


    // Cube Vert Array 'Borrowed' (Stolen) From https://learnopengl.com - Thanks Joey!
    const float CubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenBuffers(1, &BoundingBoxRendererVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, BoundingBoxRendererVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &BoundingBoxRendererVAO_);
    glBindVertexArray(BoundingBoxRendererVAO_);

    int PositionIndex = 0;
    glVertexAttribPointer(PositionIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(PositionIndex);

    int TexCoordsIndex = 2;
    glEnableVertexAttribArray(TexCoordsIndex);
    glVertexAttribPointer(TexCoordsIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));


    // Initialize Model Array
    BoundingBoxRendererModelArray_ = glm::mat4(1.0f);

}

ERS_CLASS_BoundingBoxRenderer::~ERS_CLASS_BoundingBoxRenderer() {

    SystemUtils_->Logger_->Log("BoundingBoxRenderer Destructor Called", 6);

}

void ERS_CLASS_BoundingBoxRenderer::Draw(ERS_STRUCT_Camera* Camera, ERS_STRUCT_Scene* Scene) {


    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    BoundingBoxRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();
    glm::vec3 CameraPosition = Camera->Position_;
    glm::vec3 CameraUp = Camera->Up_;
    glm::vec3 CameraRight = Camera->Right_;

    
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {

        // Calculate Model Matrix For The Bounding Box
        glm::mat4 ModelMatrix = glm::translate(BoundingBoxRendererModelArray_, Scene->Models[i]->ModelPosition);
        ModelMatrix = glm::rotate(ModelMatrix, Scene->Models[i]->ModelRotation.x, glm::vec3(1, 0, 0));
        ModelMatrix = glm::rotate(ModelMatrix, Scene->Models[i]->ModelRotation.x, glm::vec3(0, 1, 0));
        ModelMatrix = glm::rotate(ModelMatrix, Scene->Models[i]->ModelRotation.x, glm::vec3(0, 0, 1));
        ModelMatrix = glm::scale(ModelMatrix, Scene->Models[i]->ModelScale);

        // Set Shader Uniforms
        BoundingBoxRendererShader_->SetMat4("model", ModelMatrix);
        BoundingBoxRendererShader_->SetMat4("view", View);
        BoundingBoxRendererShader_->SetMat4("projection", Projection);

        // Draw Vertices
        glBindVertexArray(BoundingBoxRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 36); // 36 Verts to draw, count size of cube array

    }



    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);


}

