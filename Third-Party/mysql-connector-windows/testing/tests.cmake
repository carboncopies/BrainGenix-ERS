# Copyright (c) 2020, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0, as
# published by the Free Software Foundation.
#
# This program is also distributed with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms,
# as designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an
# additional permission to link the program and your derivative works
# with the separately licensed software that they have included with
# MySQL.
#
# Without limiting anything contained in the foregoing, this file,
# which is part of MySQL Connector/C++, is also subject to the
# Universal FOSS Exception, version 1.0, a copy of which can be found at
# http://oss.oracle.com/licenses/universal-foss-exception.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA


# Note: This file is meant to be included from the main CMakeLists.txt.
# It defines tests for the build tree.
# =====================================================================

#
# Note: We must clear compile flags - the ones used to build the connector
# are not good for building client code that uses the connector.
#

set_property(
  DIRECTORY .
  PROPERTY COMPILE_DEFINITIONS ""
)

if(BUILD_STATIC)
  add_definitions(-DSTATIC_CONCPP)
endif()


# Auto-generated test targets

IF (WITH_TESTS)
  # Unit tests declared with ADD_NG_TEST() (see cdk/cmake/testing.cmake)
  ADD_TEST_TARGET()

  # Test for public headers declared with ADD_HEADERS()
  # (see cdk/cmake/headers.cmake)
  ADD_HEADERS_TEST()
ENDIF (WITH_TESTS)

#
# Sub-project test
# ----------------
#
# This test checks using Con/C++ build system as a sub-project in
# the main cmake project.
#

file(REMOVE_RECURSE ${PROJECT_BINARY_DIR}/sub_project_test)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/sub_project_test)

if(CMAKE_GENERATOR_PLATFORM)
  list(APPEND cmake_options -A ${CMAKE_GENERATOR_PLATFORM})
endif()

if(CMAKE_GENERATOR_TOOLSET)
  list(APPEND cmake_options -T ${CMAKE_GENERATOR_TOOLSET})
endif()

add_custom_target(sub_project_test
  COMMAND ${CMAKE_COMMAND} -E remove -f ${PROJECT_BINARY_DIR}/sub_project_test/CMakeCache.txt
  COMMAND ${CMAKE_COMMAND}
    -G "${CMAKE_GENERATOR}"
    ${cmake_options}
    -D CONCPP_CACHE=${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/testing/sub_project_test
  COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIGURATION>  --clean-first
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/sub_project_test
  VERBATIM
)

set_target_properties(sub_project_test PROPERTIES FOLDER "Tests")


#
# Linking test
# ------------
#
# This test compiles test application using internal installation of built
# connector. It is important to work with installed files because otherwise
# cmake does its magic to resolve missing dependencies when building test code.
# We don't want this to happen to make sure that test code can be built with
# connector library only, as we distribute it.
#
# Note: For this test to work on platforms which do not provide required
# dependencies (such as OpenSSL), connector build tree must be configured
# with BUNDLE_DEPENDENCIES option enabled
#
# Note: internal installation into <binary_dir>/install is done by directly
# executing cmake_install.cmake script which is generated by cmake.
#
# TODO: Also test dynamic linking (requires adopting test app project)
#

file(REMOVE_RECURSE ${PROJECT_BINARY_DIR}/link_test)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/link_test)

unset(jdbc_options)
if(WITH_JDBC)
  #message("-- BOOST_ROOT: ${BOOST_ROOT}")
  list(APPEND jdbc_options -DWITH_JDBC=ON)
endif()

add_custom_target(link_test
  COMMAND ${CMAKE_COMMAND} -E echo "==== Installing con/C++ ===="
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_BINARY_DIR}/install
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/install
  COMMAND ${CMAKE_COMMAND}
    -D CMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/install
    -D CMAKE_INSTALL_CONFIG_NAME=$<$<BOOL:$<CONFIGURATION>>:$<CONFIGURATION>>$<$<NOT:$<BOOL:$<CONFIGURATION>>>:Release>
    -P ${PROJECT_BINARY_DIR}/cmake_install.cmake
  COMMAND ${CMAKE_COMMAND} -E echo "==== Configuring test application build ===="
  COMMAND ${CMAKE_COMMAND} -E remove -f ${PROJECT_BINARY_DIR}/link_test/CMakeCache.txt
  COMMAND ${CMAKE_COMMAND}
    -G "${CMAKE_GENERATOR}"
    -D WITH_CONCPP=${PROJECT_BINARY_DIR}/install
    -D WITH_SSL="${WITH_SSL}"
    -D BUILD_STATIC=${BUILD_STATIC}
    -D STATIC_MSVCRT=${STATIC_MSVCRT}
    ${jdbc_options}
    ${PROJECT_SOURCE_DIR}/testapp
  COMMAND ${CMAKE_COMMAND} -E echo "==== Building test application ===="
  COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIGURATION>  --clean-first
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/link_test
)

set_target_properties(link_test PROPERTIES FOLDER "Tests")

add_dependencies(link_test connector)
if(WITH_JDBC)
  add_dependencies(link_test connector-jdbc)
endif()

# TDOD: Use ${CMAKE_COMMAND}, but evaluated at test time, not here.

add_test(NAME Link_test
  COMMAND cmake --build . --target link_test --config $<CONFIGURATION>
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
