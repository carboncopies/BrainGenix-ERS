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

namespace BrainGenix {
namespace ERS {
namespace Module {

TEST(ExternalModelLoaderTest, TestFindTextureBitmap) {
    BrainGenix::ERS::Module::ExternalModelLoader loader;  // Use an appropriate constructor
    std::vector<std::pair<std::string, FIBITMAP*>> LoadedTextures;
    // Populate the vector with some data...
    std::string TexturePath = "test_path";
    FIBITMAP* bitmap = loader.FindTextureBitmap(TexturePath, &LoadedTextures);
    // Add ASSERT or EXPECT commands to verify bitmap is as expected...
}

TEST(ExternalModelLoaderTest, TestDeleteTextureBitmap) {
    BrainGenix::ERS::Module::ExternalModelLoader loader;  // Use an appropriate constructor
    std::vector<std::pair<std::string, FIBITMAP*>> LoadedTextures;
    // Populate the vector with some data...
    std::string TexturePath = "test_path";
    loader.DeleteTextureBitmap(TexturePath, &LoadedTextures);
    // Add ASSERT or EXPECT commands to verify LoadedTextures does not contain TexturePath anymore...
}

TEST(ExternalModelLoaderTest, TestFindTextureMatches) {
    BrainGenix::ERS::Module::ExternalModelLoader loader;  // Use an appropriate constructor
    ERS_STRUCT_Mesh* Mesh;
    // Initialize Mesh with data...
    std::string Type1 = "type1";
    std::string Type2 = "type2";
    std::pair<std::string, std::string> matches = loader.FindTextureMatches(Mesh, Type1, Type2);
    // Add ASSERT or EXPECT commands to verify matches is as expected...
}

TEST(ExternalModelLoaderTest, TestDetectBoundingBox) {
    BrainGenix::ERS::Module::ExternalModelLoader loader;  // Use an appropriate constructor
    ERS_STRUCT_Model* Model;
    // Initialize Model with data...
    loader.DetectBoundingBox(Model);
    // Add ASSERT or EXPECT commands to verify the bounding box of Model is correctly computed...
}

}
}
} 