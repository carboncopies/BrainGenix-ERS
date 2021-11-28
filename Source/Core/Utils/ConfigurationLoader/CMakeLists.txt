########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(ConfigurationLoader_Sources
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(ConfigurationLoader_Headers
    "LocalConfigurationLoader.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(ConfigurationLoader ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(ConfigurationLoader 
    yaml-cpp
    )
target_include_directories(ConfigurationLoader PUBLIC ./)

