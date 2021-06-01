//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is used to instantiate the Visual Rendering Pipleine Class within one function.
    Additonal Notes: None
    Date Created: 2021-06-01
*/  


#include "Core/Rendering/Visual/VisualRenderingMainModule/VisualRenderingMainModule.cpp"



// Defines Function That Initializes The Visual Rendering Pipeline //
int InstantiateVisualRenderingPipeline() {


    VisualRenderingPipeline ERSInstance;

    try {
        ERSInstance.InitializeConfiguration();

    } catch (const std::exception& e) {
        
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}