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

        bool IsCursorActive_; /**<Indicates If Cursor Active Or Disabled*/







void Frustum(float left, float right, float bottom, float top, float znear, float zfar, float* m16)
{
   float temp, temp2, temp3, temp4;
   temp = 2.0f * znear;
   temp2 = right - left;
   temp3 = top - bottom;
   temp4 = zfar - znear;
   m16[0] = temp / temp2;
   m16[1] = 0.0;
   m16[2] = 0.0;
   m16[3] = 0.0;
   m16[4] = 0.0;
   m16[5] = temp / temp3;
   m16[6] = 0.0;
   m16[7] = 0.0;
   m16[8] = (right + left) / temp2;
   m16[9] = (top + bottom) / temp3;
   m16[10] = (-zfar - znear) / temp4;
   m16[11] = -1.0f;
   m16[12] = 0.0;
   m16[13] = 0.0;
   m16[14] = (-temp * zfar) / temp4;
   m16[15] = 0.0;
}

void Perspective(float fovyInDegrees, float aspectRatio, float znear, float zfar, float* m16)
{
   float ymax, xmax;
   ymax = znear * tanf(fovyInDegrees * 3.141592f / 180.0f);
   xmax = ymax * aspectRatio;
   Frustum(-xmax, xmax, -ymax, ymax, znear, zfar, m16);
}

void Cross(const float* a, const float* b, float* r)
{
   r[0] = a[1] * b[2] - a[2] * b[1];
   r[1] = a[2] * b[0] - a[0] * b[2];
   r[2] = a[0] * b[1] - a[1] * b[0];
}

float Dot(const float* a, const float* b)
{
   return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void Normalize(const float* a, float* r)
{
   float il = 1.f / (sqrtf(Dot(a, a)) + FLT_EPSILON);
   r[0] = a[0] * il;
   r[1] = a[1] * il;
   r[2] = a[2] * il;
}

void LookAt(const float* eye, const float* at, const float* up, float* m16)
{
   float X[3], Y[3], Z[3], tmp[3];

   tmp[0] = eye[0] - at[0];
   tmp[1] = eye[1] - at[1];
   tmp[2] = eye[2] - at[2];
   Normalize(tmp, Z);
   Normalize(up, Y);

   Cross(Y, Z, tmp);
   Normalize(tmp, X);

   Cross(Z, X, tmp);
   Normalize(tmp, Y);

   m16[0] = X[0];
   m16[1] = Y[0];
   m16[2] = Z[0];
   m16[3] = 0.0f;
   m16[4] = X[1];
   m16[5] = Y[1];
   m16[6] = Z[1];
   m16[7] = 0.0f;
   m16[8] = X[2];
   m16[9] = Y[2];
   m16[10] = Z[2];
   m16[11] = 0.0f;
   m16[12] = -Dot(X, eye);
   m16[13] = -Dot(Y, eye);
   m16[14] = -Dot(Z, eye);
   m16[15] = 1.0f;
}

void OrthoGraphic(const float l, float r, float b, const float t, float zn, const float zf, float* m16)
{
   m16[0] = 2 / (r - l);
   m16[1] = 0.0f;
   m16[2] = 0.0f;
   m16[3] = 0.0f;
   m16[4] = 0.0f;
   m16[5] = 2 / (t - b);
   m16[6] = 0.0f;
   m16[7] = 0.0f;
   m16[8] = 0.0f;
   m16[9] = 0.0f;
   m16[10] = 1.0f / (zf - zn);
   m16[11] = 0.0f;
   m16[12] = (l + r) / (l - r);
   m16[13] = (t + b) / (b - t);
   m16[14] = zn / (zn - zf);
   m16[15] = 1.0f;
}

inline void rotationY(const float angle, float* m16)
{
   float c = cosf(angle);
   float s = sinf(angle);

   m16[0] = c;
   m16[1] = 0.0f;
   m16[2] = -s;
   m16[3] = 0.0f;
   m16[4] = 0.0f;
   m16[5] = 1.f;
   m16[6] = 0.0f;
   m16[7] = 0.0f;
   m16[8] = s;
   m16[9] = 0.0f;
   m16[10] = c;
   m16[11] = 0.0f;
   m16[12] = 0.f;
   m16[13] = 0.f;
   m16[14] = 0.f;
   m16[15] = 1.0f;
}











        float CameraDistance_;
        int gizmoCount = 1;

        float* CameraView_;
        float* CameraProjection_;
        float* Matrix_;


        float objectMatrix[4][16] = {
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

        const float identityMatrix[16] =
        { 1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f };






        ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;


      ERS_OBJECT_CAMERA_NOCLIP *Camera_;


    public:

        Cursors3D();
        ~Cursors3D();

        /**
         * @brief Called Every Frame To Update Cursor
         * 
         */
        void BeginRenderpass(ERS_OBJECT_CAMERA_NOCLIP *Camera, float AspectRatio);

        /**
         * @brief Returns if camera input should be disabled (if user interacting with cursor)
         * 
         * @return true 
         * @return false 
         */
        bool DisableCameraMovement();


        void EndRenderpass();

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