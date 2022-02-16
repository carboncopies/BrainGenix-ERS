//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_Grid.h>


ERS_CLASS_Grid::ERS_CLASS_Grid(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> GridShader) {

    SystemUtils_ = SystemUtils;
    GridShader_ = GridShader;
    SystemUtils_->Logger_->Log("Creating Viewport Grid Instance", 4);


    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create 2D Plane To Draw Grid On
    SystemUtils_->Logger_->Log("Setting Up Grid Plane", 3);
    const float GridVertices[] = {
        -1.0,  1.0, 0.0, 1.0, 0.0,  // Top Left
        -1.0, -1.0, 0.0, 0.0, 0.0,  // Bottom Left
        1.0, -1.0,  0.0, 0.0, 1.0,  // Bottom Right
        1.0,  1.0,  0.0, 1.0, 1.0   // Top Right
    };

    glGenBuffers(1, &GridVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, GridVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GridVertices), GridVertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &GridVAO_);
    glBindVertexArray(GridVAO_);

    int PositionIndex = 0;
    glVertexAttribPointer(PositionIndex, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(PositionIndex);

    int TexCoordsIndex = 2;
    glEnableVertexAttribArray(TexCoordsIndex);
    glVertexAttribPointer(TexCoordsIndex, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));


    // Setup Grid Model Matrix
    GridModelArray_ = glm::mat4();
    GridModelArray_ = glm::scale(GridModelArray_, glm::vec3(10.0f));
    GridModelArray_ = glm::rotate(GridModelArray_, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

}


ERS_CLASS_Grid::~ERS_CLASS_Grid() {

    SystemUtils_->Logger_->Log("Viewport Grid Destructor Called", 6);

    glDeleteBuffers(1, &GridVBO_);
    glDeleteVertexArrays(1, &GridVAO_);

}


void ERS_CLASS_Grid::DrawGrid(glm::mat4 View, glm::mat4 Projection) {


    glDisable(GL_DEPTH_TEST);

    GridShader_->MakeActive();
    GridShader_->SetMat4("model", GridModelArray_);
    GridShader_->SetMat4("view", View);
    GridShader_->SetMat4("projection", Projection);

    glBindVertexArray(GridVAO_);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glEnable(GL_DEPTH_TEST);


}