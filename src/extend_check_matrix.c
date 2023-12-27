#ifdef __cplusplus
extern "C" {
#endif
	#include "utils.h"
	#include "extend_check_matrix.h"
#ifdef __cplusplus
}
#endif



bool do_rows_commute(const size_t row_a, const size_t row_b, const size_t num_rows, const size_t num_qubits, bool** check_matrix){
	assert(row_a >= 0);
	assert(row_b >= 0);
	assert(row_a < num_rows);
	assert(row_b < num_rows);

	bool ret = true;
	const size_t num_columns = 2 * num_qubits;
	for(size_t j=0;j<num_columns;j++){
		ret ^= check_matrix[row_a][j] * check_matrix[row_b][(j + num_qubits) % num_columns];
	}
	return ret;
}

bool is_row_in_span_of_other_rows(const size_t row_under_question, const size_t num_columns, bool** scratch_matrix){

	// make a copy of 'scratch matrix'
	bool** matrix = (bool**) malloc(sizeof(bool*) * (row_under_question + 1));
	bool* row;
        for(size_t i=0;i<row_under_question + 1;i++){
        	row = (bool*) malloc(sizeof(bool) * num_columns); // NOTE we use num_columns+1 instead of num_columns because the rref function later will only perform rref on all but the very last column
        	for(size_t j=0;j<num_columns;j++){
	    	    row[j] = scratch_matrix[i][j];
    		}
        	matrix[i] = &(row[0]);
        }
	bool is_last_column_zero;

	//put the copy in rref
    	bring_into_rref(row_under_question + 1, num_columns, row_under_question + 1, num_columns, matrix);

	//check if the last column is zero
	size_t ix = 0;
	ulog("\nmatrix to check if last row is in span of others:\n");
	if(DEBUG_MODE){
		print_matrix(row_under_question + 1, num_columns, matrix);
	}

	while(ix<num_columns && !(*(*(matrix + row_under_question) + ix))){ix++;}
	is_last_column_zero = (ix == num_columns);

	//clean up
	for(size_t i=0;i<row_under_question;i++){
		free(matrix[i]);
	}
	free(matrix);
	return is_last_column_zero;
}

void extend_rref_check_matrix(const size_t num_rows, const size_t num_qubits, bool** extended_check_matrix){
    // TODO a problem currently is that elements in the kernel of a check matrix might not commute with each other..., so we cannot just add all basis elements to the check matrix and then perfrom RREF. Although we can just add a single element and 'sweep down' (i.e. only upper triangular form); if the remaining element does not become an all-zero row, then it is not in the span of the existing rows. Hence we may add it to the list, and then repeat until we have num_qubits rows
    // NOTE a full solution is to write down the symplectic equation M'*OMEGA*M'^T = OMEGA where M' is the check matrix with rows with variables appended, and then note that this is a linear equaion since x^2 may be replaced with x if x is boolean. Hence the solution to this set of linear equations is a full extension to the check matrix.
    
    //definitions
    assert(num_rows <= num_qubits);
    bool* _row;
    const size_t num_variables = num_qubits * 2;

    // check_matrix is a matrix of size num_rows x num_variables
    // extended_check_matrix is a matrix of size num_qubits x num_variables
    bool** scratch_matrix = (bool**) malloc(sizeof(bool*) * num_qubits); // matrix of size num_qubits x (num_variables + 1)
    bool** solutions = (bool**) malloc(sizeof(bool*) * num_variables); // matrix of size num_variables x (num_variables + 1)


    /* INITIALISATION */

    // initialise the top part of scratch_matrix to equal check_matrix; the rest of the rows only contain zeroes
    // set the first num_rows of extended_check_matrix equal to matrix
    // Also add a column with only zeroes at the end
    for(size_t i=0;i<num_rows;i++){
	_row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
	for(size_t j=0;j<num_variables;j++){
		_row[j] = extended_check_matrix[i][j];
	}
	_row[num_variables] = false;
	scratch_matrix[i] = &(_row[0]);
    }
    for(size_t i=num_rows;i<num_qubits;i++){
	_row = (bool*) malloc(sizeof(bool) * (num_variables + 1));
	for(size_t j=0;j<num_variables + 1;j++){
		_row[j] = false;
	}
	scratch_matrix[i] = &(_row[0]);
    }

    //TODO can the following lines be replaced by:
    //allocate_and_fill_solutions_template(num_variables, solutions);
    //
    // START of lines which might be replaced
    for(size_t i=0;i<num_variables;i++){
	_row = (bool *) malloc(sizeof(bool) * (num_variables + 1));
	for(size_t j=0;j<num_variables + 1;j++){
		_row[j] = false;
	}
	solutions[i] = &(_row[0]);
    } 
    // END of lines which might be replaced

    // FIND ROWS WHICH EXTEND THE CHECK MATRIX, ONE BY ONE

    size_t num_sols;
    size_t current_num_rows = num_rows;
    size_t ix;
    size_t basis_ix;

    while(current_num_rows < num_qubits){

        // initialise the top part of scratch_matrix to equal check_matrix; the rest of the rows only contain zeroes
        // set the first num_rows of extended_check_matrix equal to matrix
        // Also add a column with only zeroes at the end
        for(size_t i=0;i<current_num_rows;i++){
    	for(size_t j=0;j<num_variables;j++){
    		*((*(scratch_matrix + i)) + j) = *(*(extended_check_matrix + i) + j);
    	}
    	*(*(scratch_matrix + i) + num_variables) = false;
        }
        for(size_t i=current_num_rows;i<num_qubits;i++){
    	for(size_t j=0;j<num_variables + 1;j++){
    		*(*(scratch_matrix + i) + j) = false;
    	}
    	*(*(scratch_matrix + i) + num_variables) = false;
        }

	//Step 1. find basis for kernel, stored in the columns {1, 2, ...} of 'solutions'
    	reset_solutions_template(num_variables, solutions);
    	bring_into_rref(current_num_rows, num_variables + 1, current_num_rows, num_variables, scratch_matrix);  // TODO can be partially done outside of the loop; now doing double work
	ulog("rref scratch_matrix:\n");
	if(DEBUG_MODE){
		print_matrix(num_qubits, num_variables + 1, scratch_matrix);
	}
	num_sols = solutions_from_rref(num_rows, num_variables + 1, num_variables, scratch_matrix, solutions);
	assert(num_sols > 0);

	ulog("\ncur num rows = %li:\n", current_num_rows);
	ulog("(num_sols=%li) solutions:\n", num_sols);
	if(DEBUG_MODE){print_matrix(num_variables, num_variables + 1, solutions);}

	//Step 2. find a basis vector which is, when 'rotated', not already in the span of the existing check matrix
	basis_ix = 0;
	do{
		assert(basis_ix < num_sols);
		//re-initialise the last row by putting a 'rotated' basis in there
		for(size_t j=0;j<num_variables;j++){
			ix = (j + num_qubits) % num_variables;
			//printf("%b ", solutions[ix][basis_ix + 1]);
			*(*(scratch_matrix + current_num_rows) + j) = *(*(solutions + ix) + basis_ix + 1);
		}
		
    		ulog("\nscratch_matrix, extended, before (cur num rows=%li:", current_num_rows);
	    	if(DEBUG_MODE){print_matrix(num_qubits, num_variables + 1, scratch_matrix);}
    		ulog("\n");
		basis_ix++;
    	ulog("\nscratch_matrix, extended, after:\n");
	if(DEBUG_MODE){print_matrix(num_qubits, num_variables + 1, scratch_matrix);}
	}while(is_row_in_span_of_other_rows(current_num_rows, num_variables + 1, scratch_matrix));
	
	//Step 3. add the found basis to extended_check_matrix

	if(DEBUG_MODE){
	ulog("\nscratch_matrix, extended, finished:\n");
	print_matrix(num_qubits, num_variables + 1, scratch_matrix);
	ulog("\ncheck matrix, before extending:\n");
	print_matrix(num_qubits, num_variables, extended_check_matrix);
	ulog("\n Now adding (currentnumrows=%li, basisix+1=%li)", current_num_rows, basis_ix+1);
	}

	assert(basis_ix != 0);
	for(size_t j=0;j<num_variables;j++){
		ix = (j + num_qubits) % num_variables;
		//printf("%b ", solutions[ix][basis_ix]);
		*((*(extended_check_matrix + current_num_rows)) + j) = *(*(solutions + ix) + basis_ix);
	}
	ulog("\ncheck matrix, after extending:\n");
	if(DEBUG_MODE){print_matrix(num_qubits, num_variables, extended_check_matrix);}


	current_num_rows++;
		
    }

    // cleaning up
    tear_down_solutions_template(num_variables, solutions);
    for(size_t i=0;i<num_qubits;i++){
	    free(scratch_matrix[i]);
    }
    free(scratch_matrix);
    free(solutions);
}
