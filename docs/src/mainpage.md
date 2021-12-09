<!-- SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
SPDX-License-Identifier: Apache-2.0 -->

# Tutorial {#mainpage}

ForceGraph is a [Force-Directed Graph](https://en.wikipedia.org/wiki/Force-directed_graph_drawing). This is a graph where nodes are simulated as physical bodies, and forces are applied to attempt to minimise the number of crossing links.

[![Collatz](example-collatz.gif)](#)

---

## Table of Contents

- [Usage](#usage)
- [Library reference](annotated.html)
- [CMake integration](#cmake)
- [Building manually](#building)

---

## Usage {#usage}

In most cases you'll only need to include the `ForceSimulation.hpp` header file.

```cpp
#include "ForceGraph/ForceSimulation.hpp"
```

Take a look at the ForceSimulation documentation [here](classfg_1_1ForceSimulation.html), or feel free to take a look at one of the examples:

 - [Collatz](Collatz_8cpp-example.html) Visualising the collatz conjecture.

---

## CMake integration {#cmake}

The simplest way to integrate ForceGraph into your project is via [CMake](https://cliutils.gitlab.io/modern-cmake/).

```cmake
include(FetchContent)

FetchContent_Declare(
	ForceGraph
	GIT_REPOSITORY "https://gitlab.com/metaquarx/forcegraph"
	GIT_TAG "v1.0.0"
)

FetchContent_MakeAvailable(ForceGraph)

# ...

target_link_libraries(my_executable PRIVATE ForceGraph)
```

### Building manually {#building}

If that is not suitable for your project, you can call cmake manually and then copy the artefacts that you need into your project

To build the project,
```
cmake -S . -B build -DFORCEGRAPH_BUILD_DOCS=ON
cmake --build build
```

To build the documentation (requires doxygen),
```
cmake --build build -t doxygen
```

To build the examples,
```
cmake --build build -t Collatz
```

To run the examples
```
./build/examples/Collatz
```
