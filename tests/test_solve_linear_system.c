#ifdef __cplusplus
extern "C" {
#endif
	#include "solve_linear_system.h"
	#include "utils.h"
#ifdef __cplusplus
}
#endif


void test_one(){
	
    // INITIALISING THE PROBLEM
    // creating the following matrix
    // 0 1 0 0
    // 1 1 0 1
    // 1 0 1 0
    // which describes the linear system of equations M*x=b
    // where
    // M = 0 1 0
    //     1 1 0
    //     1 0 1
    // and
    // b = 0
    //     1
    //     0

    #define num_rows_test_one 3
    #define num_variables_test_one 3
    const size_t num_rows = num_rows_test_one;
    const size_t num_variables = num_variables_test_one;
    const size_t num_columns = num_variables + 1;

    // array of pointers to arrays of bools
    bool* matrix[num_rows_test_one];
    bool* row;

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = true;
    row[2] = false;
    row[3] = false;
    matrix[0] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = false;
    row[3] = true;
    matrix[1] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = false;
    row[2] = true;
    row[3] = false;
    matrix[2] = &(row[0]);

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);


    //initialize solutions: matrix of num_variables rows and num_variables+1 columns
    //first column is solution to inhomogeneous equation
    //remaining columns are a basis of solutions to homogeneous equation
    bool* solutions[num_variables_test_one];
    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		row[column_ix] = false;
	}
	solutions[row_ix] = &(row[0]);
    }



    int solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);

    //verify correctness:
    // the solution to the inhomogeneous equation is [1, 0, 1]
    bool solution_inhomogeneous[3] = {true, false, true};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }
    // only the trivial vector [0, 0, 0] is a solution to the homogeneous equation,
    // so all other entries in the vector 'solution' are zero
    for(size_t i=0;i<num_variables;i++){
    	for(size_t j=1;j<num_variables+1;j++){
		    assert(!solutions[i][j]);
	    }
    }
    assert(solution_space_dimension == 0);
    
    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
}


void test_two(){
	
    // INITIALISING THE PROBLEM
    
    // creating the following matrix
    // 0 0 0
    // 1 0 0
    // 1 0 
    #define num_rows_test_two 3
    #define num_variables_test_two 2
    const size_t num_rows = num_rows_test_two;
    const size_t num_variables = num_variables_test_two;
    const size_t num_columns = num_variables + 1;

    // array of pointers to arrays of bools
    bool* matrix[num_rows_test_two];
    bool* row;

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    matrix[0] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = false;
    row[2] = false;
    matrix[1] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = false;
    row[2] = false;
    matrix[2] = &(row[0]);

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

    //initialize solutions: matrix of num_variables rows and num_variables+1 columns
    //first column is solution to inhomogeneous equation
    //remaining columns are a basis of solutions to homogeneous equation
    bool* solutions[num_variables_test_two];
    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		row[column_ix] = false;
	}
	solutions[row_ix] = &(row[0]);
    }

    int solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);



    //verify correctness:
    //a solution to the inhomogeneous equation is [0, 0]
    bool solution_inhomogeneous[2] = {false, false};
    for(size_t i=0;i<num_variables;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }

    // the dimension of the kernel of M is 1 and is spanned by [0, 1]
    assert(!solutions[1][0]);
    assert(solutions[1][1]);



    assert(solution_space_dimension == 1);
    // all other entries in the vector 'solution' are zero
    for(size_t i=0;i<num_variables;i++){
    	for(size_t j=2;j<num_variables+1;j++){
		    assert(!solutions[i][j]);
	    }
    }

    
    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
}




int main(){

    test_one();
    test_two();
    return 0;
}
