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
GUISystem::GUISystem(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<VisualRenderer> VisualRenderer) {

    // Create Local Pointer
    SystemUtils_ = SystemUtils;
    Window_ = Window;
    Cursors3D_ = Cursors3D;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;
    VisualRenderer_ = VisualRenderer;

    // Initialize ImGui
    SystemUtils_->Logger_->Log("Initializing DearImGui GUI Library", 5);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Initialize Managers
    ThemeManager_ = std::make_shared<ERS_CLASS_ThemeManager>(SystemUtils_->Logger_);
    FontManager_ = std::make_shared<ERS_CLASS_FontManager>(SystemUtils_->Logger_);
    UserProfileManager_ = std::make_shared<ERS_CLASS_UserProfileManager>(SystemUtils_->Logger_);

    // Load User Profile
    ThemeManager_->ApplyThemes(UserProfileManager_->GetUserColorProfile().c_str());
    FontManager_->UseFont(UserProfileManager_->GetUserFont());
    FontManager_->SetFontSize(UserProfileManager_->GetUserFontSize());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    // Initialize Windows
    SystemUtils_->Logger_->Log("Initializing Editor Menu", 5);
    Menu_File_ = std::make_unique<GUI_Menu_File>(SystemUtils_, SceneManager_, ProjectUtils_);
    Menu_View_ = std::make_unique<GUI_Menu_View>(SystemUtils_, ThemeManager_, FontManager_);
    Menu_Window_ = std::make_unique<GUI_Menu_Window>(SystemUtils_, Cursors3D_, SceneManager_);
    Menu_Debug_ = std::make_unique<GUI_Menu_Debug>(SystemUtils_);




}

// GUISystem Destructor
GUISystem::~GUISystem() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUISystem Destructor Called", 6);

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


    // Add Main Menu
    if (ImGui::BeginMainMenuBar()) {

        Menu_File_->Draw();
        Menu_View_->Draw();
        Menu_Window_->Draw();
        Menu_Debug_->Draw();

    ImGui::EndMainMenuBar();
    }


}

// Deferred Update
void GUISystem::DeferredFrameUpdate() {


}


void GUISystem::UpdateFrame() {

    // Rendering
    ImGui::Render();

    // Draw The GUI
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}