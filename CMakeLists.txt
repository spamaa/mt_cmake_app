# CMakeList.txt : CMake project for CMakeApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)


# this must be set if you want to compile direct from vstudio
#set(CMAKE_TOOLCHAIN_FILE c:/work/repos/public/vcpkg/scripts/buildsystems/vcpkg.cmake)
#set(VCPKG_TARGET_TRIPLET x64-windows-static)
#set(VCPKG_OVERLAY_TRIPLETS c:/work/repos/matterfi/VcpkgPortProject/triplets)
#set(VCPKG_FEATURE_FLAGS "registries,manifest")

project ("CMakeApp")

message (STATUS "!!!!== CMAKE_TOOLCHAIN_FILE: '${CMAKE_TOOLCHAIN_FILE}' ==!!!!")
message (STATUS "!!!!== CMAKE_MODULE_PATH: '${CMAKE_MODULE_PATH}' ==!!!!")
message (STATUS "!!!!== CMAKE_PREFIX_PATH: '${CMAKE_PREFIX_PATH}' ==!!!!")
message (STATUS "!!!!== VCPKG_TARGET_TRIPLET: '${VCPKG_TARGET_TRIPLET}' ==!!!!")
message (STATUS "!!!!== VCPKG_MANIFEST_FEATURES: '${VCPKG_MANIFEST_FEATURES}' ==!!!!")
message (STATUS "!!!!== VCPKG_OVERLAY_TRIPLETS: '${VCPKG_OVERLAY_TRIPLETS}' ==!!!!")

find_package(cmake-top-lib CONFIG REQUIRED)
find_package(cmake-static-lib CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} CMakeApp.cpp)


# set compilation type for windows
# see: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html 
# for more options
set_target_properties(${PROJECT_NAME} PROPERTIES
        MSVC_RUNTIME_LIBRARY MultiThreadedDebug
#        MSVC_RUNTIME_LIBRARY MultiThreaded
)

get_target_property(MSVC_LINKING_TYPE ${PROJECT_NAME} MSVC_RUNTIME_LIBRARY)
message (STATUS "!!!!== AFTER set MSVC_LINKING_TYPE: '${MSVC_LINKING_TYPE}' ==!!!!")

# TODO: Add tests and install targets if needed.
target_link_libraries(${PROJECT_NAME} PRIVATE CMakeTopLib::CMakeTopLib)
