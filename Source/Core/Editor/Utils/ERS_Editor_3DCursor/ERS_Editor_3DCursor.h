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
#include <glm/gtx/matrix_decompose.hpp>

#include <imgui.h>

#include <ImGuizmo.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_Camera.h>
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


        float Matrix_[4][16] = { /**<Cube For Viewport Angle Identifier*/
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
        float* CameraView_; /**<Camera View Matrix, Converted From GLM::Mat4*/
        float* CameraProjection_; /**<Camera Projection Matrix, Converted From GLM::Mat4*/

        std::shared_ptr<ERS_STRUCT_Camera> Camera_; /**<Camera Object Pointer*/
        ImGuizmo::OPERATION CurrentGizmoOperation_ = ImGuizmo::TRANSLATE; /**<Set Current Cursor Operation*/

        bool HasObjectChanged_ = false; /*<Indicate If Update Needed*/

    public:

        glm::vec3 Pos_;
        glm::vec3 Rot_;
        glm::vec3 Scale_;

    public:

        /**
         * @brief Construct a new Cursors 3 D object
         * 
         */
        Cursors3D();

        /**
         * @brief Destroy the Cursors 3 D object
         * 
         */
        ~Cursors3D();


        /**
         * @brief Returns if the gizmo is being used
         * 
         * @return true 
         * @return false 
         */
        bool IsUsing();

        /**
         * @brief Returns if the gizmo is being hovered by the mouse
         * 
         * @return true 
         * @return false 
         */
        bool IsHovered();


        /**
         * @brief Draw the gizmo
         * 
         * @param Camera 
         * @param IsCameraMoving 
         */
        void Draw(std::shared_ptr<ERS_STRUCT_Camera> Camera, bool IsCameraMoving);




        /**
         * @brief Set the Loc Rot Scale object, accepts three glm::vec3 arrays indicating position, rotation and scale (in that order).
         * 
         * @param Pos 
         * @param Rot 
         * @param Scale 
         */
        void SetLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale);


};