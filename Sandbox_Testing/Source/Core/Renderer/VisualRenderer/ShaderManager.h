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

    // Utility Functions
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

    void MakeActive() {

        if (!_ShaderProgramInitialized) {
            std::cout << "Shader Program Not Yet Initialised\n";
        }

        glUseProgram(ShaderProgram);
    
    }


    // Population Functions
    void SetBool(const std::string &Name, bool Value) const
    {         
        glUniform1i(glGetUniformLocation(ShaderProgram, Name.c_str()), (int)Value); 
    }

    void SetInt(const std::string &Name, int Value) const
    { 
        glUniform1i(glGetUniformLocation(ShaderProgram, Name.c_str()), Value); 
    }

    void SetFloat(const std::string &Name, float Value) const
    { 
        glUniform1f(glGetUniformLocation(ShaderProgram, Name.c_str()), Value); 
    }

};


ShaderObject CreateShaderObject(const char* VertexText, const char* FragmentText, LoggerClass *Logger_);

ShaderObject LoadShaderFromFile(const char* VertexPath, const char* FragmentPath, LoggerClass *Logger_);