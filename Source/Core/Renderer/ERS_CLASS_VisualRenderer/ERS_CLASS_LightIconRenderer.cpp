//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_LightIconRenderer.h>



ERS_CLASS_LightIconRenderer::ERS_CLASS_LightIconRenderer(ERS_STRUCT_OpenGLDefaults* Defaults, ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> LightIconRendererShader) {


    SystemUtils_ = SystemUtils;
    LightIconRendererShader_ = LightIconRendererShader;
    OpenGLDefaults_ = Defaults;


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


void ERS_CLASS_LightIconRenderer::Draw(ERS_STRUCT_Camera* Camera, ERS_CLASS_SceneManager* SceneManager) {

    
    LightIconRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();
    glm::vec3 CameraPosition = Camera->Position;
    glm::vec3 CameraUp = Camera->Up;
    glm::vec3 CameraRight = Camera->Right;

    // Draw All Point Lights
    for (int i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights.size(); i++) {

        glm::mat4 NewModelMatrix = glm::scale(LightIconRendererModelArray_, glm::vec3(LightIconRendererScale_));
        NewModelMatrix = glm::translate(NewModelMatrix, SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos);

        std::cout<<glm::to_string(SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos)<<std::endl;

        LightIconRendererShader_->SetMat4("model", NewModelMatrix);
        LightIconRendererShader_->SetMat4("view", View);
        LightIconRendererShader_->SetMat4("projection", Projection);

        LightIconRendererShader_->SetVec3("CameraPosition", CameraPosition);
        LightIconRendererShader_->SetVec3("CameraRight", CameraRight);
        LightIconRendererShader_->SetVec3("CameraUp", CameraUp);

        LightIconRendererShader_->SetFloat("BillboardSize", LightIconRendererScale_);
        LightIconRendererShader_->SetVec3("BillboardPosition", SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos);
        
        //LightIconRendererShader_->SetVec3("BillboardRotation", SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos);
        
        


        glUniform1i(glGetUniformLocation(LightIconRendererShader_->ShaderProgram, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->PointLightTexture_);

        glBindVertexArray(LightIconRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }

}