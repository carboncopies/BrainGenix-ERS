//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#include <ERS_STRUCT_Shader.h>


// Shader Destructor
ERS_STRUCT_Shader::~ERS_STRUCT_Shader() {

    // Deallocate Shader Program
    glDeleteProgram(ShaderProgram);

}

// Compile Vertex Shader
std::string ERS_STRUCT_Shader::CompileVertexShader(const char* VertexText, std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {

    // Compile The Vertex Shader Text Into A Binary
    std::string ErrorMessage;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(VertexShader, 1, &VertexText, NULL);
    glCompileShader(VertexShader);

    // Report Compilation Status
    int VertexSuccess;
    char VertexInfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VertexSuccess);
    if (!VertexSuccess) {
        glGetShaderInfoLog(VertexShader, 512, NULL, VertexInfoLog);
        ErrorMessage = std::string(VertexInfoLog);
        if (Logger != nullptr) {
            Logger->Log("Vertex Shader Compile Error: " +  std::string(VertexInfoLog), 8);
        }
    }

    // Update Vars
    _VertexShaderInitialized = true;
    return ErrorMessage;

}

// Compile Fragment Shader
std::string ERS_STRUCT_Shader::CompileFragmentShader(const char* FragmentText, std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {

    // Compile The Fragment Shader Text Into A Binary
    std::string ErrorMessage;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(FragmentShader, 1, &FragmentText, NULL);
    glCompileShader(FragmentShader);

    // Report Compilation Status
    int FragmentSuccess;
    char FragmentInfoLog[512];
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FragmentSuccess);
    if (!FragmentSuccess) {
        glGetShaderInfoLog(FragmentShader, 512, NULL, FragmentInfoLog);
        ErrorMessage = std::string(FragmentInfoLog);
        if (Logger != nullptr) {
            Logger->Log("Fragment Shader Compile Error: " +  std::string(FragmentInfoLog), 8);
        }
    }

    // Update Vars
    _FragmentShaderInitialized = true;
    return ErrorMessage;

}


// Compile Shader Program
std::string ERS_STRUCT_Shader::CreateShaderProgram(bool DeleteShadersUponLink, std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {

    // Check That Vertex And Fragment Shaders Are Initialized
    std::string ErrorMessage;
    if (!_VertexShaderInitialized || !_FragmentShaderInitialized) {
        if (Logger != nullptr) {
            Logger->Log("Vertex/Fragment Shader Compile Error", 8);
        }
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
        ErrorMessage = std::string(InfoLog);
        if (Logger != nullptr) {
            Logger->Log("Shader Link Error: " +  std::string(InfoLog), 8);
        }
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

    // Return Status
    return ErrorMessage;

}

// Make Shader Active
void ERS_STRUCT_Shader::MakeActive(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {

    if ((Logger != nullptr)  && (!_ShaderProgramInitialized)) {
        Logger->Log("Shader Not Yet Initialized", 8);
    }

    glUseProgram(ShaderProgram);

}


// Population Functions
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
}
void ERS_STRUCT_Shader::SetFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
