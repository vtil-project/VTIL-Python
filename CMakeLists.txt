# Require at least CMake version 3.15 or later for FetchContent
cmake_minimum_required(VERSION 3.14.5)

project(VTIL-Python)

# Dependencies
add_subdirectory(external/core)
add_subdirectory(external/pybind11)

# Python module
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.hpp
    )

pybind11_add_module(${PROJECT_NAME} ${SOURCES})

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES})

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