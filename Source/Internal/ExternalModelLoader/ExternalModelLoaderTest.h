//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <future>
#include <thread>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <FreeImage.h>

#include <LuciferIL/Lucifer.h>
#include <LuciferIL/Lucifer_ImageUtils.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Exceptional.h>

#include <ghc/filesystem.hpp>


// Internal Libraries (BG convention: use <> instead of "")
#include <Mesh.h>
#include <Texture.h>
#include <Vertex.h>
#include <Model.h>
#include <ModelWriterData.h>

#include <SystemUtils.h>
#include <IOData.h>
