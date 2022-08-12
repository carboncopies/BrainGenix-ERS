//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_YAMLHelpers.h>

// Standart Type Helper Functions
bool ERS_FUNCTION_GetInt(YAML::Node Data, std::string Name, int &Target) {
    try {
        Target = Data[Name].as<int>();
        return true;
    } catch (YAML::TypedBadConversion<int>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetFloat(YAML::Node Data, std::string Name, float &Target) {
    try {
        Target = Data[Name].as<float>();
        return true;
    } catch (YAML::TypedBadConversion<float>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetBool(YAML::Node Data, std::string Name, bool &Target) {
    try {
        Target = Data[Name].as<bool>();
        return true;
    } catch (YAML::TypedBadConversion<bool>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetLong(YAML::Node Data, std::string Name, long &Target) {
    try {
        Target = Data[Name].as<long>();
        return true;
    } catch (YAML::TypedBadConversion<long>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetDouble(YAML::Node Data, std::string Name, double &Target) {
    try {
        Target = Data[Name].as<double>();
        return true;
    } catch (YAML::TypedBadConversion<double>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetUnsignedInt(YAML::Node Data, std::string Name, unsigned int &Target) {
    try {
        Target = Data[Name].as<unsigned int>();
        return true;
    } catch (YAML::TypedBadConversion<unsigned int>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetBool(YAML::Node Data, std::string Name, unsigned long &Target) {
    try {
        Target = Data[Name].as<unsigned long>();
        return true;
    } catch (YAML::TypedBadConversion<unsigned long>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetLongLong(YAML::Node Data, std::string Name, long long &Target) {
    try {
        Target = Data[Name].as<long long>();
        return true;
    } catch (YAML::TypedBadConversion<long long>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetUnsignedLongLong(YAML::Node Data, std::string Name, unsigned long long &Target) {
    try {
        Target = Data[Name].as<unsigned long long>();
        return true;
    } catch (YAML::TypedBadConversion<unsigned long long>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetString(YAML::Node Data, std::string Name, std::string &Target) {
    try {
        Target = Data[Name].as<std::string>();
        return true;
    } catch (YAML::TypedBadConversion<std::string>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetNode(YAML::Node Data, std::string Name, YAML::Node &Target) {
    try {
        Target = Data[Name];
        return true;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}


// Vector Helpers
bool ERS_FUNCTION_GetStringVector(YAML::Node Data, std::string Name, std::vector<std::string> &Target) {
    try {
        YAML::Node TargetNode = Data[Name];
        for (YAML::const_iterator it=TargetNode.begin(); it!=TargetNode.end(); ++it) {
            Target.push_back(it->second.as<std::string>());
        }
        return true;
    } catch (YAML::TypedBadConversion<std::string>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetIntVector(YAML::Node Data, std::string Name, std::vector<int> &Target) {
    try {
        YAML::Node TargetNode = Data[Name];
        for (YAML::const_iterator it=TargetNode.begin(); it!=TargetNode.end(); ++it) {
            Target.push_back(it->second.as<int>());
        }
        return true;
    } catch (YAML::TypedBadConversion<int>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetLongVector(YAML::Node Data, std::string Name, std::vector<long> &Target) {
    try {
        YAML::Node TargetNode = Data[Name];
        for (YAML::const_iterator it=TargetNode.begin(); it!=TargetNode.end(); ++it) {
            Target.push_back(it->second.as<long>());
        }
        return true;
    } catch (YAML::TypedBadConversion<long>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
bool ERS_FUNCTION_GetNodeVector(YAML::Node Data, std::string Name, std::vector<YAML::Node> &Target) {
    try {
        YAML::Node TargetNode = Data[Name];
        for (YAML::const_iterator it=TargetNode.begin(); it!=TargetNode.end(); ++it) {
            Target.push_back(it->second);
        }
        return true;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}


// GLM Helper Functions
bool ERS_FUNCTION_GetVec3(YAML::Node Data, std::string NameBase, glm::vec3 &Target) {
    try {
        float X = Data[NameBase + "X"].as<float>();
        float Y = Data[NameBase + "Y"].as<float>();
        float Z = Data[NameBase + "Z"].as<float>();
        Target = glm::vec3(X,Y,Z);
        return true;
    } catch (YAML::TypedBadConversion<float>&) {
        return false;
    } catch (YAML::KeyNotFound&) {
        return false;
    }
}
