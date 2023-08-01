vcpkg_from_git(
  OUT_SOURCE_PATH SOURCE_PATH
  URL https://gitlab.braingenix.org/carboncopies/BrainGenix/ERS/IOSubsystem.git
  REF f48084d697c09535485510c90e891cf1880031cf
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