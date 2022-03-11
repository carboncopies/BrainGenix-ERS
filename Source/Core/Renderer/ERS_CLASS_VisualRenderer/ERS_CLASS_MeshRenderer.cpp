//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_MeshRenderer.h>



ERS_CLASS_MeshRenderer::ERS_CLASS_MeshRenderer(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing MeshRenderer Class Instance", 5);

}

ERS_CLASS_MeshRenderer::~ERS_CLASS_MeshRenderer() {

    SystemUtils_->Logger_->Log("MeshRenderer Destructor Called", 6);

}


void ERS_CLASS_MeshRenderer::RenderScene(ERS_STRUCT_Scene* Scene, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {

    ERS_FUNCTION_UpdateMeshTransparency(Scene);

    


    // Get List Of Transparent/Opaque Meshes
    std::vector<ERS_STRUCT_Mesh*> OpaqueMeshes;
    std::vector<ERS_STRUCT_Mesh*> TransparentMeshes;

    for (unsigned long i = 0; i < Scene->Models.size(); i++) {

        ERS_STRUCT_Model *Model = Scene->Models[i].get();
        glm::mat4 ModelMatrix = Model->GetMat4();
        for (unsigned int i = 0; i < Model->Meshes.size(); i++) {

            ERS_STRUCT_Mesh* Mesh = &Model->Meshes[i];
            Mesh->ModelMatrix = ModelMatrix;
            if (Mesh->HasTransparency_) {
                TransparentMeshes.push_back(Mesh);
            } else {
                OpaqueMeshes.push_back(Mesh);
            }

        }

    }

    // Draw All Opaque Meshes
    for (unsigned long i = 0; i < OpaqueMeshes.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->DefaultTexture_);
        glActiveTexture(OpenGLDefaults->DefaultTexture_);
        Shader->SetMat4("model", OpaqueMeshes[i]->ModelMatrix);
        OpaqueMeshes[i]->Draw(OpenGLDefaults, Shader);
    }


    // Disable Depth Filtering
    glDisable(GL_DEPTH_TEST);

    // Render Transparent Meshes In Right Order
    for (unsigned long i = 0; i < TransparentMeshes.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->DefaultTexture_);
        glActiveTexture(OpenGLDefaults->DefaultTexture_);
        Shader->SetMat4("model", TransparentMeshes[i]->ModelMatrix);
        TransparentMeshes[i]->Draw(OpenGLDefaults, Shader);
    }

    // Enable Depth Filtering
    glEnable(GL_DEPTH_TEST);


    // TODO: Update rendering process
    // should be based around the idea that the models are used to get the meshes to be rendered
    // the meshes are then compiled into two lists to be rendered
    // firstly, there are opaque meshes which are rendered normally (With the depth testing enabled)
    // next, there's the transparent meshes which are sorted by distance on another thread while the opaque meshes are rendering
    // then, these are rendered via depth peeling.

    // A later method would be to implement support for OIT or something fancy like that but this will work for now.  



    // Also remove model draw call, as it's no longer used
    // then remove the mesh draw function and put it into here so that it's more consoldiated and self-explanitory
    // then maybe move the renderer code into it's own namespace?

}