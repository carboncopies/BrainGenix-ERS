//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_Grid.h>


ERS_CLASS_Grid::ERS_CLASS_Grid(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> GridShader) {

    SystemUtils_ = SystemUtils;
    GridShader_ = GridShader;
    SystemUtils_->Logger_->Log("Creating Viewport Grid Instance", 4);

    // Create 2D Plane To Draw Grid On
    SystemUtils_->Logger_->Log("Setting Up Grid Plane", 3);
    const float GridVertices[] = {
        -1.0,  1.0, 0.0, // Top Left
        -1.0, -1.0, 0.0, // Bottom Left
        1.0, -1.0, 0.0, // Bottom Right
        1.0,  1.0, 0.0, // Top Right
    };

    glGenBuffers(1, &GridVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, GridVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GridVertices), GridVertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &GridVAO_);
    glBindVertexArray(GridVAO_);

    int PositionIndex = 0;
    glVertexAttribPointer(PositionIndex, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(PositionIndex);

}


ERS_CLASS_Grid::~ERS_CLASS_Grid() {

    SystemUtils_->Logger_->Log("Viewport Grid Destructor Called", 6);

    glDeleteBuffers(1, &GridVBO_);
    glDeleteVertexArrays(1, &GridVAO_);

}


void ERS_CLASS_Grid::DrawGrid() {

    glBindVertexArray(GridVAO_);
    GridShader_->MakeActive();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}