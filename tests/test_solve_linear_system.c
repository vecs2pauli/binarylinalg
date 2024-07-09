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

    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;

    // array of pointers to arrays of bools
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
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
    bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		row[column_ix] = false;
	}
	solutions[row_ix] = &(row[0]);
    }



    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);

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
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);
}


void test_two(){
	
    // INITIALISING THE PROBLEM
    
    // creating the following matrix
    // 0 0 0
    // 1 0 0
    // 1 0 
    const size_t num_rows = 3;
    const size_t num_variables = 2;
    const size_t num_columns = num_variables + 1;

    // array of pointers to arrays of bools
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
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
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		row[column_ix] = false;
	}
	solutions[row_ix] = &(row[0]);
    }

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);



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
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);
}



void test_three(){

    // INITIALISATION:
    /* We create the following matrix
     * 0 1 1 1
     * 1 0 0 1
     * 1 1 1 0
     * i.e. the matrix M with b appended at the right
     */
 
    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;
 
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
    bool* row;
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = true;
    row[2] = true;
    row[3] = true;
    matrix[0] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = false;
    row[2] = false;
    row[3] = true;
    matrix[1] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[2] = &(row[0]);
 

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

 
    //Initialize `solutions`: a matrix of 3 rows and 4 columns (num_variables and num_variables + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    allocate_and_fill_solutions_template(num_variables, solutions);

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);
    assert(solution_space_dimension == 1);

 
    // DISPLAY THE SOLUTION
    // should displays the matrix
    // 1 0 0 0
    // 1 1 0 0
    // 0 1 0 0
    // i.e. the solution set to the system of linear equation is 
    // {(1, 1, 0) + a * (1, 1, 0) + b * (0, 0, 0) + c * (0, 0, 0) | a, b, c are binary numbers}
    
    //verify correctness:
    // the solution to the inhomogeneous equation is [1, 0, 1]
    bool solution_inhomogeneous[3] = {true, true, false};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }

    bool first_vector[3] = {false, true, true};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][1] == first_vector[i]);
    }

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
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);

}


void test_four(){

    // INITIALISATION:
    /* We create the following matrix
     * 1 1 1 0
     * 1 1 1 0
     * 1 1 1 0
     * i.e. the matrix M with b appended at the right
M =
1 1 1
1 1 1
1 1 1
and
b =
0
0
0
     */
 
    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;
 
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
    bool* row;
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[0] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[1] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[2] = &(row[0]);
 

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

 
    //Initialize `solutions`: a matrix of 3 rows and 4 columns (num_variables and num_variables + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    allocate_and_fill_solutions_template(num_variables, solutions);

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);
    assert(solution_space_dimension == 2);

    // solution should be
    // 0 1 1 0
    // 0 1 0 0
    // 0 0 1 0
    
    //verify correctness:
    // the solution to the inhomogeneous equation is [1, 0, 1]
    bool solution_inhomogeneous[3] = {false, false, false};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }

    bool first_vector[3] = {true, true, false};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][1] == first_vector[i]);
    }

    bool second_vector[3] = {true, false, true};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][2] == second_vector[i]);
    }

    // all other entries in the vector 'solution' are zero
    for(size_t i=0;i<num_variables;i++){
          assert(!solutions[i][3]);
    }
 
    
    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);

}

void test_five(){

    // INITIALISATION:
    /* We create the following matrix
     * 1 1 1 1
     * 1 1 1 0
     * 1 1 1 0
     * i.e. the matrix M with b appended at the right
M =
1 1 1
1 1 1
1 1 1
and
b =
1
0
0
     */
 
    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;
 
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
    bool* row;
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = true;
    matrix[0] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[1] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[2] = &(row[0]);
 

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

 
    //Initialize `solutions`: a matrix of 3 rows and 4 columns (num_variables and num_variables + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    allocate_and_fill_solutions_template(num_variables, solutions);

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);

    // the system is unsolvable
    assert(solution_space_dimension == -1);

    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);

}

void test_six(){

    // INITIALISATION:
    /* We create the following matrix
     * 1 1 1 0
     * 0 0 0 0
     * 0 0 0 0
     * i.e. the matrix M with b appended at the right
     *
M =
1 1 1
0 0 0
0 0 0
and
b=
0
0
0
     */
 
    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;
 
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
    bool* row;
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = false;
    matrix[0] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    matrix[1] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    matrix[2] = &(row[0]);
 

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

 
    //Initialize `solutions`: a matrix of 3 rows and 4 columns (num_variables and num_variables + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    allocate_and_fill_solutions_template(num_variables, solutions);

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);
    assert(solution_space_dimension == 2);

    // solution should be
    // 0 1 1 0
    // 0 1 0 0
    // 0 0 1 0
    
    //verify correctness:
    // the solution to the inhomogeneous equation is [1, 0, 1]
    bool solution_inhomogeneous[3] = {false, false, false};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }

    bool first_vector[3] = {true, true, false};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][1] == first_vector[i]);
    }

    bool second_vector[3] = {true, false, true};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][2] == second_vector[i]);
    }

    // all other entries in the vector 'solution' are zero
    for(size_t i=0;i<num_variables;i++){
          assert(!solutions[i][3]);
    }
 
    
    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);

}

void test_seven(){

    // INITIALISATION:
    /* We create the following matrix
     * 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * i.e. the matrix M with b appended at the right
     *
M =
0 0 0
0 0 0
0 0 0
and
b=
0
0
0
     */
 
    const size_t num_rows = 3;
    const size_t num_variables = 3;
    const size_t num_columns = num_variables + 1;
 
    bool** matrix = (bool**) malloc (sizeof(bool*) * num_rows);
    bool* row;
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    matrix[0] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    matrix[1] = &(row[0]);
 
    row = (bool*) malloc(sizeof(bool) * num_columns);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    matrix[2] = &(row[0]);
 

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_columns, num_rows, num_columns - 1, matrix);

 
    //Initialize `solutions`: a matrix of 3 rows and 4 columns (num_variables and num_variables + 1, respectively)
    //The first column is solution to inhomogeneous equation M * v = b
    //The remaining columns are a basis of solutions v to the homogeneous equation M * v = (0, 0, 0)
        bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables);
    allocate_and_fill_solutions_template(num_variables, solutions);

    size_t solution_space_dimension = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);
    assert(solution_space_dimension == 3);

    // solution should be
    // 0 1 0 0
    // 0 0 1 0
    // 0 0 0 1
    
    //verify correctness:
    // the solution to the inhomogeneous equation is [1, 0, 1]
    bool solution_inhomogeneous[3] = {false, false, false};
    for(size_t i=0;i<num_rows;i++){
	   assert(solutions[i][0] == solution_inhomogeneous[i]);
    }

    bool first_vector[3] = {true, false, false};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][1] == first_vector[i]);
    }

    bool second_vector[3] = {false, true, false};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][2] == second_vector[i]);
    }

    // all other entries in the vector 'solution' are zero
    bool third_vector[3] = {false, false, true};
    for(size_t i=0;i<num_rows;i++){
	  assert(solutions[i][3] == third_vector[i]);
    }
 
    
    // cleaning up
    for(size_t i=0;i<num_rows;i++){
	    free(matrix[i]);
    }
    free(matrix);
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
    free(solutions);

}

int main(){
    test_one();
    test_two();
    test_three();
    test_four();
    test_five();
    test_six();
    test_seven();
    return 0;
}
