vcpkg_from_git(
  OUT_SOURCE_PATH SOURCE_PATH
  URL https://gitlab.braingenix.org/carboncopies/BrainGenix/ERS/IOSubsystem.git
  REF 5093e0ccf24a4d88b54ff3f841b5caaa824c48c7
  HEAD_REF main
)



vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        # -DBUILD_EXAMPLES=OFF
        # -DBUILD_TESTS=OFF
)
vcpkg_cmake_install()

# vcpkg_configure_cmake(
#   SOURCE_PATH "${SOURCE_PATH}"
#   PREFER_NINJA
# )
# vcpkg_install_cmake()
# vcpkg_fixup_cmake_targets()

# file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)