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

    SystemUtils_->Logger_->Log("Freeing Cube VAO/VBO", 4);
    glDeleteVertexArrays(1, &BoundingBoxRendererVAO_);
    glDeleteBuffers(1, &BoundingBoxRendererVBO_);
    SystemUtils_->Logger_->Log("Freed Cube VAO/VBO", 3);

}

void ERS_CLASS_BoundingBoxRenderer::DrawAll(ERS_STRUCT_Camera* Camera, ERS_STRUCT_Scene* Scene) {


    if (DrawWireframe_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (DisableDepthTest_) {
        glDisable(GL_DEPTH_TEST);
    }

    BoundingBoxRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();

    
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {


        // Calculate Model Matrix For The Bounding Box
        glm::mat4 ModelMatrix = glm::translate(BoundingBoxRendererModelArray_, Scene->Models[i]->ModelPosition + (Scene->Models[i]->BoxOffset_ * Scene->Models[i]->ModelScale));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Scene->Models[i]->ModelRotation.z), glm::vec3(0, 0, 1));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Scene->Models[i]->ModelRotation.y), glm::vec3(0, 1, 0));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Scene->Models[i]->ModelRotation.x), glm::vec3(1, 0, 0));
        ModelMatrix = glm::scale(ModelMatrix, Scene->Models[i]->ModelScale * Scene->Models[i]->BoxScale_);

        // Set Shader Uniforms
        BoundingBoxRendererShader_->SetMat4("Model", ModelMatrix);
        BoundingBoxRendererShader_->SetMat4("View", View);
        BoundingBoxRendererShader_->SetMat4("Projection", Projection);

        BoundingBoxRendererShader_->SetVec4("Color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));


        // Draw Vertices
        glBindVertexArray(BoundingBoxRendererVAO_);
        glDrawArrays(GL_TRIANGLES, 0, 36); // 36 Verts to draw, count size of cube array

    }


    if (DrawWireframe_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (DisableDepthTest_) {
        glEnable(GL_DEPTH_TEST);
    }

}


// todo:
// add option to viewport struct to color code the bounding boxes based on the loading system (so different colors would indicate loading vs unloading for example)
// then add option to just draw normal color
// fix offset caused during rotation due to object's center not being the center of the box.

void ERS_CLASS_BoundingBoxRenderer::DrawModel(ERS_STRUCT_Camera* Camera, ERS_STRUCT_Model* Model, glm::vec3 Color) {

    if (DrawWireframe_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (DisableDepthTest_) {
        glDisable(GL_DEPTH_TEST);
    }

    BoundingBoxRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();


    // Calculate Model Matrix For The Bounding Box
    glm::mat4 ModelMatrix = glm::translate(BoundingBoxRendererModelArray_, Model->ModelPosition + (Model->BoxOffset_ * Model->ModelScale));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.z), glm::vec3(0, 0, 1));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.y), glm::vec3(0, 1, 0));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Model->ModelRotation.x), glm::vec3(1, 0, 0));
    ModelMatrix = glm::scale(ModelMatrix, Model->ModelScale * Model->BoxScale_);

    // Set Shader Uniforms
    BoundingBoxRendererShader_->SetMat4("Model", ModelMatrix);
    BoundingBoxRendererShader_->SetMat4("View", View);
    BoundingBoxRendererShader_->SetMat4("Projection", Projection);

    BoundingBoxRendererShader_->SetVec4("Color", glm::vec4(Color, 1.0f));

    // Draw Vertices
    glBindVertexArray(BoundingBoxRendererVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 36 Verts to draw, count size of cube array


    if (DrawWireframe_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (DisableDepthTest_) {
        glEnable(GL_DEPTH_TEST);
    }

}

void ERS_CLASS_BoundingBoxRenderer::SetDepthTest(bool DepthTestEnabled) {
    DisableDepthTest_ = !DepthTestEnabled;
}

void ERS_CLASS_BoundingBoxRenderer::SetDrawMode(bool WireframeEnabled) {
    DrawWireframe_ = WireframeEnabled;
}

