//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#include "Core/Renderer/VisualRenderer/ShaderCompiler.h"

unsigned int ShaderCompiler(const char* ShaderText, LoggerClass *Logger_) {

    // Compile The Vertex Shader Text Into A Binary
    unsigned int VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(VertexShader);

    // Report Compilation Status
    int Success;
    char InfoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
    if (!Success) {
        Logger_->Log("Shader Compilation Failed", 10);
        Logger_->Log(InfoLog, 10);
    }




}