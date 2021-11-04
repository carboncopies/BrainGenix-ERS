//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#pragma once


class ERS_OBJECT_MODEL {


    private:

    public:

        // Model Data
        std::vector<ERS_OBJECT_MESH> Meshes;
        std::Vector<ERS_OBJECT_TEXTURE> Textures_Loaded;
        std::string Directory;
        bool GammaCorrection;

        // Load Model From File
        void LoadModelFromFile(std::string const &Path);

        // Draw Model
        void Draw(ERS_OBJECT_SHADER &Shader);



};
