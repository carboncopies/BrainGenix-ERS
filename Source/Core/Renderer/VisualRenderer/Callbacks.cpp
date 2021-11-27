// //======================================================================//
// // This file is part of the BrainGenix-ERS Environment Rendering System //
// //======================================================================//

// /*
//     Description: This file contains the visual renderer callback functions.
//     Documentation Status: Done
//     Additonal Notes: None
//     Date Created: 2021-11-16
// */

// #include "Callbacks.h"


// void FramebufferSizeCallback(GLFWwindow* /*Window*/, int Width, int Height) {

//     // Update Viewport
//     glViewport(0, 0, Width, Height);
//     glScissor(0, 0, Width, Height);

// }


// void MouseCallback(GLFWwindow* /*Window*/, double XPos, double YPos) {

//     // Update Positions
//     if (FirstMouse) {

//         LastX = XPos;
//         LastY = YPos;

//         FirstMouse = false;

//     }

//     // Calculate Offsets
//     float XOffset = XPos - LastX;
//     float YOffset = YPos - LastY;

//     // Update Last Positions
//     LastX = XPos;
//     LastY = YPos;

//     // Process Camera Movement
//     Camera_.ProcessMouseMovement(XOffset, YOffset);

// }



// void ScrollCallback(GLFWwindow* /*Window*/, double /*XOffset*/, double YOffset) {

//     Camera_.ProcessMouseScroll(YOffset);

// }
