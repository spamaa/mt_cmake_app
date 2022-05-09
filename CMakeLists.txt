# CMakeList.txt : CMake project for CMakeApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)


# this must be set if you want to compile direct from vstudio
if (NOT CMAKE_TOOLCHAIN_FILE)
    message (FATAL_ERROR "!!!! VCPKG INTEGRATION IS NOT ENABLED !!!!")
endif()


project ("CMakeApp")

if (NOT VCPKG_OVERLAY_TRIPLETS)
    message (FATAL_ERROR "!!!! TRIPLET DEFINITION LOCATION IS NOT SPECFIED !!!!")
endif()
if (NOT VCPKG_TARGET_TRIPLET)
    message (FATAL_ERROR "!!!! TRIPLET TYPE IS NOT SELECTED !!!!")
endif()
if (NOT VCPKG_FEATURE_FLAGS)
    message (FATAL_ERROR "!!!! VCPKG manifest and register mode is not enabled !!!!")
endif()


find_package(cmake-top-lib CONFIG REQUIRED)
find_package(cmake-static-lib CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} CMakeApp.cpp)

if (MSVC)
    # set proper runtime type for msvc
    set (MSVC_RUNTIME_TYPE)
    if (VCPKG_TARGET_TRIPLET STREQUAL "x64-windows-static")
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set (MSVC_RUNTIME_TYPE MultiThreadedDebug)
        elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
            set (MSVC_RUNTIME_TYPE MultiThreaded)
        else()
            message (FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'")
        endif()
    else()
        message (FATAL_ERROR "Unsuported vcpkg triplet: '${VCPKG_LIBRARY_LINKAGE}'")
    endif()

    # set compilation type for windows
    # see: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html 
    # for more options
    message (STATUS "Setting MSVC runtime type to: '${MSVC_RUNTIME_TYPE}'")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_TYPE}
    )
endif()

get_target_property(MSVC_LINKING_TYPE ${PROJECT_NAME} MSVC_RUNTIME_LIBRARY)
message (STATUS "!!!!== AFTER set MSVC_LINKING_TYPE: '${MSVC_LINKING_TYPE}' ==!!!!")
message (STATUS "!!!!== PROJECT_NAME: '${PROJECT_NAME}' ==!!!!")
message (STATUS "!!!!== CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}' ==!!!!")

# TODO: Add tests and install targets if needed.
target_link_libraries(${PROJECT_NAME} PRIVATE CMakeTopLib::CMakeTopLib)
