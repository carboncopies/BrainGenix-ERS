//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Library (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_IOData.h>
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief The Shader Loader Is Responsible For Populating Shader Structs.
 * 
 */
class ERS_CLASS_ShaderLoader {


private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer To Instance Of SystemUtils*/


public:


    /**
     * @brief Construct a new Shader Loader object
     * 
     * @param SystemUtils
     */
    ERS_CLASS_ShaderLoader(ERS_STRUCT_SystemUtils* SystemUtils);


    /**
     * @brief Destroy the Shader Loader object
     * 
     */
    ~ERS_CLASS_ShaderLoader();
    

    /**
     * @brief Create a Shader Object object
     * 
     * @param VertexText 
     * @param FragmentText 
     * @return ERS_STRUCT_Shader 
     */
    std::shared_ptr<ERS_STRUCT_Shader> CreateShaderObject(const char* VertexText, const char* FragmentText, bool LogBuild = true);


    /**
     * @brief Load vertex/fragment shaders from the IOSubsystem.
     * 
     * @param VertexID 
     * @param FragmentID 
     * @return std::shared_ptr<ERS_STRUCT_Shader> 
     */
    std::shared_ptr<ERS_STRUCT_Shader> LoadShaderFromAsset(long VertexID, long FragmentID, std::string ShaderName = "Untitled Shader");



};