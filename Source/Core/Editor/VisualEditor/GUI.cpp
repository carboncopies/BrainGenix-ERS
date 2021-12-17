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
GUISystem::GUISystem(ERS_STRUCT_SystemUtils SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D, std::shared_ptr<SceneManager> SceneManager) {

    // Create Local Pointer
    SystemUtils_ = SystemUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;
    SceneManager_ = SceneManager;

    // Initialize ImGui
    SystemUtils_.Logger_->Log("Initializing DearImGui GUI Library", 5);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Initialize Managers
    ThemeManager_ = std::make_shared<ERS_CLASS_ThemeManager>(SystemUtils_.Logger_);
    FontManager_ = std::make_shared<ERS_CLASS_FontManager>(SystemUtils_.Logger_);
    UserProfileManager_ = std::make_shared<ERS_CLASS_UserProfileManager>(SystemUtils_.Logger_);

    // Load User Profile
    ThemeManager_->ApplyThemes(UserProfileManager_->GetUserColorProfile().c_str());
    FontManager_->UseFont(UserProfileManager_->GetUserFont());
    FontManager_->SetFontSize(UserProfileManager_->GetUserFontSize());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    // Initialize Windows
    SystemUtils_.Logger_->Log("Initializing Editor Menu", 5);
    Menu_File_ = std::make_unique<GUI_Menu_File>(SystemUtils_, SceneManager_);

    // Initialize Widgets
    SystemUtils_.Logger_->Log("Initializing Editor Widgets", 5);
    Widget_ObjectProperties_ = std::make_shared<Widget_ObjectProperties>(Cursors3D_);

    // Initialize Windows
    SystemUtils_.Logger_->Log("Initializing Editor Windows", 5);
    Window_SceneTree_ = std::make_shared<Window_SceneTree>(SceneManager_);


}

// GUISystem Destructor
GUISystem::~GUISystem() {

    // Log Destructor Call
    SystemUtils_.Logger_->Log("GUISystem Destructor Called", 6);

    // Deinit ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();

}

// Update GUI
void GUISystem::UpdateGUI() {

    
    // CheckUpdate Font
    FontManager_->CheckUpdateFont();


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


    // Begin Guizmo
    ImGuizmo::BeginFrame();

    //ImGui::ShowDemoWindow();






    // Update Windows
    UpdateWindow_ColorThemePicker();

    // Update Widgets
    Widget_FramerateCounter_.Draw();
    Widget_RenderingSettings_.Draw();
    Widget_FramerateHistogram_.Draw();
    Widget_FramerateGraph_.Draw();
    Widget_FrameratePlot_.Draw();

    Window_SceneTree_->Draw();

    FontManager_->FontSelectorWindow(&ShowFontPicker_);



    // Add Main Menu
    if (ImGui::BeginMainMenuBar()) {

        Menu_File_->Draw();

        // View Menu
        if (ImGui::BeginMenu("View")) {


            if (ImGui::MenuItem("Color Theme")) {
                ShowColorThemePicker_ = true;
            }

            if (ImGui::MenuItem("System Font")) {
                ShowFontPicker_ = true;
            }


        ImGui::EndMenu();
        }

        // Window Menu
        if (ImGui::BeginMenu("Window")) {

            // Add Widgets Menu
            if (ImGui::BeginMenu("Widgets")) {

                // Framerate Widgets
                if (ImGui::BeginMenu("Framerate")) {

                    // Framerate Related Tools
                    ImGui::Checkbox("Framerate Counter", &Widget_FramerateCounter_.Enabled_);
                    ImGui::Checkbox("Framerate Histogram", &Widget_FramerateHistogram_.Enabled_);
                    ImGui::Checkbox("Framerate Graph", &Widget_FramerateGraph_.Enabled_);
                    ImGui::Checkbox("Framerate Plot", &Widget_FrameratePlot_.Enabled_);

                ImGui::EndMenu();
                }

                // Viewport Widgets
                if (ImGui::BeginMenu("Viewport")) {

                    // Viewport Settings
                    ImGui::Checkbox("Object Properties", &Widget_ObjectProperties_->Enabled_);
                    ImGui::Checkbox("Global Viewport Settings", &Widget_RenderingSettings_.Enabled_);
                    

                ImGui::EndMenu();
                }


            ImGui::EndMenu();
            }

            // Add Windows Menu
            if (ImGui::BeginMenu("Windows")) {

                // Add Scene Tree Editor Window
                ImGui::Checkbox("Scene Tree", &Window_SceneTree_->Enabled_);
                
            ImGui::EndMenu();
            }



        ImGui::EndMenu();
        }

    ImGui::EndMainMenuBar();
    }







}

// Deferred Update
void GUISystem::DeferredFrameUpdate() {

    // Update Widgets
    Widget_ObjectProperties_->Draw();

}

//FIXME: MOVE MENU UPDATE FUNCTION OUT OF GUP INTO THIS FUNCTION!!!!
void GUISystem::UpdateWindow_ColorThemePicker() {

    // Draw Color Picker Menu
    if (ShowColorThemePicker_) {
        ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
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