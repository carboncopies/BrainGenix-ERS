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
    void CompileVertexShader(const char* VertexText) {

        // Compile The Vertex Shader Text Into A Binary
        VertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(VertexShader, 1, &VertexText, NULL);
        glCompileShader(VertexShader);

        // Report Compilation Status
        int VertexSuccess;
        char VertexInfoLog[512];
        glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VertexSuccess);
        if (!VertexSuccess) {
            glGetShaderInfoLog(VertexShader, 512, NULL, VertexInfoLog);
            std::cout<<"Shader Compile Error: " << VertexInfoLog << std::endl;
        }

        // Update Vars
        _VertexShaderInitialized = true;

    }

    /**
     * @brief Function To Compile Fragment Shader With Given Code (const char*)
     * 
     * @param FragmentText 
     */
    void CompileFragmentShader(const char* FragmentText) {

        // Compile The Fragment Shader Text Into A Binary
        FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(FragmentShader, 1, &FragmentText, NULL);
        glCompileShader(FragmentShader);

        // Report Compilation Status
        int FragmentSuccess;
        char FragmentInfoLog[512];
        glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FragmentSuccess);
        if (!FragmentSuccess) {
            glGetShaderInfoLog(FragmentShader, 512, NULL, FragmentInfoLog);
            std::cout<<"Shader Compile Error: " << FragmentInfoLog << std::endl;
        }

        // Update Vars
        _FragmentShaderInitialized = true;

    }

    /**
     * @brief Create a Shader Program object from Fragment and Vertex Shaders.
     * 
     * @param DeleteShadersUponLink 
     */
    void CreateShaderProgram(bool DeleteShadersUponLink = true) {

        // Check That Vertex And Fragment Shaders Are Initialized
        if (!_VertexShaderInitialized || !_FragmentShaderInitialized) {
            std::cout<<"Vertex/Fragment Shader Not Yet Initialized\n";
        }

        // Create Shader Program
        ShaderProgram = glCreateProgram();

        // Attach Shaders To Program
        glAttachShader(ShaderProgram, VertexShader);
        glAttachShader(ShaderProgram, FragmentShader);

        // Link Program
        glLinkProgram(ShaderProgram);


        // Get Link Status
        int Success;
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
        if (!Success) {
            char InfoLog[512];
            glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
            std::cout << "SHADER LINK ERROR: " << InfoLog << std::endl;
        } else {
            _ShaderProgramInitialized = true;
        }

        // Delete Old Shaders
        if (DeleteShadersUponLink) {

            // Free RAM
            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);

            // Set State Of Vertex/Fragment Shaders To Uninit
            _VertexShaderInitialized = false;
            _FragmentShaderInitialized = false;

        }

    }

    /**
     * @brief Make The Shader Stored Within The Struct Active.
     * 
     */
    void MakeActive() {

        if (!_ShaderProgramInitialized) {
            std::cout << "Shader Program Not Yet Initialised\n";
        }

        glUseProgram(ShaderProgram);
    
    }


    // Population Functions
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Bool object
     * 
     * @param name 
     * @param value 
     */
    void SetBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Int object
     * 
     * @param name 
     * @param value 
     */
    void SetInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Float object
     * 
     * @param name 
     * @param value 
     */
    void SetFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 2 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
    }
    /**
     * @brief Set the Vec 2 object
     * 
     * @param name 
     * @param x 
     * @param y 
     */
    void SetVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 3 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
    }
    /**
     * @brief Set the Vec 3 object
     * 
     * @param name 
     * @param x 
     * @param y 
     * @param z 
     */
    void SetVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Vec 4 object
     * 
     * @param name 
     * @param value 
     */
    void SetVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
    }
    /**
     * @brief Set the Vec 4 object
     * 
     * @param name 
     * @param x 
     * @param y 
     * @param z 
     * @param w 
     */
    void SetVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 2 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 3 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    /**
     * @brief Set the Mat 4 object
     * 
     * @param name 
     * @param mat 
     */
    void SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }



    /**
     * @brief Create a Shader Object
     * 
     * @param VertexText 
     * @param FragmentText 
     * @param Logger_ 
     */
    CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_);

    /**
     * @brief Construct a new Shader From File object
     * 
     * @param VertexPath 
     * @param FragmentPath 
     * @param Logger_ 
     */
    LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_);



};


