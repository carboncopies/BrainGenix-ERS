//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// cppcheck-suppress missingIncludeSystem
#include <GUI_Menu_Layout.h>


GUI_Menu_Layout::GUI_Menu_Layout(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_LayoutManager* LayoutManager) {

    SystemUtils_ = SystemUtils;
    LayoutManager_ = LayoutManager;
    SystemUtils_->Logger_->Log("Editor Setting Up Layout Menu", 4);

}


GUI_Menu_Layout::~GUI_Menu_Layout() {

    SystemUtils_->Logger_->Log("Editor Destroying Layout Menu", 4);

}


void GUI_Menu_Layout::EnsureLayoutsLoaded() {

    if (!LayoutsLoaded_) {
        LayoutManager_->LoadLayouts();
        LayoutsLoaded_ = true;
    }
}


void GUI_Menu_Layout::DrawSaveLayoutPopup() {

    if (ImGui::BeginPopupModal("Save Layout Preset", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputTextWithHint("Layout Name", "Preset Name", LayoutNameBuffer_, IM_ARRAYSIZE(LayoutNameBuffer_));

        if (ImGui::Button("Save", ImVec2(120, 0)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter))) {
            LayoutManager_->CreateLayout(LayoutNameBuffer_);
            LayoutsLoaded_ = true;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
            ImGui::CloseCurrentPopup();
        }

    ImGui::EndPopup();
    }
}


void GUI_Menu_Layout::Draw() {

    EnsureLayoutsLoaded();

    if (ImGui::BeginMenu("Layout")) {

        if (ImGui::BeginMenu("Apply Preset")) {
            std::vector<std::string> LayoutNames = LayoutManager_->GetLayoutNames();
            std::string ActiveLayoutName = LayoutManager_->GetActiveLayoutName();

            if (LayoutNames.size() == 0) {
                ImGui::MenuItem("No Layouts Found", "", false, false);
            }

            for (unsigned long i = 0; i < LayoutNames.size(); i++) {
                bool Selected = LayoutNames[i] == ActiveLayoutName;
                if (ImGui::MenuItem(LayoutNames[i].c_str(), "", Selected)) {
                    LayoutManager_->ApplyLayout((int)i);
                }
            }

        ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Save Current Layout...")) {
            ImGui::OpenPopup("Save Layout Preset");
        }

        if (ImGui::MenuItem("Reload Layouts")) {
            LayoutManager_->LoadLayouts();
            LayoutsLoaded_ = true;
        }

    ImGui::EndMenu();
    }

    DrawSaveLayoutPopup();

}
