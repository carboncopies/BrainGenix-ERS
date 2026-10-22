//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <DrawMeshNoTextures.h>


void ERS_FUNCTION_DrawMeshNoTextures(ERS_STRUCT_Mesh* Mesh, ERS_STRUCT_Shader* Shader) {

    // NOTE: This Pass Intentionally Binds No Textures - It Is Used Exclusively For Depth/Shadow Map Rendering
    // Where Only Geometry And The Model Matrix Matter.

    Shader->SetMat4("model", Mesh->ModelMatrix);

    // Draw Mesh
    glBindVertexArray(Mesh->VAO);
    glDrawElements(GL_TRIANGLES, Mesh->NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}
