# Create Library (Name Should Be Parent Dir Name)
add_library(WhereAmI

            # Add Source Files (.cpp)
            "src/whereami.c"

            # Add Header Files (.h)
            "src/whereami.h"
            
            ${BACKWARD_ENABLE}
            )

set_source_files_properties("src/whereami.c" PROPERTIES LANGUAGE C)
set_source_files_properties("src/whereami.h" PROPERTIES LANGUAGE C)
# set_property(TARGET WhereAmI PROPERTY CXX_STANDARD 17)

# Link 3rd Party Libs
target_link_libraries(WhereAmI
    )

# Link Internal Libs
target_link_libraries(WhereAmI
    )
target_include_directories(WhereAmI PUBLIC ./src)
target_include_directories(WhereAmI PUBLIC ./)
