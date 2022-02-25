//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_LightIconRenderer.h>



ERS_CLASS_LightIconRenderer::ERS_CLASS_LightIconRenderer(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> LightIconRendererShader) {


    SystemUtils_ = SystemUtils;
    LightIconRendererShader_ = LightIconRendererShader;


    SystemUtils_->Logger_->Log("Setting Up VisualRenderer LightIconRenderer System", 5);



    const float LightIconRendererVertices[] = {
        -1.0,  1.0, 0.0, 0.0, 1.0,  // Top Left
        -1.0, -1.0, 0.0, 1.0, 1.0,  // Bottom Left
        1.0, -1.0,  0.0, 1.0, 0.0,  // Bottom Right
        1.0,  1.0,  0.0, 0.0, 0.0   // Top Right
    };

    glGenBuffers(1, &LightIconRendererVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, LightIconRendererVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LightIconRendererVertices), LightIconRendererVertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &LightIconRendererVAO_);
    glBindVertexArray(LightIconRendererVAO_);

    int PositionIndex = 0;
    glVertexAttribPointer(PositionIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(PositionIndex);

    int TexCoordsIndex = 2;
    glEnableVertexAttribArray(TexCoordsIndex);
    glVertexAttribPointer(TexCoordsIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));


    // Initialize Model Array
    LightIconRendererModelArray_ = glm::mat4();

}

ERS_CLASS_LightIconRenderer::~ERS_CLASS_LightIconRenderer() {

    SystemUtils_->Logger_->Log("LightIconRenderer Destructor Called", 6);

}


void ERS_CLASS_LightIconRenderer::Draw(glm::mat4 View, glm::mat4 Projection, glm::vec3 CameraPosition, ERS_CLASS_SceneManager* SceneManager) {

    
    LightIconRendererShader_->MakeActive();


    // Draw All Point Lights
    for (int i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights.size(); i++) {

        glm::mat4 NewModelMatrix = glm::scale(LightIconRendererModelArray_, glm::vec3(LightIconRendererScale_));
        NewModelMatrix = glm::translate()

        LightIconRendererShader_->SetMat4("model", LightIconRendererModelArray_);
        LightIconRendererShader_->SetMat4("view", View);
        LightIconRendererShader_->SetMat4("projection", Projection);

        LightIconRendererShader_->SetVec3("CameraPosition", CameraPosition);

        glBindVertexArray(LightIconRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }

}