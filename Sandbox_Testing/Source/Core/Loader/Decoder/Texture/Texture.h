//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file Loads Textures.
    Additonal Notes: None
    Date Created: 2021-11-04
*/  


#pragma once

#include <string>


unsigned int TextureFromFile(const char *Path, const std::string &Directory, bool Gamma = false);


#include "Core/Loader/Decoder/Texture/Texture.cpp"