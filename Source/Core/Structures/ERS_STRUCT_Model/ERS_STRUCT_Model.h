//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_OpenGLDefaults.h>



/**
 * @brief This structure creates a model object. The model object stores the mesh, textures, and positions. Please see the full list of attrbutes for more information.
 * 
 */
struct ERS_STRUCT_Model {


    std::vector<ERS_STRUCT_Texture> TexturesToPushToGPU_;
    std::vector<long> AttachedScriptIndexes_; /**<Indexes of attached scripts (index in the project struct's list of scripts)*/
    std::vector<unsigned int> OpenGLTextureIDs_;
    double LoadingStartTime_; /**<Time that the loading started*/
    double LoadingFinishTime_; /**<Time When Loading Was Completed*/
    double TotalLoadingTime_; /**<The Total Time Needed To Load*/
    unsigned long TotalVertices_; /**<Total Number Of Verts In This Model*/ 
    unsigned long TotalIndices_; /**<Total Number Of Indices In Model*/


    // Model Data
    std::vector<ERS_STRUCT_Mesh> Meshes;
    std::vector<ERS_STRUCT_Texture> Textures_Loaded;
    std::string Directory;
    std::string Name = "Name Not Assigned";
    long ShaderOverrideIndex_ = -1; /**<If not -1, This indicates that the model is requesting a custom shader, and the value is the index of the shader in the system*/
    long AssetID;



    // Shadows Information
    bool CastDynamicShadows_ = true; /**<Indicate if this model is to be rendered when generating the depth maps (dynamically)*/
    bool CastStaticShadows_ = true; /**<Set if this model is rendered when building static depth maps*/
    bool ReceiveShadows_ = true; /**<Determines if this model is to have shadows applied to it.*/



    // Enable Config
    bool Enabled = true;

    // Loading Config
    bool HasTexturesLoaded = false;
    bool HasMeshLoaded = false;
    bool IsReadyForGPU = false;
    bool FullyReady = false;

    // Model Config
    bool GammaCorrection = false;
    bool FlipTextures = false;
    bool IsTemplateModel = false; /**<This indicates if the model is a the "master" copy of instanced models.*/

    long MetadataID;
    long ModelDataID;
    
    std::vector<long> TextureIDs;
    

    // Model Information
    glm::vec3 ModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 ModelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 ModelScale = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::mat4 SourceModelLocRotScale_ = glm::mat4(1.0f);
    glm::mat4 ModelLocRotScale_ = glm::mat4(1.0f);




    /**
     * @brief Set the Position object (Overloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetPosition(double X, double Y, double Z);

    /**
     * @brief Set the Position object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Position 
     */
    void SetPosition(glm::vec3 Position);

    /**
     * @brief Set the Rotation object (OVerloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetRotation(double X, double Y, double Z);

    /**
     * @brief Set the Rotation object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Rotation 
     */
    void SetRotation(glm::vec3 Rotation);


    /**
     * @brief Set the Scale object (OVerloaded). Accepts X,Y,Z Floats. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param X 
     * @param Y 
     * @param Z 
     */
    void SetScale(double X, double Y, double Z);

    /**
     * @brief Set the Scale object (Overloaded). Accepts glm::vec3(x,y,z). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Scale 
     */
    void SetScale(glm::vec3 Scale);

    /**
     * @brief Set the Loc Rot Scale object (Overloaded) Sets the location, rotation, and scale by taking three doubles for each category. (XYZ). Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param LocX 
     * @param LocY 
     * @param LocZ 
     * @param RotX 
     * @param RotY 
     * @param RotZ 
     * @param ScaleX 
     * @param ScaleY 
     * @param ScaleZ 
     */
    void SetLocRotScale(double LocX, double LocY, double LocZ, double RotX, double RotY, double RotZ, double ScaleX, double ScaleY, double ScaleZ);

    /**
     * @brief Set the Loc Rot Scale object (Overloaded). Sets the location, rotation, and scale by taking three glm::vec3 variables for positiom, rotation, scale. Remember to Call ApplyTrsnformations When Ready.
     * 
     * @param Position 
     * @param Rotation 
     * @param Scale 
     */
    void SetLocRotScale(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale);

    /**
     * @brief Applies Transformatins Set By Using the Set (Loc/Rot/Scale) Methods. Returns True on success and False on failure (caused if model is a template model).
     *
     * @return true 
     * @return false 
     */
    bool ApplyTransformations();

    /**
     * @brief Get the Mat 4 object
     * 
     * @return glm::mat4 
     */
    glm::mat4 GetMat4();

    /**
     * @brief Updates the transparency of all meshes contained by this model.
     * 
     */
    void UpdateMeshTransparency();


};



