//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#include <ERS_STRUCT_Shader.h>


ERS_STRUCT_Shader::ERS_STRUCT_Shader() {
    std::cout<<"1|"<<glGetError()<<std::endl;

    ShaderProgram_ = 0;
    VertexShader = 0;
    FragmentShader = 0;

    VertexID = 0;
    FragmentID = 0;
    std::cout<<"2|"<<glGetError()<<std::endl;

}

ERS_STRUCT_Shader::~ERS_STRUCT_Shader() {

    // Deallocate Shader Program
    glUseProgram(0);
    glDeleteProgram(ShaderProgram_);

}

std::string ERS_STRUCT_Shader::CompileVertexShader(const char* VertexText, ERS_CLASS_LoggingSystem* Logger) {

    // Compile The Vertex Shader Text Into A Binary
    std::string ErrorMessage;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(VertexShader, 1, &VertexText, NULL);
    glCompileShader(VertexShader);

    // Report Compilation Status
    int VertexSuccess;
    char VertexInfoLog[65535];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VertexSuccess);
    if (!VertexSuccess) {
        glGetShaderInfoLog(VertexShader, 65535, NULL, VertexInfoLog);
        ErrorMessage = std::string(VertexInfoLog);
        if (Logger != nullptr) {
            Logger->Log("Vertex Shader Compile Error: " +  std::string(VertexInfoLog), 8);
        }
    }


    return ErrorMessage;

}

std::string ERS_STRUCT_Shader::CompileFragmentShader(const char* FragmentText, ERS_CLASS_LoggingSystem* Logger) {

    // Compile The Fragment Shader Text Into A Binary
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(FragmentShader, 1, &FragmentText, NULL);
    glCompileShader(FragmentShader);

    // Report Compilation Status
    int FragmentSuccess;
    char FragmentInfoLog[65535];
    std::string ErrorMessage;
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FragmentSuccess);
    if (!FragmentSuccess) {
        glGetShaderInfoLog(FragmentShader, 65535, NULL, FragmentInfoLog);
        ErrorMessage = std::string(FragmentInfoLog);
        if (Logger != nullptr) {
            Logger->Log("Fragment Shader Compile Error: " +  std::string(FragmentInfoLog), 8);
        }
    }

    return ErrorMessage;

}


std::string ERS_STRUCT_Shader::CreateShaderProgram(ERS_CLASS_LoggingSystem* Logger) {

    // Create Shader Program
    ShaderProgram_ = glCreateProgram();

    // Attach Shaders To Program
    glAttachShader(ShaderProgram_, VertexShader);
    glAttachShader(ShaderProgram_, FragmentShader);

    // Link Program
    glLinkProgram(ShaderProgram_);


    // Get Link Status
    int Success;
    std::string ErrorMessage;
    glGetProgramiv(ShaderProgram_, GL_LINK_STATUS, &Success);
    if (!Success) {
        char InfoLog[65535];
        glGetProgramInfoLog(ShaderProgram_, 65535, NULL, InfoLog);
        ErrorMessage = std::string(InfoLog);
        if (Logger != nullptr) {
            Logger->Log("Shader Link Error: " +  std::string(InfoLog), 8);
        }
    }

    // Free RAM
    glDetachShader(ShaderProgram_, VertexShader);
    glDeleteShader(VertexShader);

    glDetachShader(ShaderProgram_, FragmentShader);
    glDeleteShader(FragmentShader);




    // Return Status
    return ErrorMessage;

}

bool ERS_STRUCT_Shader::MakeActive() {

    glUseProgram(ShaderProgram_);
    return true;

}


// Population Functions
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ShaderProgram_, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ShaderProgram_, name.c_str()), value); 
}
void ERS_STRUCT_Shader::SetFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ShaderProgram_, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ShaderProgram_, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ShaderProgram_, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, &value[0]); 
}
void ERS_STRUCT_Shader::SetVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(ShaderProgram_, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ERS_STRUCT_Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
