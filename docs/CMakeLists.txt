# SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
# SPDX-License-Identifier: Apache-2.0

# Setup

find_package(Doxygen REQUIRED)

# Dependencies

file(DOWNLOAD
	https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/main/doxygen-awesome.css
	${CMAKE_CURRENT_BINARY_DIR}/doxygen-awesome.css
)

file(DOWNLOAD
	https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/main/doxygen-awesome-sidebar-only.css
	${CMAKE_CURRENT_BINARY_DIR}/doxygen-awesome-sidebar-only.css
)

# Docs

set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_FULL_PATH_NAMES NO)

# doxygen-awesome
list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${CMAKE_CURRENT_BINARY_DIR}/"doxygen-awesome.css")
list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${CMAKE_CURRENT_BINARY_DIR}/"doxygen-awesome-sidebar-only.css")

list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET "custom.css")

set(DOXYGEN_EXTRACT_PRIVATE NO)
set(DOXYGEN_SORT_MEMBER_DOCS NO)
set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
set(DOXYGEN_EXAMPLE_PATH "../examples/src")

set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "src/mainpage.md")

set(DOCS_FILES
	"src/mainpage.md"
	"../include/ForceGraph/ForceSimulation.hpp"
	"../include/ForceGraph/Node.hpp"
)

doxygen_add_docs(
	doxygen
	${DOCS_FILES}
)
