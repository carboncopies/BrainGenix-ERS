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
    LightIconRendererModelArray_ = glm::mat4(1.0f);

}

ERS_CLASS_LightIconRenderer::~ERS_CLASS_LightIconRenderer() {

    SystemUtils_->Logger_->Log("LightIconRenderer Destructor Called", 6);

}

void ERS_CLASS_LightIconRenderer::Draw(ERS_STRUCT_Camera* Camera, ERS_CLASS_SceneManager* SceneManager) {

    
    LightIconRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();
    glm::vec3 CameraPosition = Camera->Position_;
    glm::vec3 CameraUp = Camera->Up_;
    glm::vec3 CameraRight = Camera->Right_;

    // Draw All Point Lights
    for (int i = 0; (long)i < (long)SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(LightIconRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera

        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.x, glm::vec3(1, 0, 0));
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.y, glm::vec3(0, 1, 0));
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(LightIconRendererScale_));

        LightIconRendererShader_->SetMat4("model", NewModelMatrix);
        LightIconRendererShader_->SetMat4("view", View);
        LightIconRendererShader_->SetMat4("projection", Projection);

        LightIconRendererShader_->SetVec3("CameraPosition", CameraPosition);
        LightIconRendererShader_->SetVec3("CameraRight", CameraRight);
        LightIconRendererShader_->SetVec3("CameraUp", CameraUp);

        LightIconRendererShader_->SetFloat("BillboardSize", LightIconRendererScale_);
        LightIconRendererShader_->SetVec3("BillboardPosition", LightPosition);
        
        //LightIconRendererShader_->SetVec3("BillboardRotation", SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos);
        
        glUniform1i(glGetUniformLocation(LightIconRendererShader_->ShaderProgram, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->PointLightTexture_);

        glBindVertexArray(LightIconRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }


    // Draw All Directional Lights
    for (int i = 0; (long)i < (long)SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(LightIconRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera
        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);

        glm::vec3 LampRotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[i]->Rot;
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.x, glm::vec3(1, 0, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.y, glm::vec3(0, 1, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(LightIconRendererScale_));

        LightIconRendererShader_->SetMat4("model", NewModelMatrix);
        LightIconRendererShader_->SetMat4("view", View);
        LightIconRendererShader_->SetMat4("projection", Projection);

        LightIconRendererShader_->SetVec3("CameraPosition", CameraPosition);
        LightIconRendererShader_->SetVec3("CameraRight", CameraRight);
        LightIconRendererShader_->SetVec3("CameraUp", CameraUp);

        LightIconRendererShader_->SetFloat("BillboardSize", LightIconRendererScale_);
        LightIconRendererShader_->SetVec3("BillboardPosition", LightPosition);
        LightIconRendererShader_->SetVec3("BillboardRotation", LampRotation);
        
        glUniform1i(glGetUniformLocation(LightIconRendererShader_->ShaderProgram, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->DirectionalLightTexture_);

        glBindVertexArray(LightIconRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }


    // Draw All Spot Lights
    for (int i = 0; i < SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(LightIconRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera
        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);

        glm::vec3 LampRotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[i]->Rot;
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.x, glm::vec3(1, 0, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.y, glm::vec3(0, 1, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(LightIconRendererScale_));

        LightIconRendererShader_->SetMat4("model", NewModelMatrix);
        LightIconRendererShader_->SetMat4("view", View);
        LightIconRendererShader_->SetMat4("projection", Projection);

        LightIconRendererShader_->SetVec3("CameraPosition", CameraPosition);
        LightIconRendererShader_->SetVec3("CameraRight", CameraRight);
        LightIconRendererShader_->SetVec3("CameraUp", CameraUp);

        LightIconRendererShader_->SetFloat("BillboardSize", LightIconRendererScale_);
        LightIconRendererShader_->SetVec3("BillboardPosition", LightPosition);
        LightIconRendererShader_->SetVec3("BillboardRotation", LampRotation);
        
        glUniform1i(glGetUniformLocation(LightIconRendererShader_->ShaderProgram, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->SpotLightTexture_);

        glBindVertexArray(LightIconRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }




}

