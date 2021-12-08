# SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
# SPDX-License-Identifier: Apache-2.0

# Setup

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(ForceGraph VERSION 1.0.0 LANGUAGES CXX)

option(FORCEGRAPH_BUILD_DOCS "Build ForceGraph documentation" OFF)

# Build types

set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set (CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)

	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# ForceGraph

set(SOURCE_FILES
	"src/ForceSimulation.cpp"
	"src/Node.cpp"
	"src/Maths.cpp"
	"src/PhysicsSystems.cpp"
	"src/Arrow.cpp"
)

add_library(ForceGraph ${SOURCE_FILES})

target_include_directories(ForceGraph PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(ForceGraph PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(ForceGraph PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

# Dependencies

include(FetchContent)

FetchContent_Declare(
	Stitch
	GIT_REPOSITORY "https://gitlab.com/metaquarx/stitch"
	GIT_TAG "v0.4.1"
)

FetchContent_MakeAvailable(Stitch)

target_link_libraries(ForceGraph PUBLIC Stitch)

set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)

FetchContent_Declare(
	sfml
	GIT_REPOSITORY "https://github.com/SFML/SFML"
	GIT_TAG "110fb75513301af5400df0b9c499510a90684dc6" # After 2.5.1, needed for fix to https://github.com/SFML/SFML/issues/1626
)

FetchContent_MakeAvailable(sfml)

target_link_libraries(ForceGraph PUBLIC sfml-graphics)

# Docs

add_subdirectory(examples)

if (FORCEGRAPH_BUILD_DOCS)
	add_subdirectory(docs)
endif()
