#ifdef __cplusplus
extern "C" {
#endif
#include "utils.h"
#include "matrix.h"
#ifdef __cplusplus
}
#endif


size_t position_in_array(size_t* array, size_t array_size, size_t element){
	size_t ix = 0;
	for(ix=0;ix<array_size;ix++){
		if(array[ix] == element){return ix;}
	}
	return array_size;
}


void print_matrix(const size_t num_rows, const size_t num_columns, bool** matrix){
	printlogstring();
	for(size_t row_ix=0;row_ix<num_rows;row_ix++){
		printlogstring();
		for(size_t column_ix=0;column_ix<num_columns;column_ix++){
			printf("%i,", matrix[row_ix][column_ix]);
		}
	}
}

void print_vector(const size_t num_rows, bool* vector){
	for(size_t row_ix=0;row_ix<num_rows;row_ix++){
		printlogstring();
		printf("%i,", vector[row_ix]);
	}
}


void add_row(const size_t num_rows, const size_t num_columns, const size_t row_a, const size_t row_b, bool ** matrix){
    assert(row_a >= 0);
    assert(row_b >= 0);
    assert(row_a < num_rows);
    assert(row_b < num_rows);
    for(size_t i=0;i<num_columns;i++){
        matrix[row_b][i] ^= matrix[row_a][i];
    }
}


void swap_rows(const size_t num_rows, const size_t row_a, const size_t row_b, bool ** matrix){
    assert(row_a >= 0);
    assert(row_b >= 0);
    assert(row_a < num_rows);
    assert(row_b < num_rows);
    bool * temp = matrix[row_a];
    matrix[row_a] = matrix[row_b];
    matrix[row_b] = temp;
}


void insert_row(const size_t num_rows, const size_t row, const size_t position, bool ** matrix){
    assert(row >= 0);
    assert(position >= 0);
    assert(position <= row);
    assert(row < num_rows);
    assert(position < num_rows);

    for(size_t i=position;i<row;i++){
    	swap_rows(num_rows, row, i, matrix);
    }
}


void bring_into_rref(const size_t num_rows, const size_t num_columns, const size_t max_row, const size_t max_column, bool** matrix){
	assert(num_rows > 0);
	assert(num_columns > 0);
	assert(max_row <= num_rows);
	assert(max_column <= num_columns);

	size_t top_row = 0;
	size_t current_column = 0;

	size_t current_row;
	size_t row_ix;

	while(top_row < max_row && current_column < max_column){
		
		// find smallest row index 'current_row' among {top_row, top_row+1,...,max_row} such that matrix[current_row][current_row] = true
		current_row = top_row;
		while(current_row<max_row && !matrix[current_row][current_column]){current_row++;}
		if(current_row != max_row)
		{
			// row index found!

			// TODO if not working, replace 'insert_row' by 'swap_rows'
			swap_rows(num_rows, current_row, top_row, matrix);
			//insert_row(num_rows, current_row, top_row, matrix);
			
			//NOTE: if the for loop below starts at top_row+1, then only brings into upper triangular form, not in RREF (I think, should doublecheck)
			for(row_ix=0;row_ix<max_row;row_ix++){
				if(row_ix!=top_row && matrix[row_ix][current_column] == true){
					add_row(num_rows, num_columns, top_row, row_ix, matrix);
				}
			}
			top_row++;
			current_column++;
		}
		else{
			// no row index found, hence entire remainder of the column consists of zeroes
			current_column++;
		}
	}
}
