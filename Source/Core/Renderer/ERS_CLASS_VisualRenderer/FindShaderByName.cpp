//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <set>

#include <FindShaderByName.h>


unsigned int ERS_FUNCTION_FindShaderByName(std::string Name, std::vector<std::unique_ptr<ERS_STRUCT_Shader>>* Shaders, BG::Common::Logger::LoggingSystem* Logger) {

    long Index = -1;
    for (unsigned long i = 0; i < Shaders->size(); i++) {
        if ((*Shaders)[i]->InternalName == Name) {
            Index = i;
            break;
        }
    }

    // Shader missing: fall back to index 0, but report it (once per distinct
    // name, as this is called every frame by VisualRenderer::UpdateViewports).
    if (Index == -1) {
        Index = 0;
        static std::set<std::string> ReportedNames;
        if ((Logger != nullptr) && (ReportedNames.count(Name) == 0)) {
            ReportedNames.insert(Name);
            Logger->Log(std::string("Required Shader '") + Name + "' Not Found In Project, Falling Back To Shader Index 0", 8);
        }
    }

    return Index;

}