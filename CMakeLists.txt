# Require at least CMake version 3.15 or later for FetchContent
cmake_minimum_required(VERSION 3.15)

project(VTIL-Python)

# Variables
option(VTIL_PYTHON_VERSION "Version string" "dev")

# Dependencies
add_subdirectory(external/core)
add_subdirectory(external/pybind11)

# Hack to build with -fPIC on Linux
if(UNIX AND NOT APPLE)
    target_compile_options(capstone-static PUBLIC -fPIC)
endif()

# Python module
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.hpp
    )

pybind11_add_module(${PROJECT_NAME} NO_EXTRAS ${SOURCES})

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_INFO="${VTIL_PYTHON_VERSION}")

target_link_libraries(${PROJECT_NAME} PRIVATE VTIL)

if(WIN32)
    set(EXTENSION ".pyd")
else()
    set(EXTENSION ".so")
endif()

install(PROGRAMS
    $<TARGET_FILE:${PROJECT_NAME}>
    DESTINATION .
    COMPONENT pyd
    RENAME vtil${EXTENSION}
    )