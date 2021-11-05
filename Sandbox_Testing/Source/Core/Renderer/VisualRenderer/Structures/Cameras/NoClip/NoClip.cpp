//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the Noclip Camera.
    Additonal Notes: None
    Date Created: 2021-11-05
*/

void ERS_OBJECT_CAMERA_NOCLIP::ProcessMouseScroll(float YOffset) {

    // Update Zoom
    Zoom -= (float)YOffset;

    // Bound Zoom
    if (Zoom < MinZoom)
        Zoom = MinZoom;
    if (Zoom > MaxZoom)
        Zoom = MaxZoom;

    // Update Vectors
    UpdateCameraVectors();


}

void ERS_OBJECT_CAMERA_NOCLIP::UpdateCameraVectors() {
    
    // Calculate New Front Vector
    glm::vec3 NewFront;
    NewFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    NewFront.y = sin(glm::radians(Pitch));
    NewFromt.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(NewFront);

    // Calculate Right, Up Vector
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

}