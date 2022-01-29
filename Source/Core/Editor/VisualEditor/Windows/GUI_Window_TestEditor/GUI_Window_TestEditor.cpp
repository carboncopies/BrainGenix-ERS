//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_TestEditor.h>


// Constructor
Window_TestEditor::Window_TestEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing Demo Zep Editor Window", 4);

}

// Destructor
Window_TestEditor::~Window_TestEditor() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("Zep Editor Window Destructor Called", 6);

}


// Draw Function
void Window_TestEditor::Draw() {

    if (Enabled_) {
    bool Visible = ImGui::Begin("System Log", &Enabled_);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);


        if (Visible) {

            ImGui::Text("Testing!");

        }

    ImGui::End();
    }

}