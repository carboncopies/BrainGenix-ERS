//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

// Standard Library (BG convention: use <> instead of "")
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <FileIO.h>




/**
 * @brief Structure To Store Shader Object
 * 
 */
struct ERS_OBJECT_SHADER {

    // Constructor
    ERS_OBJECT_SHADER() {
    }

    // Destructor
    ~ERS_OBJECT_SHADER() {
    }

    unsigned int ShaderProgram; /**<OpenGL refernece ID for Shader Program */

    unsigned int VertexShader; /**<OpenGL Reference ID for Vertex Shader */
    unsigned int FragmentShader; /**<OpenGL Reference ID For Fragment Shader */

    bool _VertexShaderInitialized = false; /**<Control Variable indicating Vertex Shader Initialization Status */
    bool _FragmentShaderInitialized = false; /**<Control Variable Indicating Fragment Shader Initialization Status */
    bool _ShaderProgramInitialized = false; /**<Control Variable Indicating Shader Program Initializatation Status */

    /**
     * @brief Function To Compile Vertex Shader With Given Code (const char*)
     * 
     * @param VertexText 
     */
    void CompileVertexShader(const char* VertexText);

    /**
     * @brief Function To Compile Fragment Shader With Given Code (const char*)
     * 
     * @param FragmentText 
     */
    void CompileFragmentShader(const char* FragmentText);

    /**
     * @brief Create a Shader Program object from Fragment and Vertex Shaders.
     * 
     * @param DeleteShadersUponLink 
     */
    void CreateShaderProgram(bool DeleteShadersUponLink = true);

    /**
     * @brief Make The Shader Stored Within The Struct Active.
     * 
     */
    void MakeActive();


    // Population Functions
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Bool object
     * 
     * @param name 
     * @param value 
     */
    void SetBool(const std::string &name, bool value) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Int object
     * 
     * @param name 
     * @param value 
     */
    void SetInt(const std::string &name, int value) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Float object
     * 
     * @param name 
     * @param value 
     */
    void SetFloat(const std::string &name, float value) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 2 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    /**
     * @brief Set the Vec 2 object
     * 
     * @param name 
     * @param x 
     * @param y 
     */
    void SetVec2(const std::string &name, float x, float y) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 3 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    /**
     * @brief Set the Vec 3 object
     * 
     * @param name 
     * @param x 
     * @param y 
     * @param z 
     */
    void SetVec3(const std::string &name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 4 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec4(const std::string &name, const glm::vec4 &value) const;
    /**
     * @brief Set the Vec 4 object
     * 
     * @param name 
     * @param x 
     * @param y 
     * @param z 
     * @param w 
     */
    void SetVec4(const std::string &name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 2 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 3 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 4 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

};

// FIXME: MOVE THISE TO OTHER (seperate) Shader Loader Class

