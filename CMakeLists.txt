# CMakeList.txt : CMake project for CMakeApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("CMakeApp")

# this include must be after project
include ("${VCPKG_INSTALLED_DIR}/${MATTERFI_CMAKE_HOST_TRIPLET}/${MATTERFI_CMAKE_CONFIG_FILE}")

# make vcpkg configuration checkings
matterfi_check_toolchain_file()
matterfi_check_triplets_location()
matterfi_check_triplet_file()
matterfi_check_vcpkg_modes()

find_package(cmake-top-lib CONFIG REQUIRED)
find_package(cmake-static-lib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} CMakeApp.cpp)

# set runtime type for msvc compilation
matterfi_set_msvc_type(${PROJECT_NAME})

# enable sanitizer
matterfi_enable_msvc_asan(CMakeApp)

get_target_property(MSVC_LINKING_TYPE ${PROJECT_NAME} MSVC_RUNTIME_LIBRARY)

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
