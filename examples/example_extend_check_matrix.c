/* In this example, we start with the 1x4 matrix M (an 1x(2n) matrix with n=4):
 * M = 1 0 0 0
 * This matrix is the top row of a symplectic binary matrix (of dimensions (2n)x(2n) ).
 * We want to extend it to a nx(2n) = 2x4  matrix which forms the top two rows of
 * a 4x4 symplectic binary matrix.
 *
 * Compilation instructions:
 * gcc -I ../include/ ../src/*.c -o example_extend_check_matrix example_extend_check_matrix.c
 * The compiled binary is then called "example_extend_check_matrix".
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// from binarylinalg
#include "extend_check_matrix.h"
#include "utils.h"
#include "solve_linear_system.h"
#include "matrix.h"


#define NUM_ROWS 1
#define NUM_QUBITS 2
#define NUM_VARIABLES (2 * NUM_QUBITS)


int main(){
    // INITIALISING THE PROBLEM
    // 1 0 0 0

    bool* extended_check_matrix[NUM_QUBITS];

    bool _first_row[4] = {true, false, false, false};
    extended_check_matrix[0] = &(_first_row[0]);

    bool _second_row[4] = {false, false, false, false};
    extended_check_matrix[1] = &(_second_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(NUM_ROWS, NUM_QUBITS, extended_check_matrix);

    // TEST the outputted check matrix:
    // verify that its first rows hasn't changed
    bool* expected_outputted_check_matrix[NUM_ROWS];
    bool _expected_first_row[4] = {true, false, false, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    // SHOW THE RESULT
    print_matrix(2, 4, extended_check_matrix);
    // prints the matrix
    // 1 0 0 0
    // 0 0 0 1

    printf("Done\n");

    return 0;
}
