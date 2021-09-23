//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for model importing.
    Additonal Notes: None
    Date Created: 2021-09-22
*/   


#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(LoggerClass Logger, const char* VertexPath, const char* FragmentPath, const char* GeometryPath = nullptr)
    {
        // Retrieve The Vertex/Fragment Source Code From FilePath
        std::string vertexCode;
        std::string ragmentCode;
        std::string geometryCode;
        std::ifstream VertexShaderFile;
        std::ifstream FragmentShaderFile;
        std::ifstream GeometryShaderFile;

        // Enable Exceptions For ifstream
        VertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        FragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        GeometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);


        // Vertex File
        try {

            // Log File Read
            Logger.Log(std::string("Reading Vertex Shader File: " + std::string(VertexPath)).c_str(), 1);

            // Open And Read Vertex File
            VertexShaderFile.open(vertexPath);
            std::stringstream VertexShaderStream;
            VertexShaderStream << VertexShaderFile.rdbuf();
            VertexShaderFile.close();

            // Convert Stream Into String
            VertexCode = VertexShaderStream.str();
            const char* VertexShaderCode = vertexCode.c_str();
		

        } catch (std::ifstream::failure& e) {

            // Log Vertex File Read/Decode Error
            Logger.Log(std::string("ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ").c_str());
        }

        // Fragment File
        try {

            // Log File Read
            Logger.Log(std::string("Reading Fragment Shader File: " + std::string(FragmentPath)).c_str(), 1);

            // Open And Read Fragment File
            FragmentShaderFile.open(fragmentPath);
            std::stringstream FragmentShaderStream;
            FragmentShaderStream << FragmentShaderFile.rdbuf();
            FragmentShaderFile.close();

            // Convert Stream Into String
            FragmentCode = FragmentShaderStream.str();
            const char * FragmentShaderCode = fragmentCode.c_str();

        } catch (std::ifstream::failure& e) {

            // Log Vertex File Read/Decode Error
            Logger.Log(std::string("ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ").c_str());
        }



        // Geometry File
        try {
            if(GeometryPath != nullptr) {

                // Log File Read
                Logger.Log(std::string("Reading Geometry Shader File: " + std::string(GeometryPath)).c_str(), 1);

                // Open And Read Geometry File
                GeometryShaderFile.open(GeometryPath);
                std::stringstream GeometryShaderStream;
                GeometryShaderStream << GeometryShaderFile.rdbuf();
                GeometryShaderFile.close();

                // Convert Stream Into String
                GeometryCode = GeometryShaderStream.str();
                const char * GeometryShaderCode = GeometryCode.c_str();

            } else {
                // Log No Geometry Shader Specified
                Logger.Log("No Geometry Shader Specified, Skipping Geometry Shader", 1);
            }

        } catch (std::ifstream::failure& e) {

            // Log Vertex File Read/Decode Error
            Logger.Log(std::string("ERROR::SHADER::GEOMETRY::FILE_NOT_SUCCESFULLY_READ").c_str());
        }


        // Compile Shaders
        unsigned int Vertex, Fragment, Geometry;


        // Compile Vertex Shader
        Vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(Vertex, 1, &VertexShaderCode, NULL);
        glCompileShader(Vertex);
        checkCompileErrors(Logger, Vertex, "VERTEX");


        // Compile Fragment Shader
        Fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(Fragment, 1, &FragmentShaderCode, NULL);
        glCompileShader(Fragment);
        checkCompileErrors(Logger, Fragment, "FRAGMENT");


        // If Geometry shader Exists, Compile It
        if(GeometryPath != nullptr) {

            Geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(Geometry, 1, &GeometryShaderCode, NULL);
            glCompileShader(Geometry);
            checkCompileErrors(Logger, Geometry, "GEOMETRY");
        }


        // Create Shader Program
        ID = glCreateProgram();

        // Add Vertex, Fragment, Geometry Shaders To Program
        glAttachShader(ID, Vertex);
        glAttachShader(ID, Fragment);
        if(GeometryPath != nullptr) {
            glAttachShader(ID, Geometry);
        }

        // Link Program And Check For Compile Errors
        glLinkProgram(ID);
        checkCompileErrors(Logger, ID, "PROGRAM");


        // Delete Shader Components
        glDeleteShader(Vertex);
        glDeleteShader(Fragment);
        if(GeometryPath != nullptr) {
            glDeleteShader(Geometry);
        }

    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(LoggerClass Logger, GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                Logger.Log(std::string("ERROR::SHADER_COMPILATION_ERROR of type: " + std::string(type) + "\n" + std::string(infoLog)).c_str());
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                Logger.Log(std::string("ERROR::PROGRAM_LINKING_ERROR of type: " + std::string(type) + "\n" + std::string(infoLog)).c_str());
            }
        }
    }
};
  
#endif