<!-- SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
SPDX-License-Identifier: Apache-2.0 -->

# Tutorial {#mainpage}

ForceGraph is a [Force-Directed Graph](https://en.wikipedia.org/wiki/Force-directed_graph_drawing). This is a graph where nodes are simulated as physical bodies, and forces are applied to attempt to minimise the number of crossing links.

---

## Table of Contents

- [Usage](#usage)
- [CMake integration](#cmake)
- [Library references](annotated.html)
- [Building manually](#building)

---

## Usage {#usage}

In most cases you'll only need to include the `ForceSimulation.hpp` header file.

```cpp
#include "ForceGraph/ForceSimulation.hpp"
```

Take a look at the [Collatz](Collatz_8cpp-example.html) example to see the library in use, or take a look at the [documentation](annotated.html).

---

## CMake integration {#cmake}

The simplest way to integrate ForceGraph into your project is via [CMake](https://cliutils.gitlab.io/modern-cmake/).

```cmake
include(FetchContent)

FetchContent_Declare(
	ForceGraph
	GIT_REPOSITORY "https://gitlab.com/metaquarx/forcegraph"
)

FetchContent_MakeAvailable(ForceGraph)

# ...

target_link_libraries(my_executable PRIVATE ForceGraph)
```

### Building manually {#building}

If that is not suitable for your project, you can call cmake manually and then copy the artefacts that you need into your project

To build the project,
```
cmake -S . -B build -DFORCEGRAPH_BUILD_DOCS=ON -DFORCEGRAPH_BUILD_EXAMPLES=ON
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
