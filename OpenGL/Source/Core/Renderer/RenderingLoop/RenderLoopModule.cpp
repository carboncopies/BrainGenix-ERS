//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/   

#include "Core/SystemInput/WindowInput/WindowInputModule.cpp"

void MainRenderLoop(GLFWwindow* Window) {

    // Create System Shutdown Variable //
    bool SystemShutdownInvoked = false;

    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // Rendering Commands Here //
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        float vertices[] = {
        -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
        };  


        // allocate gpu mem to store verts
        unsigned int VBO;
        glGenBuffers(1, &VBO); 

        glBindBuffer(GL_ARRAY_BUFFER, VBO);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // note gl_static_draw can be changed for other purposes (look this up later)


        // create vertex shader
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);


        // compile vertex shader
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);


        // Check vertex shader compile status
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "} ";

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);


        // link shaders into shader program
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // use program
        glUseProgram(shaderProgram);

        // delete old shader objects
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);  



        // load in verts
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  


        // 0. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 1. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        // 2. use our shader program when we want to render an object
        glUseProgram(shaderProgram);
        // 3. now draw the object 



        // vertex array object? idk anymore
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);  

        // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
        // 1. bind Vertex Array Object
        glBindVertexArray(VAO);
        // 2. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. then set our vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        




        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);





        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Update Window User Input //
            ProcessWindowInput(Window);

            // Check For Shutdown Events //
            SystemShutdownInvoked = glfwWindowShouldClose(Window);


            // GLFW Window Update //
            glfwSwapBuffers(Window);
            glfwPollEvents(); 

        }

   
    }

}