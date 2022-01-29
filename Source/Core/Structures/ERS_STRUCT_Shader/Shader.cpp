//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-02
*/



#include "Shader.h"


// Compile Vertex Shader
void ERS_OBJECT_SHADER::CompileVertexShader(const char* VertexText) {

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

// Compile Fragment Shader
void ERS_OBJECT_SHADER::CompileFragmentShader(const char* FragmentText) {

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


// Compile Shader Program
void ERS_OBJECT_SHADER::CreateShaderProgram(bool DeleteShadersUponLink) {

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

// Make Shader Active
void ERS_OBJECT_SHADER::MakeActive() {

    if (!_ShaderProgramInitialized) {
        std::cout << "Shader Program Not Yet Initialised\n";
    }

    glUseProgram(ShaderProgram);

}


// Population Functions
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
}
void ERS_OBJECT_SHADER::SetFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_OBJECT_SHADER::SetVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_OBJECT_SHADER::SetVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_OBJECT_SHADER::SetVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_OBJECT_SHADER::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
