//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing the gui.
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#include <GUI.h>


// GUISystem Constructor
GUISystem::GUISystem(LoggerClass* Logger, GLFWwindow* Window) {

    // Create Local Pointer
    Logger_ = Logger;
    Window_ = Window;

    // Initialize ImGui
    Logger_->Log("Initializing DearImGui GUI Library", 5);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");







}

// GUISystem Destructor
GUISystem::~GUISystem() {

    // Log Destructor Call
    Logger_->Log("GUISystem Destructor Called", 6);

    // Deinit ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

// Update GUI
void GUISystem::UpdateGUI() {

    // Get Window Width, Height
    float Width;
    float Height;
    glfwGetWindowContentScale(Window_, &Width, &Height);


    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.


    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("System Controls");

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("System Framerate %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }



    // // create an ImGui window that covers the entire viewport, so that we can have a menu bar at the top of the applications
    // ImGui::SetNextWindowPos(ImVec2(0, 0));                                                  // always at the window origin
    // ImGui::SetNextWindowSize(ImVec2(Width, Height));    // always at the window size

    // ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoBringToFrontOnFocus |                 // we just want to use this window as a host for the menubar and docking
    //     ImGuiWindowFlags_NoNavFocus |                                                      // so turn off everything that would make it act like a window
    //     //ImGuiWindowFlags_NoDocking |
    //     ImGuiWindowFlags_NoTitleBar |
    //     ImGuiWindowFlags_NoResize |
    //     ImGuiWindowFlags_NoMove |
    //     ImGuiWindowFlags_NoCollapse |
    //     ImGuiWindowFlags_MenuBar |
    //     ImGuiWindowFlags_NoBackground;                                                      // we want our game content to show through this window, so turn off the background.

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));   








    // Rendering
    ImGui::Render();


}

// Update Frame
void GUISystem::UpdateFrame() {

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}