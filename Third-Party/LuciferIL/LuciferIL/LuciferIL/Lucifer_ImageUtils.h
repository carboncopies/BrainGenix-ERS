//-----------------------//
// Lucifer Image Library //
// Thomas Liao (2022)    //
//-----------------------//

#pragma once


// Standard Libs
#include <iostream>
#include <memory>
#include <cstring>

// Third-Party Libs
#include <FreeImage.h>

// Internal Libs
#include <LuciferIL/Lucifer_WritingStatusEnum.h>
#include <LuciferIL/Lucifer_ImageFormatEnum.h>
#include <LuciferIL/Lucifer_ImageStruct.h>


namespace Lucifer {

/**
 * @brief Returns the number of bits per pixel for the given image
 * 
 * @param Image Lucifer image struct
 * @return int Number of bits per pixel
 */
int Lucifer_GetBitsPerPixel(Image &Image);

/**
 * @brief Copies the image into a new FIBITMAP.
 * You'll need to take care of destroying the returned image manually.
 * 
 * @param Image 
 * @return FIBITMAP* 
 */
FIBITMAP* Lucifer_CreateFIBitmapFromImage(Image &Image);

};