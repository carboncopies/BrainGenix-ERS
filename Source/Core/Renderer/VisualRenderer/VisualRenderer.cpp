//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#include <VisualRenderer.h>


// FIX THIS LATER!!
static void FramebufferSizeCallback(GLFWwindow* /*Window*/, int Width, int Height) {

    // Update Viewport
    glViewport(0,0, Width, Height);
    glScissor(0, 0, Width, Height);


}


static void MouseCallback(GLFWwindow* /*Window*/, double XPos, double YPos) {

    // Update Positions
    if (FirstMouse) {

        LastX = XPos;
        LastY = YPos;

        FirstMouse = false;

    }

    // Calculate Offsets
    float XOffset = XPos - LastX;
    float YOffset = YPos - LastY;

    // Update Last Positions
    LastX = XPos;
    LastY = YPos;

    // Process Camera Movement
    Camera_.ProcessMouseMovement(XOffset, YOffset);

}



static void ScrollCallback(GLFWwindow* /*Window*/, double /*XOffset*/, double YOffset) {

    Camera_.ProcessMouseScroll(YOffset);

}
// END FIX !


void ErrorCallback(int, const char* ErrorString) {
    std::cout<<"GLFW ERROR: " << ErrorString << std::endl;
}




VisualRenderer::VisualRenderer (YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;

    // Initialize Texture Loader
    TextureLoader_ = new TextureLoader(Logger_);

    // Initialize Systems
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

VisualRenderer::~VisualRenderer() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}



void VisualRenderer::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();

    //glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

    // Create Window Object
    glfwSetErrorCallback(ErrorCallback);
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window_);

}

void VisualRenderer::InitializeOpenGL() {


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

    // Enable Scissor Test
    glEnable(GL_SCISSOR_TEST);

    // Setup Shaders
    Shader_ = LoadShaderFromFile("Shaders/Main.vert", "Shaders/Main.frag", Logger_);

    // Load Model
    ModelLoader MLoader(Logger_, TextureLoader_);
    Model_ = MLoader.LoadModelFromFile("Assets/S1/scene.gltf");
    Model2_ = MLoader.LoadModelFromFile("Assets/S2/scene.gltf");
    Model3_ = MLoader.LoadModelFromFile("Assets/S3/scene.gltf");
    Model4_ = MLoader.LoadModelFromFile("Assets/S4/scene.gltf");
    Model5_ = MLoader.LoadModelFromFile("Assets/S5/scene.gltf", true);
    



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader_.MakeActive();



}

void VisualRenderer::UpdateLoop() {


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




        

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model_.Draw(Shader_);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model2_.Draw(Shader_);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-8.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model3_.Draw(Shader_);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-12.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model4_.Draw(Shader_);


    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(-0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Shader_.SetMat4("model", model);
    Model5_.Draw(Shader_);


    // Update Window Stuff
    glfwSwapBuffers(Window_);
    glfwPollEvents();



    // Update Window Title With FPS Counter
    std::string NewWindowTitle = std::string((*SystemConfiguration_)["WindowTitle"].as<std::string>() + std::string(" - ") + std::to_string(1/DeltaTime) + std::string(" FPS"));
    glfwSetWindowTitle(Window_, NewWindowTitle.c_str());

    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        *SystemShouldRun_ = false;
    }

}