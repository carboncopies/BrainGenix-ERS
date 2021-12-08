//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for creating and managing 3d cursors.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-01
*/


#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>


// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>

#include <ImGuizmo.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <NoClip.h>
#include <ERS_STRUCT_LocRotScale.h>



enum class GizmoMode
{
    none,
    translate,
    rotate,
    scale
};




/**
 * @brief Setup 3D Cursors for the user to edit with
 * 
 */
class Cursors3D {

    private:


        float Matrix_[4][16] = { // Cube For Viewport Angle Identifier
            { 1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f },

            { 1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            2.f, 0.f, 0.f, 1.f },

            { 1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            2.f, 0.f, 2.f, 1.f },

            { 1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 2.f, 1.f }
        };



        bool IsCursorActive_; /**<Indicates If Cursor Active Or Disabled*/
        bool FirstFrame_ = true;
        float CameraDistance_;
        float* CameraView_;
        float* CameraProjection_;


        ERS_OBJECT_CAMERA_NOCLIP *Camera_;
        ImGuizmo::OPERATION CurrentGizmoOperation_ = ImGuizmo::TRANSLATE;


        ERS_STRUCT_LocRotScale CurrentPos_;
        ERS_STRUCT_LocRotScale LastPos_;
        bool HasObjectChanged_ = false;



    public:

        Cursors3D();
        ~Cursors3D();

        /**
         * @brief Called Every Frame To Update Cursor
         * 
         */
        void BeginRenderpass(ERS_OBJECT_CAMERA_NOCLIP *Camera, float* CameraView, float* CameraProjection, bool IsCameraMoving);

        /**
         * @brief Returns if camera input should be disabled (if user interacting with cursor)
         * 
         * @return true 
         * @return false 
         */
        bool DisableCameraMovement();

        /**
         * @brief Finish render pass
         * 
         */
        void EndRenderpass();

        /**
         * @brief returns if LocRotScale Has changed.
         * 
         * @return true 
         * @return false 
         */
        bool HasLocRotScaleChanged();

        /**
         * @brief Get the Loc Rot Scale object
         * 
         * @return ERS_STRUCT_LocRotScale 
         */
        ERS_STRUCT_LocRotScale GetLocRotScale();

        /**
         * @brief Get a pointer to the Loc Rot Scale object
         * 
         * @return ERS_STRUCT_LocRotScale* 
         */
        ERS_STRUCT_LocRotScale* GetLocRotScalePtr();

        /**
         * @brief Set the Loc Rot Scale object
         * 
         */
        void SetLocRotScale(ERS_STRUCT_LocRotScale);

        /**
         * @brief Check if two ERS_STRUCT_LocRotScale Objects are Equal.
         * 
         * @param LRS1 
         * @param LRS2 
         * @return true 
         * @return false 
         */
        bool IsLocRotScaleEqual(ERS_STRUCT_LocRotScale LRS1, ERS_STRUCT_LocRotScale LRS2);

};