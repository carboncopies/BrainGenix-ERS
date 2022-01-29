//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Library (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief The Shader Loader Is Responsible For Populating Shader Structs.
 * 
 */
class ShaderLoader {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer To Instance Of SystemUtils*/


    public:

        /**
         * @brief Construct a new Shader Loader object
         * 
         * @param SystemUtils
         */
        ShaderLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

        /**
         * @brief Destroy the Shader Loader object
         * 
         */
        ~ShaderLoader();
        

        /**
         * @brief Create a Shader Object object
         * 
         * @param VertexText 
         * @param FragmentText 
         * @return ERS_OBJECT_SHADER 
         */
        std::shared_ptr<ERS_OBJECT_SHADER> CreateShaderObject(const char* VertexText, const char* FragmentText);


        /**
         * @brief 
         * 
         * @param VertexPath 
         * @param FragmentPath 
         * @return ERS_OBJECT_SHADER 
         */
        std::shared_ptr<ERS_OBJECT_SHADER> LoadShaderFromFile(const char* VertexPath, const char* FragmentPath);



};