# set msvc compiler
set (CMAKE_C_COMPILER cl.exe)
set (CMAKE_CXX_COMPILER cl.exe)

# configure vcpkg
include ("c:/work/repos/public/vcpkg/scripts/buildsystems/vcpkg.cmake")
set (VCPKG_OVERLAY_TRIPLETS c:/work/repos/matterfi/VcpkgPortProject/triplets)
set (VCPKG_FEATURE_FLAGS "registries,manifest")
