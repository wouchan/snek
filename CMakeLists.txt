cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    snek
    VERSION 0.0.0
    LANGUAGES CXX
)

# download CPM.cmake
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.7/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=83e5eb71b2bbb8b1f2ad38f1950287a057624e385c238f6087f94cdfc44af9c5
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# add dependencies
CPMAddPackage("gh:raysan5/raylib#5.0")
CPMAddPackage("gh:RobLoach/raylib-cpp#v5.0.1")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cxx")
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR OFF
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-braced-scalar-init)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)
