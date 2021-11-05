//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the Noclip camera.
    Additonal Notes: None
    Date Created: 2021-11-05
*/

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


// Define Camera Directions
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


// Setup Camera Options
class Camera {

    public:

    private:


};



#include "Core/VisualRenderer/Structures/Cameras/NoClip.cpp"