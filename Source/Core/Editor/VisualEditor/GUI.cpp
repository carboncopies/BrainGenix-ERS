//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing the gui.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#include <GUI.h>


// GUISystem Constructor
GUISystem::GUISystem(LoggerClass* Logger, GLFWwindow* Window, bool *SystemShouldRun) {

    // Create Local Pointer
    Logger_ = Logger;
    Window_ = Window;
    SystemShouldRun_ = SystemShouldRun;


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

    // Initializing Theme Loader
    ThemeManager_ = new ThemeManager(Logger_);

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


    // Enable Docking
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Setup Dockspace
    ImGui::DockSpaceOverViewport();


    ImGui::ShowDemoWindow();





    ImGui::Begin("System Controls");


    // Wireframe Rendering Mode
    static bool OpenGLDrawLines = false;
    ImGui::Checkbox("Wireframe Rendering Mode", &OpenGLDrawLines);
    ImGui::NewLine();
    if (OpenGLDrawLines) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }


    // Rendering Background Clear Color
    static ImVec4 ClearColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    ImGui::ColorEdit4("Background Clear Color", (float*)&ClearColor);
    ImGui::NewLine();
    glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);



    // End System Controls Window
    ImGui::End();




    // System Info Window
    ImGui::Begin("System Info");

    // FPS Counter
    ImGui::Text("System Framerate %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    // End System Info Window
    ImGui::End();






    // Update Windows
    UpdateWindow_ColorThemePicker();


    // Add Main Menu
    if (ImGui::BeginMainMenuBar()) {

        // Add File Menu
        if (ImGui::BeginMenu("File")) {

                if (ImGui::MenuItem("Exit")) {
                    MenuExitFunction();
                }

            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {


                if (ImGui::MenuItem("Color Theme")) {
                    ShowColorThemePicker_ = true;
                }


            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }







}

void GUISystem::UpdateWindow_ColorThemePicker() {

    // Draw Color Picker Menu
    if (ShowColorThemePicker_) {
        ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking;
        ImGui::Begin("Pick Color Theme", &ShowColorThemePicker_, Flags);

            ImGui::SetWindowSize(ImVec2(0, 0));


            // Put Radio Buttons Here
            ImGui::BeginChild("Theme Selector", ImVec2(250, 250), true);

                static int ThemeSelector = 0;
                for (int i = 0; i < ThemeManager_->ThemeNames_.size(); i++) {

                    ImGui::RadioButton(ThemeManager_->ThemeNames_[i].c_str(), &ThemeSelector, i);

                }
                

            ImGui::EndChild();


            ImGui::Separator();


            // Reload Button
            if (ImGui::Button("Reload Themes")) {
                ThemeManager_->LoadThemes();
            }
            ImGui::SameLine();

            // Apply Button
            if (ImGui::Button("Apply")) {
                ThemeManager_->ApplyThemes(ThemeSelector);
            }
            ImGui::SameLine();

            // Close Button
            if (ImGui::Button("Close")) {
                ShowColorThemePicker_ = false;
            }
            

        ImGui::End();
    }

}

void GUISystem::UpdateFrame() {

    // Rendering
    ImGui::Render();

    // Draw The GUI
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}

void GUISystem::MenuExitFunction() {

    // Shutdown System
    *SystemShouldRun_ = false;
    
}