##########################
# Builds Library For ERS #
##########################


include(ExternalProject)



ERSBuildLogger(${Green} "Configuring Boost Library")

#---------------------------------------------------------------------------
# Get and build boost

set( Boost_Bootstrap_Command )

# Note: It IS important to download different files on different OS's:
# on Unix-like systems, we need the file persmissions (only available in the .tar.gz),
# while on Windows, we need CR/LF line feeds (only available in the .zip)

if( UNIX )
  set( Boost_url "http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz")
  set( Boost_md5 51528a0e3b33d9e10aaa311d9eb451e3 )
  set( Boost_Bootstrap_Command ./bootstrap.sh )
  set( Boost_b2_Command ./b2 )
else()
  if( WIN32 )
    set( Boost_url "http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.zip")
    set( Boost_md5 08d29a2d85db3ebc8c6fdfa3a1f2b83c )
    set( Boost_Bootstrap_Command cmd /C bootstrap.bat msvc )
    set( Boost_b2_Command b2.exe )
  endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(Boost_address_model 64)
else()
  set(Boost_address_model 32)
endif()

if (MSVC_VERSION EQUAL 1500) #VS2008
set(boost_toolset "--toolset=msvc-9.0")
elseif(MSVC_VERSION EQUAL 1600) #VS2010
set(boost_toolset "--toolset=msvc-10.0")
elseif(MSVC_VERSION EQUAL 1700) #VS2012
set(boost_toolset "--toolset=msvc-11.0")
elseif(MSVC_VERSION EQUAL 1800) #VS2013
set(boost_toolset "--toolset=msvc-12.0")
elseif(MSVC_VERSION EQUAL 1900) #VS2015
set(boost_toolset "--toolset=msvc-14.0")
endif(MSVC_VERSION EQUAL 1500)


if(${BUILD_SHARED_LIBS} MATCHES OFF)
  set(BUILD_LIBS "static")
elseif(${BUILD_SHARED_LIBS} MATCHES ON)
  set(BUILD_LIBS "shared")
endif()

set(INSTALL_DEPENDENCIES_DIR ${BIN_DIR}/ThirdParty/Boost)

ExternalProject_Add(Boost
    BUILD_IN_SOURCE 1
    SOURCE_DIR ${LIB_DIR}/boost
#     BINARY_DIR ${BIN_DIR}/boost
#   URL ${Boost_url}
#   URL_MD5 ${Boost_md5}


    # Show Output To Terminal
    LOG_DOWNLOAD TRUE
    LOG_UPDATE TRUE
    LOG_PATCH TRUE
    LOG_CONFIGURE TRUE
    LOG_BUILD TRUE
    LOG_INSTALL TRUE
    LOG_TEST TRUE
    LOG_MERGED_STDOUTERR TRUE

    USES_TERMINAL_DOWNLOAD TRUE
    USES_TERMINAL_UPDATE TRUE
    USES_TERMINAL_PATCH TRUE
    USES_TERMINAL_CONFIGURE TRUE
    USES_TERMINAL_BUILD TRUE
    USES_TERMINAL_INSTALL TRUE
    USES_TERMINAL_TEST TRUE

    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ${Boost_Bootstrap_Command} --prefix=${INSTALL_DEPENDENCIES_DIR}/lib
    BUILD_COMMAND ${Boost_b2_Command} install -j8 --prefix=${INSTALL_DEPENDENCIES_DIR} --with-thread --with-filesystem --with-system --with-date_time --with-program_options  --with-atomic  address-model=${Boost_address_model} link=static,shared ${boost_toolset}
    INSTALL_COMMAND ""
)

if( WIN32 )
  set( Boost_INCLUDE_DIR ${INSTALL_DEPENDENCIES_DIR}/include/boost-1_59 )
  set( BOOST_ROOT ${INSTALL_DEPENDENCIES_DIR} )
else()
  set( Boost_INCLUDE_DIR ${INSTALL_DEPENDENCIES_DIR}/include )
endif()

set( Boost_LIBRARY_DIR ${INSTALL_DEPENDENCIES_DIR}/lib )


message(STATUS "Set Boost Include Directory To '${Boost_INCLUDE_DIR}'")
message(STATUS "Set Boost Library Directory To '${Boost_LIBRARY_DIR}'")


# set(BOOST_LIBS_TO_BUILD
# 	# chrono
# 	# context
# 	date_time
# 	# exception
# 	filesystem
# 	# graph
# 	# graph_parallel
# 	# iostreams
# 	# locale
# 	# math
# 	# mpi
# 	# program_options
# 	# python
# 	# random
# 	# regex
# 	# serialization
# 	# signals
# 	system
# 	# test
# 	# thread
# 	# timer
# 	# wave
# )

# if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
#     set(COMPILER_IS_CLANG TRUE)
# elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
#     set(COMPILER_IS_GCC TRUE)
# elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
#     set(COMPILER_IS_INTEL TRUE)
# elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
#     set(COMPILER_IS_MSVC TRUE)
# endif() # CMAKE_CXX_COMPILER_ID

# # Set boost toolset
# if(MSVC11)
# 	set(BOOST_TOOLSET msvc-11.0)
# elseif(MSVC12)
# 	set(BOOST_TOOLSET msvc-12.0)
# elseif(MSVC14)
# 	set(BOOST_TOOLSET msvc-14.0)
# elseif(APPLE)
# 	set(BOOST_TOOLSET darwin)
# elseif(COMPILER_IS_CLANG)
# 	set(BOOST_TOOLSET clang)
# elseif(COMPILER_IS_INTEL)
# 	# Extracts first two version numbers, e.g. 13.0 from 13.0.0.20121010
# 	string(REGEX MATCH ^[0-9]*.[0-9] INTEL_COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
# 	set(BOOST_TOOLSET intel-${INTEL_COMPILER_VERSION})
# elseif(COMPILER_IS_GCC)
# 	set(BOOST_TOOLSET gcc)
# endif()

# # Prefix with --with- for bjam (b2) build command
# foreach(LIB_TO_BUILD ${BOOST_LIBS_TO_BUILD})
# 	set(BOOST_LIBS_TO_BUILD_CMD ${BOOST_LIBS_TO_BUILD_CMD} --with-${LIB_TO_BUILD})
# endforeach()

# # Prefix with boost_ for library names
# foreach(LIB_TO_BUILD ${BOOST_LIBS_TO_BUILD})
# 	set(BOOST_LIBS_TO_BUILD_NAMES ${BOOST_LIBS_TO_BUILD_NAMES} boost_${LIB_TO_BUILD})
# endforeach()

# # Set update command
# if(WIN32)
# 	set(BOOST_UPDATE_COMMAND bootstrap.bat)
# else()
# 	set(BOOST_UPDATE_COMMAND ./bootstrap.sh)
# endif()

# # Set additional config options
# set(BOOST_CONFIG_OPTIONS "")
# if(WIN32)
# 	if(HAVE_64_BIT)
# 		set(BOOST_CONFIG_OPTIONS "architecture=x86;address-model=64")
# 	endif()
# endif()

# include(ProcessorCount)
# ProcessorCount(N)

# ExternalProject_Add(boost

#     # Specify Directory Configuration Options
#     SOURCE_DIR ${LIB_DIR}/boost
#     BINARY_DIR ${BIN_DIR}/boost
    
#     # Show Output To Terminal
#     LOG_DOWNLOAD TRUE
#     LOG_UPDATE TRUE
#     LOG_PATCH TRUE
#     LOG_CONFIGURE TRUE
#     LOG_BUILD TRUE
#     LOG_INSTALL TRUE
#     LOG_TEST TRUE
#     LOG_MERGED_STDOUTERR TRUE

#     USES_TERMINAL_DOWNLOAD TRUE
#     USES_TERMINAL_UPDATE TRUE
#     USES_TERMINAL_PATCH TRUE
#     USES_TERMINAL_CONFIGURE TRUE
#     USES_TERMINAL_BUILD TRUE
#     USES_TERMINAL_INSTALL TRUE
#     USES_TERMINAL_TEST TRUE

#     # Set Configuation Commands
# 	UPDATE_COMMAND "${BOOST_UPDATE_COMMAND}"
# 	CONFIGURE_COMMAND ""
# 	BUILD_COMMAND ./b2 ${BOOST_LIBS_TO_BUILD_CMD} -j ${N} ${NUM_PROCESSORS} toolset=${BOOST_TOOLSET} link=static stage ${BOOST_CONFIG_OPTIONS}
# 	INSTALL_COMMAND ""
# )
# ExternalProject_Get_Property( boost binary_dir )
# set(boost_BINARY_DIR ${binary_dir} CACHE PATH "" FORCE)


# include_directories(${Boost_INCLUDE_DIRS})


ERSBuildLogger(${BoldGreen} "Finished Configuring Boost Library")