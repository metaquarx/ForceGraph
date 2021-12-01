# SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
# SPDX-License-Identifier: Apache-2.0

macro(MakeFile SOURCE)
	get_filename_component(NAME ${SOURCE} NAME_WE)

	add_executable(${NAME} EXCLUDE_FROM_ALL "src/${SOURCE}")
	set_target_properties(${NAME} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
	)

	target_link_libraries(${NAME} PRIVATE ForceGraph)

	target_include_directories(${NAME} PRIVATE "${NAME_CURRENT_SOURCE_DIR}")

	message(STATUS "Added example ${NAME}")
endmacro()

MakeFile("Collatz.cpp")
