//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_Grid.h>


ERS_CLASS_Grid::ERS_CLASS_Grid(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Creating Viewport Grid Instance", 4);

    // Create 2D Plane To Draw Grid On
    const float GridVertices[] = {
        -1.0,  1.0, 0.0, // Top Left
        -1.0, -1.0, 0.0, // Bottom Left
        1.0, -1.0, 0.0, // Bottom Right
        1.0,  1.0, 0.0, // Top Right
    };

    glGenBuffers(1, &GridVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, GridVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GridVertices), GridVertices, GL_STATIC_DRAW);

}

ERS_CLASS_Grid::~ERS_CLASS_Grid() {
    SystemUtils_->Logger_->Log("Viewport Grid Destructor Called", 6);
}