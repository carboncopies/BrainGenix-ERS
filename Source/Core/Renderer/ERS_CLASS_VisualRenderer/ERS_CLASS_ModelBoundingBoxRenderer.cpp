//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_BoundingBoxRenderer.h>



ERS_CLASS_BoundingBoxRenderer::ERS_CLASS_BoundingBoxRenderer(ERS_STRUCT_OpenGLDefaults* Defaults, ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_Shader* BoundingBoxRendererShader) {


    SystemUtils_ = SystemUtils;
    BoundingBoxRendererShader_ = BoundingBoxRendererShader;
    OpenGLDefaults_ = Defaults;


    SystemUtils_->Logger_->Log("Setting Up VisualRenderer BoundingBoxRenderer System", 5);


    // 'Borrowed' (Stolen) From https://learnopengl.com - Thanks Joey!
    const float BoundingBoxVerticies[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(BoundingBoxRendererVertices), BoundingBoxRendererVertices, GL_STATIC_DRAW);
    
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

void ERS_CLASS_BoundingBoxRenderer::Draw(ERS_STRUCT_Camera* Camera, ERS_CLASS_SceneManager* SceneManager) {

    glDisable(GL_DEPTH_TEST);
    BoundingBoxRendererShader_->MakeActive();
    glm::mat4 View = Camera->GetViewMatrix();
    glm::mat4 Projection = Camera->GetProjectionMatrix();
    glm::vec3 CameraPosition = Camera->Position_;
    glm::vec3 CameraUp = Camera->Up_;
    glm::vec3 CameraRight = Camera->Right_;

    // Draw All Point Lights
    for (int i = 0; (long)i < (long)SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(BoundingBoxRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera

        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.x, glm::vec3(1, 0, 0));
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.y, glm::vec3(0, 1, 0));
        // NewModelMatrix = glm::rotate(NewModelMatrix, ModelRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(BoundingBoxRendererScale_));

        BoundingBoxRendererShader_->SetMat4("model", NewModelMatrix);
        BoundingBoxRendererShader_->SetMat4("view", View);
        BoundingBoxRendererShader_->SetMat4("projection", Projection);

        BoundingBoxRendererShader_->SetVec3("CameraPosition", CameraPosition);
        BoundingBoxRendererShader_->SetVec3("CameraRight", CameraRight);
        BoundingBoxRendererShader_->SetVec3("CameraUp", CameraUp);

        BoundingBoxRendererShader_->SetFloat("BillboardSize", BoundingBoxRendererScale_);
        BoundingBoxRendererShader_->SetVec3("BillboardPosition", LightPosition);
        
        //BoundingBoxRendererShader_->SetVec3("BillboardRotation", SceneManager->Scenes_[SceneManager->ActiveScene_]->PointLights[i]->Pos);
        
        glUniform1i(glGetUniformLocation(BoundingBoxRendererShader_->ShaderProgram_, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->PointLightTexture_);

        glBindVertexArray(BoundingBoxRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }


    // Draw All Directional Lights
    for (int i = 0; (long)i < (long)SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(BoundingBoxRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera
        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);

        glm::vec3 LampRotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->DirectionalLights[i]->Rot;
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.x, glm::vec3(1, 0, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.y, glm::vec3(0, 1, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(BoundingBoxRendererScale_));

        BoundingBoxRendererShader_->SetMat4("model", NewModelMatrix);
        BoundingBoxRendererShader_->SetMat4("view", View);
        BoundingBoxRendererShader_->SetMat4("projection", Projection);

        BoundingBoxRendererShader_->SetVec3("CameraPosition", CameraPosition);
        BoundingBoxRendererShader_->SetVec3("CameraRight", CameraRight);
        BoundingBoxRendererShader_->SetVec3("CameraUp", CameraUp);

        BoundingBoxRendererShader_->SetFloat("BillboardSize", BoundingBoxRendererScale_);
        BoundingBoxRendererShader_->SetVec3("BillboardPosition", LightPosition);
        BoundingBoxRendererShader_->SetVec3("BillboardRotation", LampRotation);
        
        glUniform1i(glGetUniformLocation(BoundingBoxRendererShader_->ShaderProgram_, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->DirectionalLightTexture_);

        glBindVertexArray(BoundingBoxRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }


    // Draw All Spot Lights
    for (int i = 0; (long)i < (long)SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights.size(); i++) {

        glm::vec3 LightPosition = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[i]->Pos;
        glm::mat4 NewModelMatrix = glm::translate(BoundingBoxRendererModelArray_, LightPosition);


        // FIXME: Make Lights a "Billboard" So they Rotate Towards The Camera
        // glm::vec3 ModelRotation = glm::normalize(CameraPosition - LightPosition);

        glm::vec3 LampRotation = SceneManager->Scenes_[SceneManager->ActiveScene_]->SpotLights[i]->Rot;
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.x, glm::vec3(1, 0, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.y, glm::vec3(0, 1, 0));
        NewModelMatrix = glm::rotate(NewModelMatrix, LampRotation.z, glm::vec3(0, 0, 1));
        NewModelMatrix = glm::scale(NewModelMatrix, glm::vec3(BoundingBoxRendererScale_));

        BoundingBoxRendererShader_->SetMat4("model", NewModelMatrix);
        BoundingBoxRendererShader_->SetMat4("view", View);
        BoundingBoxRendererShader_->SetMat4("projection", Projection);

        BoundingBoxRendererShader_->SetVec3("CameraPosition", CameraPosition);
        BoundingBoxRendererShader_->SetVec3("CameraRight", CameraRight);
        BoundingBoxRendererShader_->SetVec3("CameraUp", CameraUp);

        BoundingBoxRendererShader_->SetFloat("BillboardSize", BoundingBoxRendererScale_);
        BoundingBoxRendererShader_->SetVec3("BillboardPosition", LightPosition);
        BoundingBoxRendererShader_->SetVec3("BillboardRotation", LampRotation);
        
        glUniform1i(glGetUniformLocation(BoundingBoxRendererShader_->ShaderProgram_, "IconTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults_->SpotLightTexture_);

        glBindVertexArray(BoundingBoxRendererVAO_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }


    glEnable(GL_DEPTH_TEST);


}

