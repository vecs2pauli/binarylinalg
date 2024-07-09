binarylinalg: a C library for linear algebra on binary matrices
===============================================================

Currently containing some elementary functionality for binary linear algebra:

- solving a system of binary linear equations
- determining if a binary vector is in the span of others
- bringing a binary matrix into row-reduced echelon form

`binarylinalg` was created to solve a specific task in quantum information/quantum computing. The functionality and naming in `extend_check_matrix.h` refers to this, but other than that, using the library does not require any knowledge of quantum information.

For typical example usage, see the files in the `examples` folder.

Building
--------
Ensure that you have a C/C++ compiler and CMake installed.
Then do:

```
mkdir build
cd build
cmake ..
cmake --build .
```


Testing
-------

After following the instructions 'Building':

```
cd build
make test
```
or
```
cd build
ctest -C Debug
```


Import as library to a different project
----------------------------------------

Create a folder 'myproj' with folder structure:

```
lib/
└── binarylinalg/
    └── <contents of this directory>
CMakeLists.txt
main.c
```

The file CMakeLists.txt:

```
cmake_minimum_required(VERSION 3.5)
project(foo LANGUAGES C)

add_subdirectory(lib/binarylinalg)
add_executable(foo main.c)
target_link_libraries(foo PUBLIC binarylinalg)
target_include_directories(foo PUBLIC "${PROJECT_SOURCE_DIR}/lib/")


```

An example file main.c:

```
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "binarylinalg/include/extend_check_matrix.h"
#include "binarylinalg/include/utils.h"
#include "binarylinalg/include/solve_linear_system.h"

int main(){
    // INITIALISING THE PROBLEM
    // creating the check matrix for 'X'
    // 1 0

    const size_t num_rows = 1;
    const size_t num_qubits = 1;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits];

    bool _first_row[2] = {true, false};
    extended_check_matrix[0] = &(_first_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // TEST the outputted check matrix:
    // verify that its first rows hasn't changed
    bool* expected_outputted_check_matrix[num_rows];
    bool _expected_first_row[2] = {true, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    printf("Done\n");

    return 0;
}
```


Then run in 'myproj':

```
mkdir build
cd build
cmake ..
cmake --build .
```

The file `main.c` is then compiled into the binary `foo` in the directory `build`.


Documentation
-------------
Further documentation can be found at [https://vecs2pauli.github.io/](https://vecs2pauli.github.io/).

To generate the documentation locally, install `doxygen` and run

```
doxygen doxyfile.in
```

Then open `docs/html/index.html` in your web browser.
