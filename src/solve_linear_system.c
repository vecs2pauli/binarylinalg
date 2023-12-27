#ifdef __cplusplus
extern "C" {
#endif
#include "solve_linear_system.h"
#ifdef __cplusplus
}
#endif


bool single_solution_from_rref(const size_t num_rows, const size_t num_columns, bool** matrix, bool** solutions){

	size_t column = 0;
	size_t row = 0;
	size_t row_ix;

	while(row < num_rows){

		//finding a pivot column
		while(column < num_columns - 1 && !matrix[row][column]){
			column++;
		}
		if(column == num_columns - 1){
			// no more pivots to be found, hence this row and all rows below will only contain zeroes (since the matrix is in RREF)
			// Hence only a solution is possible if this entry in 'b' and all next ones may only contain zeroes
			for(row_ix=row;row_ix<num_rows;row_ix++){
				if(matrix[num_columns-1][row_ix])
				{
					// no solutions possible
					return false;
				}
			}
			// confirmed that 'b' only contains zeroes from 'row' downwards
			return true;
		}
		else{
			//pivot found in column 'column'
			solutions[column][0] = matrix[row][num_columns-1];
			column++;
		}
		row++;
	}
	return true;
}


size_t solutions_from_rref(const size_t num_rows, const size_t num_columns, const size_t num_variables, bool** matrix, bool** solutions){

	// find single solution to the inhomogeneous equation M*v=b
	//
	bool antw = single_solution_from_rref(num_rows, num_columns, matrix, solutions);
	if(!antw){return -1;}

	//find basis for the kernel of M, i.e. solutions to a basis to vector space of vector satisfying the homogeneous equation M*v=0
	
	//Step 1: create an array 'pivots' such that pivots[r] = the column index at which the pivot of row r resides, or num_columns if there is no pivot (i.e. row r consists of zeroes only)
	size_t column = 0;
	size_t row = 0;
	size_t *pivots = (size_t*) malloc(sizeof(size_t) * num_rows);
	size_t ix;
	for(ix=0;ix<num_rows;ix++){
		pivots[ix] = num_columns;
	}

	while(column < num_columns - 1 && row < num_rows){
		while(column < num_columns - 1 && !matrix[row][column]){column++;}
		if(column != num_columns - 1){
			//pivot found
			pivots[row] = column;
			column++;
			row++;
		}
		else{
			//no more pivots to be found; outer while loop will terminate automatically
		}
	}

	//Step 2: find basis for kernel
	column = 0;
	row = 0;
	size_t pos;
	size_t current_solution_ix = 0;
	size_t row_ix;

	for(column=0;column<num_columns-1;column++){
		pos = position_in_array(pivots, num_rows, column);
		if(pos == num_rows){
			//'column' is not in 'pivots', i.e. 'column' does not contain a pivot
			// Now we add a new 'raw basis vector' v, which is the unit vector with only zeroes, and a 1 at position 'column'
			solutions[column][current_solution_ix + 1] = true; //single the first column of 'solutions' is reserved for the inhomogeneous solution, we need to add 1 to 'current_solution_ix'
			for(row_ix=0;row_ix<num_rows;row_ix++){
				if(matrix[row_ix][column]){
					solutions[pivots[row_ix]][current_solution_ix + 1] = true;
				}
			}
			current_solution_ix++;
		}
	}
	free(pivots);
	return current_solution_ix;
}



void allocate_and_fill_solutions_template(const size_t num_variables, bool** solutions){

    bool* row;
    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		row[column_ix] = false;
	}
	solutions[row_ix] = &(row[0]);
    }
}

void reset_solutions_template(const size_t num_variables, bool** solutions){

    for(size_t row_ix=0;row_ix<num_variables;row_ix++){
    	for(size_t column_ix=0;column_ix<num_variables + 1;column_ix++){
		solutions[row_ix][column_ix] = false;
	}
    }
}

void tear_down_solutions_template(const size_t num_variables, bool** solutions){
    for(size_t i=0;i<num_variables;i++){
	    free(solutions[i]);
    }
}
