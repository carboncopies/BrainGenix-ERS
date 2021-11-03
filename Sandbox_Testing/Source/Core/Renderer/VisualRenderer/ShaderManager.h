//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the shader compiler.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

// Structure To Hold Shader Ids
struct ShaderObject{

    unsigned int ShaderProgram;

    unsigned int VertexShader;
    unsigned int FragmentShader;

    bool _VertexShaderInitialized = false;
    bool _FragmentShaderInitialized = false;
    bool _ShaderProgramInitialized = false;

    void PopulateVertexShader(unsigned int VertexShaderInput) {

        // Update Vars
        VertexShader = VertexShaderInput;
        _VertexShaderInitialized = true;

    }

    void PopulateFragmentShader(unsigned int FragmentShaderInput) {

        // Update Vars
        FragmentShader = FragmentShaderInput;
        _FragmentShaderInitialized = true;

    }

    void CreateShaderProgram(bool DeleteShadersUponLink = true) {

        // Check That Vertex And Fragment Shaders Are Initialized
        if (!_VertexShaderInitialized || !_FragmentShaderInitialized) {
            std::cout<<"Vertex/Fragment Shader Not Yet Initialized\n";
        }

        // Attach Shaders To Program
        glAttachShader(ShaderProgram, VertexShader);
        glAttachShader(ShaderProgram, FragmentShader);

        // Link Program
        glLinkProgram(ShaderProgram);


        // Get Link Status
        int Success;
        char InfoLog[512];
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
        if (!Success) {
            glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
            std::cout<<InfoLog;
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

    void MakeActive() {

        if (!_ShaderProgramInitialized) {
            std::cout << "Shader Program Not Yet Initialised\n";
        }

        glUseProgram(ShaderProgram);
    
    }

};


unsigned int VertexShaderCompiler(const char* VertexText, LoggerClass *Logger_);

unsigned int FragmentShaderCompiler(const char* FragmentText, LoggerClass *Logger_);

ShaderObject CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_);

ShaderObject LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_);