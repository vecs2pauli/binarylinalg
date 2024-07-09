/* In this example, we want to solve the linear system of equations M*x=b, where
 * M = 0 1 0
 *     1 1 0
 *     1 0 1
 * and
 * b = 0
 *     1
 *     0
 *
 * Compilation instructions:
 * gcc -I ../include/ ../src/*.c -o example_solve_linear_system example_solve_linear_system.c
 * The compiled binary is then called "example_solve_linear_system".
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// from binarylinalg
#include "solve_linear_system.h"
#include "matrix.h"
#include "utils.h"


#define NUM_ROWS 3
#define NUM_VARIABLES 3
#define NUM_COLUMNS (NUM_VARIABLES + 1)

int main(){

    // INITIALISATION:
    /* We create the following matrix
     * 0 1 0 0
     * 1 1 0 1
     * 1 0 1 0
     * i.e. the matrix M with b appended at the right
     */

    bool* matrix[NUM_ROWS];
    bool* row;

    row = (bool*) malloc(sizeof(bool) * NUM_COLUMNS);
    row[0] = false;
    row[1] = true;
    row[2] = false;
    row[3] = false;
    matrix[0] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * NUM_COLUMNS);
    row[0] = true;
    row[1] = true;
    row[2] = false;
    row[3] = true;
    matrix[1] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * NUM_COLUMNS);
    row[0] = true;
    row[1] = false;
    row[2] = true;
    row[3] = false;
    matrix[2] = &(row[0]);

    // SOLVING THE PROBLEM
    bring_into_rref(NUM_ROWS, NUM_COLUMNS, NUM_ROWS, NUM_COLUMNS - 1, matrix);

    //Initialize `solutions`: a matrix of 3 rows and 4 columns (NUM_VARIABLES and NUM_VARIABLES + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
    bool* solutions[NUM_VARIABLES];
    allocate_and_fill_solutions_template(NUM_VARIABLES, solutions);

    size_t solution_space_dimension = solutions_from_rref(NUM_ROWS, NUM_COLUMNS, NUM_VARIABLES, matrix, solutions);

    // DISPLAY THE SOLUTION
    print_matrix(NUM_ROWS, NUM_COLUMNS, solutions);
    // displays the matrix
    // 1 0 0 0
    // 0 0 0 0
    // 1 0 0 0
    // i.e. the solution set to the system of linear equation is 
    // {(1, 0, 1) + a * (0, 0, 0) + b * (0, 0, 0) + c * (0, 0, 0) | a, b, c are binary numbers}

    printf("\nThe dimension of the solution space is %zu. \n", solution_space_dimension);
    // Prints "The dimension of the solution space is 0", because indeed, the solution set only
    // contains the vector (1, 0, 1)
    
    // Cleaning up
    for(size_t i=0;i<NUM_ROWS;i++){
	    free(matrix[i]);
    }
    for(size_t i=0;i<NUM_VARIABLES;i++){
	    free(solutions[i]);
    }

    return 0;
}
