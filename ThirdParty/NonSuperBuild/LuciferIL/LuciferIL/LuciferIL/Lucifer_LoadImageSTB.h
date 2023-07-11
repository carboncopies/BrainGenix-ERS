//-----------------------//
// Lucifer Image Library //
// Thomas Liao (2022)    //
//-----------------------//

#pragma once


// Standard Libs
#include <iostream>
#include <string.h>
#include <cstring>


// External Libs
#include <stb_image.h>

// Internal Libs
#include <LuciferIL/Lucifer_LoadingStatusEnum.h>
#include <LuciferIL/Lucifer_ImageStruct.h>


namespace Lucifer {


/**
 * @brief Decodes image data in-memory.
 * 
 * @param ImageData Pointer to raw bytes (these could be read directly off of the disk)
 * @param Size Size of the array
 * @param Image Reference to the image to be updated
 * @param MaxChannels Maximum number of supported channels, defaults to 4
 * @return Lucifer::LoadingStatus Status of loading
 */
LoadingStatus Lucifer_LoadSTB(unsigned char* ImageData, unsigned long Size, Image& Image, int MaxChannels = 4);





}