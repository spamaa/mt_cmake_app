# CMakeList.txt : CMake project for CMakeApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)


# check if toolchain file is set
if (NOT DEFINED  CMAKE_TOOLCHAIN_FILE)
    message (FATAL_ERROR "!!!! VCPKG INTEGRATION IS NOT ENABLED !!!!")
else()
    if (NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
        message (FATAL_ERROR "!!!! cmake toolchain file does not exists: '${CMAKE_TOOLCHAIN_FILE}' !!!!")
    else()
        message (STATUS "Using cmake toolchain file: '${CMAKE_TOOLCHAIN_FILE}'")
    endif()
endif()


project ("CMakeApp")

# check if triplets directory exists
if (NOT DEFINED VCPKG_OVERLAY_TRIPLETS)
    message (FATAL_ERROR "!!!! TRIPLET DEFINITION LOCATION IS NOT SPECFIED !!!!")
else()
    if(NOT IS_DIRECTORY "${VCPKG_OVERLAY_TRIPLETS}")
        message (FATAL_ERROR "!!!! triplets directory not exists: '${VCPKG_OVERLAY_TRIPLETS}' !!!!")
    else()
        message (STATUS "Using triplets from: '${VCPKG_OVERLAY_TRIPLETS}'")
    endif()
endif()

# check if triplet is set
if (NOT DEFINED VCPKG_TARGET_TRIPLET)
    message (FATAL_ERROR "!!!! TRIPLET TYPE IS NOT SELECTED !!!!")
else()
    message (STATUS "Using triplet: '${VCPKG_TARGET_TRIPLET}'")
endif()
if (NOT DEFINED VCPKG_FEATURE_FLAGS)
    message (FATAL_ERROR "!!!! VCPKG manifest and register mode is not enabled !!!!")
endif()


find_package(cmake-top-lib CONFIG REQUIRED)
find_package(cmake-static-lib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} CMakeApp.cpp)

if (MSVC)
    # set proper runtime type for msvc
    set (MSVC_RUNTIME_TYPE)
    if (NOT DEFINED VCPKG_TARGET_TRIPLET)
        message (FATAL_ERROR "Unknown vcpkg triplet: '${VCPKG_LIBRARY_LINKAGE}'")
    else()
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set (MSVC_RUNTIME_TYPE MultiThreadedDebug)
        elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
            set (MSVC_RUNTIME_TYPE MultiThreaded)
        else()
            message (FATAL_ERROR "Unsupported CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'")
        endif()
         message (STATUS "Using triplet: '${VCPKG_TARGET_TRIPLET}'")
    endif()

    # set compilation type for windows
    # see: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html 
    # for more options
    message (STATUS "Setting MSVC runtime type to: '${MSVC_RUNTIME_TYPE}'")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_TYPE}
    )
endif()

# enable sanitizer
if (MSVC_ENABLE_ASAN)
    message (STATUS "CMakeApp build with MSVC ASAN.")
    target_compile_options(${PROJECT_NAME} PUBLIC
        /fsanitize=address
    )
else()
    message (STATUS "CMakeApp build without MSVC ASAN.")
endif()


get_target_property(MSVC_LINKING_TYPE ${PROJECT_NAME} MSVC_RUNTIME_LIBRARY)
message (STATUS "!!!!== AFTER set MSVC_LINKING_TYPE: '${MSVC_LINKING_TYPE}' ==!!!!")
message (STATUS "!!!!== PROJECT_NAME: '${PROJECT_NAME}' ==!!!!")
message (STATUS "!!!!== CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}' ==!!!!")
message (STATUS "!!!!== CMAKE_TOOLCHAIN_FILE: '${CMAKE_TOOLCHAIN_FILE}' ==!!!!")

if (USE_EXTENDED_LIBS)
    message (STATUS "${PROJECT_NAME} uses CMakeLibTop-ext")
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            CMakeTopLib::CMakeTopLib-ext
    )
else()
    message (STATUS "${PROJECT_NAME} uses CMakeLibTop")
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            CMakeTopLib::CMakeTopLib
    )
endif()

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        fmt::fmt
)

# TODO: Add tests and install targets if needed.
message (STATUS "!!!!== CMAKE_C_FLAGS: '${CMAKE_C_FLAGS}' ==!!!!")
message (STATUS "!!!!== CMAKE_CXX_FLAGS: '${CMAKE_CXX_FLAGS}' ==!!!!")
message (STATUS "!!!!== COMPILE_OPTIONS: '${COMPILE_OPTIONS}' ==!!!!")
message (STATUS "!!!!== INTERFACE_COMPILE_OPTIONS: '${INTERFACE_COMPILE_OPTIONS}' ==!!!!")
