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


        void EndRenderpass();
        bool HasLocRotScaleChanged();


        ERS_STRUCT_LocRotScale GetLocRotScale();
        ERS_STRUCT_LocRotScale* GetLocRotScalePtr();


};




// // The gizmo tool is active if the tool is selected (the mouse is pressed and near the tool).
// // Use this to prevent e.g. the camera from moving when dragging the gizmo.
// bool gizmo_is_active();

// void gizmo_manipulate(GizmoMode mode, Transform& transform, const Mat4f& camera_matrix) {


//     // gives mouse pixel coordinates in the [-1, 1] range
//     Vec2f n = platform().mouse.normalized_coordinates();

//     Vec4f ray_start, ray_end;
//     Mat4f view_proj_inverse = inverse(camera_matrix);

//     ray_start = view_proj_inverse * Vec4f(n.x, n.y, 0.f, 1.f);
//     ray_start *= 1.f / ray_start.w;

//     ray_end = view_proj_inverse * Vec4f(n.x, n.y, 1.f, 1.f);
//     ray_end *= 1.f / ray_end.w;

//     context.camera_ray.origin = (Vec3f&)ray_start;
//     context.camera_ray.direction = (Vec3f&)normalize(ray_end - ray_start);

//     context.camera_ray.t = FLT_MAX;

// }


// float closest_distance_between_lines(Rayf& l1, Rayf& l2)
// {
//     const Vec3f dp = l2.origin - l1.origin;
//     const float v12 = dot(l1.direction, l1.direction);
//     const float v22 = dot(l2.direction, l2.direction);
//     const float v1v2 = dot(l1.direction, l2.direction);

//     const float det = v1v2 * v1v2 - v12 * v22;

//     if (std::abs(det) > FLT_MIN)
//     {
//         const float inv_det = 1.f / det;

//         const float dpv1 = dot(dp, l1.direction);
//         const float dpv2 = dot(dp, l2.direction);

//         l1.t = inv_det * (v22 * dpv1 - v1v2 * dpv2);
//         l2.t = inv_det * (v1v2 * dpv1 - v12 * dpv2);

//         return norm(dp + l2.direction * l2.t - l1.direction * l1.t);
//     }
//     else
//     {
//         const Vec3f a = cross(dp, l1.direction);
//         return std::sqrt(dot(a, a) / v12);
//     }
// }


// float closest_distance_line_circle(const Ray& line, const Circle& c, Vec3f& point)
// {
//     plane f = make_plane(c.orientation, c.center);
//     ray r = line;

//     if (intersect_ray_plane(f, r))
//     {
//         // get the ray's intersection point on the plane which
//         // contains the circle
//         const Vec3f on_plane = r.origin + r.t * r.direction;
//         // project that point on to the circle's circumference
//         point = c.center + c.radius * normalize(on_plane - c.center);
//         return norm(on_plane - point);
//     }
//     else
//     {
//         // the required point on the circle is the one closest to the camera origin
//         point = c.radius * normalize(reject(context.camera_ray.origin - c.center, c.orientation));

//         return distance_between_point_ray(point, context.camera_ray);
//     }
// }

// void draw_translation_gizmo(const Transform& transform)
// {
//     for (int i = axis_x; i < axis_count; i++)
//     {
//         Vec3f axis_end = Vec3f(0.f, 0.f, 0.f);
//         axis_end[i] = 1.f;

//         vec3f axis_color = Vec3f(0.f, 0.f, 0.f);
//         axis_color[i] = 1.f;

//         if (i == context.selected_axis)
//         {
//             axis_color = Vec3f(1.f, 0.65f, 0.f);
//         }

//         debug_draw_add_line(transform.position, axis_end + transform.position, axis_color);
//     }
// }