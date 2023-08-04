vcpkg_from_git(
  OUT_SOURCE_PATH SOURCE_PATH
  URL https://gitlab.braingenix.org/carboncopies/BrainGenix/ERS/IOSubsystem.git
  REF 1657851ff0582fd1527d96da4839dd20562788f0
  HEAD_REF main
)



vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        # -DOVERRIDE_INSTALL_DIR=OFF
        # -DBUILD_TESTS=OFF
)

vcpkg_fixup_pkgconfig()
vcpkg_cmake_install()
vcpkg_copy_pdbs()

# vcpkg_cmake_config_fixup(CONFIG_PATH "${CURRENT_PACKAGES_DIR}/CMake")
vcpkg_fixup_cmake_targets()

# Remove duplicate header/config files from debug install dir
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")


file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)