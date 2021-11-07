//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/



void Renderer::InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;

    // Initialize Systems
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

void Renderer::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    stbi_set_flip_vertically_on_load(false);


    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();

    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    // Create Window Object
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window_);

}

void Renderer::InitializeOpenGL() {


    // Setup Viewport
    Logger_->Log("Read Configuration File For 'RenderWidth' Parameter", 1);
    RenderWidth_ = (*SystemConfiguration_)["RenderWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'RenderHeight' Parameter", 1);
    RenderHeight_ = (*SystemConfiguration_)["RenderHeight"].as<int>();

    // Register Callback
    glfwMakeContextCurrent(Window_);
    //glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(Window_, FramebufferSizeCallback);
    glfwSetCursorPosCallback(Window_, MouseCallback);
    glfwSetScrollCallback(Window_, ScrollCallback);

    // Grab Mouse
    glfwSetInputMode(Window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger_->Log("Failed To Initialize GLAD", 10);
    }


    // Draw Faces In Front First
    glEnable(GL_DEPTH_TEST);

    // Setup Shaders
    Shader_ = LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag", Logger_);

    // Load Model
    float T1 = glfwGetTime();
    Model_.LoadModelFromFile("Assets/Brown_Rock_003/Brown_Rock_003.fbx");
    std::cout << "Model Loading Took: " << glfwGetTime()-T1 << " Seconds\n";



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader_.MakeActive();



}

bool Renderer::UpdateLoop() { 

    // Update DeltaTime
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastFrame;
    LastFrame = CurrentTime;

    // Process Window Input
    ProcessInput(Window_, Logger_, &Camera_, DeltaTime);

    // Rendering Commands Here
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Use Shader
    Shader_.MakeActive();



    glm::mat4 projection = glm::perspective(glm::radians(Camera_.Zoom), (float)RenderWidth_ / (float)RenderHeight_, 0.1f, 100.0f);
    glm::mat4 view = Camera_.GetViewMatrix();
    Shader_.SetMat4("projection", projection);
    Shader_.SetMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model_.Draw(Shader_);





    // Update Window Stuff
    glfwSwapBuffers(Window_);
    glfwPollEvents();



    // Update Window Title With FPS Counter
    std::string NewWindowTitle = std::string(std::string("BrainGenix-ERS") + std::string(" - ") + std::to_string(1/DeltaTime) + std::string(" FPS"));
    glfwSetWindowTitle(Window_, NewWindowTitle.c_str());

    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        return false;
    }

    // System Should Not Shutdown
    return true;

}


void Renderer::CleanUp() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}


