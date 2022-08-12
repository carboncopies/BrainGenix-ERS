//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_YAMLHelpers.h>


bool ERS_FUNCTION_GetInt(YAML::Node Data, std::string Name, int &Target) {
    try {
        Target = Data[Name].as<int>();
        return true;
    } catch (YAML::TypedBadConversion<int>) {
        return false;
    } catch (YAML::KeyNotFound) {
        return false;
    }
}
bool ERS_FUNCTION_GetFloat(YAML::Node Data, std::string Name, float &Target) {
    try {
        Target = Data[Name].as<float>();
        return true;
    } catch (YAML::TypedBadConversion<float>) {
        return false;
    } catch (YAML::KeyNotFound) {
        return false;
    }
}
bool ERS_FUNCTION_GetBool(YAML::Node Data, std::string Name, bool &Target) {
    try {
        Target = Data[Name].as<bool>();
        return true;
    } catch (YAML::TypedBadConversion<bool>) {
        return false;
    } catch (YAML::KeyNotFound) {
        return false;
    }
}
bool ERS_FUNCTION_GetLong(YAML::Node Data, std::string Name, long &Target) {
    try {
        Target = Data[Name].as<long>();
        return true;
    } catch (YAML::TypedBadConversion<long>) {
        return false;
    } catch (YAML::KeyNotFound) {
        return false;
    }
}
bool ERS_FUNCTION_GetDouble(YAML::Node Data, std::string Name, double &Target) {
    try {
        Target = Data[Name].as<double>();
        return true;
    } catch (YAML::TypedBadConversion<double>) {
        return false;
    } catch (YAML::KeyNotFound) {
        return false;
    }
}