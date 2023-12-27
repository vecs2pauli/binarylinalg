#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif
	#include "extend_check_matrix.h"
#include "utils.h"
#include "solve_linear_system.h"
#ifdef __cplusplus
}
#endif


void test_one(){

    // INITIALISING THE PROBLEM
    // creating the check matrix for 'ZZI', 'IZZ'
    // 0 0 0 1 1 0
    // 0 0 0 0 1 1

    #define num_qubits_test_one 3
    #define num_rows_test_one 2
    const size_t num_rows = num_rows_test_one;
    const size_t num_qubits = num_qubits_test_one;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits_test_one];

    bool _first_row[6] = {false, false, false, true, true, false};
    extended_check_matrix[0] = &(_first_row[0]);

    bool _second_row[6] = {false, false, false, false, true, true};
    extended_check_matrix[1] = &(_second_row[0]);

    bool _third_row[6] = {false, false, false, false, false, false};
    extended_check_matrix[2] = &(_third_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // test the outputted check matrix
    // 1. verify that its first two rows haven't changed

    bool* expected_outputted_check_matrix[num_rows_test_one];
    bool _expected_first_row[6] = {false, false, false, true, true, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    bool _expected_second_row[6] = {false, false, false, false, true, true};
    expected_outputted_check_matrix[1] = &(_expected_second_row[0]);

    for(size_t i=0;i<num_rows;i++){
	    for(size_t j=0;j<num_variables;j++){
		assert(expected_outputted_check_matrix[i][j] == extended_check_matrix[i][j]);
	    }
    }

    // 2. verify that all rows commute with each other
    for(size_t row_a=0;row_a<num_qubits;row_a++){
    	for(size_t row_b=0;row_b<num_qubits;row_b++){
		assert(do_rows_commute(row_a, row_b, num_qubits, num_qubits, extended_check_matrix));
	}
    }

    // 3. verify that it is full rank
    bring_into_rref(num_qubits, num_variables, num_qubits, num_variables, extended_check_matrix);
    assert(!is_row_in_span_of_other_rows(num_qubits - 1, num_variables, extended_check_matrix));


}

void test_two(){

    // INITIALISING THE PROBLEM
    // creating the check matrix for 'YYII', 'XXXX'
    // 1 1 0 0 1 1 0 0
    // 1 1 1 1 0 0 0 0

    #define num_rows_test_two 2
    #define num_qubits_test_two 4
    const size_t num_rows = num_rows_test_two;
    const size_t num_qubits = num_qubits_test_two;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits_test_two];

    bool _first_row[8] = {true, true, false, false, true, true, false, false};
    extended_check_matrix[0] = &(_first_row[0]);

    bool _second_row[8] = {true, true, true, true, false, false, false, false};
    extended_check_matrix[1] = &(_second_row[0]);

    bool _third_row[8] = {false, false, false, false, false, false, false, false};
    extended_check_matrix[2] = &(_third_row[0]);

    bool _fourth_row[8] = {false, false, false, false, false, false, false, false};
    extended_check_matrix[3] = &(_fourth_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // test the outputted check matrix
    // 1. verify that its first two rows haven't changed
    bool* expected_outputted_check_matrix[num_rows_test_two];
    bool _expected_first_row[8] = {true, true, false, false, true, true, false, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    bool _expected_second_row[8] = {true, true, true, true, false, false, false, false};
    expected_outputted_check_matrix[1] = &(_expected_second_row[0]);

    for(size_t i=0;i<num_rows;i++){
	    for(size_t j=0;j<num_variables;j++){
		assert(expected_outputted_check_matrix[i][j] == extended_check_matrix[i][j]);
	    }
    }

    // 2. verify that all rows commute with each other
    for(size_t row_a=0;row_a<num_qubits;row_a++){
    	for(size_t row_b=0;row_b<num_qubits;row_b++){
		assert(do_rows_commute(row_a, row_b, num_qubits, num_qubits, extended_check_matrix));
	}
    }

    // 3. verify that it is full rank
    bring_into_rref(num_qubits, num_variables, num_qubits, num_variables, extended_check_matrix);
    assert(!is_row_in_span_of_other_rows(num_qubits - 1, num_variables, extended_check_matrix));

}


void test_three(){

    // INITIALISING THE PROBLEM
    // creating the check matrix for 'X'
    // 1 0

    #define num_rows_test_three 1
    #define num_qubits_test_three 1
    const size_t num_rows = num_rows_test_three;
    const size_t num_qubits = num_qubits_test_three;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits_test_three];

    bool _first_row[2] = {true, false};
    extended_check_matrix[0] = &(_first_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // test the outputted check matrix
    // 1. verify that its first two rows haven't changed
    bool* expected_outputted_check_matrix[num_rows_test_three];
    bool _expected_first_row[2] = {true, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    for(size_t i=0;i<num_rows;i++){
	    for(size_t j=0;j<num_variables;j++){
		assert(expected_outputted_check_matrix[i][j] == extended_check_matrix[i][j]);
	    }
    }

    // 2. verify that all rows commute with each other
    for(size_t row_a=0;row_a<num_qubits;row_a++){
    	for(size_t row_b=0;row_b<num_qubits;row_b++){
		assert(do_rows_commute(row_a, row_b, num_qubits, num_qubits, extended_check_matrix));
	}
    }

    // 3. verify that it is full rank
    bring_into_rref(num_qubits, num_variables, num_qubits, num_variables, extended_check_matrix);
    assert(!is_row_in_span_of_other_rows(num_qubits - 1, num_variables, extended_check_matrix));

}

void test_four(){

    // INITIALISING THE PROBLEM
    // creating the check matrix for 'X'
    // 1 0

    #define num_rows_test_four 1
    #define num_qubits_test_four 1
    const size_t num_rows = num_rows_test_four;
    const size_t num_qubits = num_qubits_test_four;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits_test_four];

    bool _first_row[2] = {true, false};
    extended_check_matrix[0] = &(_first_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // test the outputted check matrix
    // 1. verify that its first two rows haven't changed
    bool* expected_outputted_check_matrix[num_rows_test_four];
    bool _expected_first_row[2] = {true, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    for(size_t i=0;i<num_rows;i++){
	    for(size_t j=0;j<num_variables;j++){
		assert(expected_outputted_check_matrix[i][j] == extended_check_matrix[i][j]);
	    }
    }

    // 2. verify that all rows commute with each other
    for(size_t row_a=0;row_a<num_qubits;row_a++){
    	for(size_t row_b=0;row_b<num_qubits;row_b++){
		assert(do_rows_commute(row_a, row_b, num_qubits, num_qubits, extended_check_matrix));
	}
    }

    // 3. verify that it is full rank
    bring_into_rref(num_qubits, num_variables, num_qubits, num_variables, extended_check_matrix);
    assert(!is_row_in_span_of_other_rows(num_qubits - 1, num_variables, extended_check_matrix));

}

void test_five(){

    // INITIALISING THE PROBLEM
    // creating the check matrix for 'YIZZXX', 'IIXXYY'
    // 1 0 0 0 1 1 1 0 1 1 0 0
    // 0 0 1 1 1 1 0 0 1 1 1 1
    //
    #define num_rows_test_five 2
    #define num_qubits_test_five 6
    const size_t num_rows = num_rows_test_five;
    const size_t num_qubits = num_qubits_test_five;
    const size_t num_variables = 2 * num_qubits;
    bool* extended_check_matrix[num_qubits_test_five];

    bool _first_row[12] =  {true,  false, false, false, true, true,  true,  false, true, true, false, false};
    extended_check_matrix[0] = &(_first_row[0]);

    bool _second_row[12] = {false, false, true,  true,  true,  true,  false, false, true,  true, true, true};
    extended_check_matrix[1] = &(_second_row[0]);
    
    bool _third_row[12] = {false, false, false,  false,  false,  false,  false, false, false,  false, false, false};
    extended_check_matrix[2] = &(_third_row[0]);

    bool _fourth_row[12] = {false, false, false,  false,  false,  false,  false, false, false,  false, false, false};
    extended_check_matrix[3] = &(_fourth_row[0]);

    bool _fifth_row[12] = {false, false, false,  false,  false,  false,  false, false, false,  false, false, false};
    extended_check_matrix[4] = &(_fifth_row[0]);

    bool _sixth_row[12] = {false, false, false,  false,  false,  false,  false, false, false,  false, false, false};
    extended_check_matrix[5] = &(_sixth_row[0]);

    // SOLVING THE PROBLEM
    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    // test the outputted check matrix
    // 1. verify that its first two rows haven't changed
    bool* expected_outputted_check_matrix[num_rows_test_five];

    bool _expected_first_row[12] = {true,  false, false, false, true, true,  true,  false, true, true, false, false};
    expected_outputted_check_matrix[0] = &(_expected_first_row[0]);

    bool _expected_second_row[12] = {false, false, true,  true,  true,  true,  false, false, true,  true, true, true};
    expected_outputted_check_matrix[1] = &(_expected_second_row[0]);

    for(size_t i=0;i<num_rows;i++){
	    for(size_t j=0;j<num_variables;j++){
		assert(expected_outputted_check_matrix[i][j] == extended_check_matrix[i][j]);
	    }
    }

    // 2. verify that all rows commute with each other
    for(size_t row_a=0;row_a<num_qubits;row_a++){
    	for(size_t row_b=0;row_b<num_qubits;row_b++){
		assert(do_rows_commute(row_a, row_b, num_qubits, num_qubits, extended_check_matrix));
	}
    }

    // 3. verify that it is full rank
    bring_into_rref(num_qubits, num_variables, num_qubits, num_variables, extended_check_matrix);
    assert(!is_row_in_span_of_other_rows(num_qubits - 1, num_variables, extended_check_matrix));
}



int main(){

	test_one();
	test_two();
	test_three();
	test_four();
	test_five();
	return 0;


    // INITIALISING THE PROBLEM
    // creating the check matrix for 'XXX, YYI'
    // creating the check matrix for 'ZZI', 'IZZ'
    // creating the check matrix for 'XXXX, ZZII, IZZI
    // 0 0 0 1 1 0
    // 0 0 0 0 1 1

    #define num_rows_main 3
    #define num_qubits_main 4
    const size_t num_rows = num_rows_main;
    const size_t num_qubits = num_qubits_main;
    const size_t num_variables = 2 * num_qubits;

    // array of pointers to arrays of bools
    bool* check_matrix[num_rows_main];
    bool* row;

    row = (bool*) malloc(sizeof(bool) * num_variables);
    row[0] = true;
    row[1] = true;
    row[2] = true;
    row[3] = true;
    row[4] = false;
    row[5] = false;
    row[6] = false;
    row[7] = false;
    check_matrix[0] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_variables);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    row[4] = true;
    row[5] = true;
    row[6] = false;
    row[7] = false;
    check_matrix[1] = &(row[0]);

    row = (bool*) malloc(sizeof(bool) * num_variables);
    row[0] = false;
    row[1] = false;
    row[2] = false;
    row[3] = false;
    row[4] = false;
    row[5] = true;
    row[6] = true;
    row[7] = false;
    check_matrix[2] = &(row[0]);

    ulog("Matrix:");
    print_matrix(num_rows, num_variables, check_matrix);

    // SOLVING THE PROBLEM
    bring_into_rref(num_rows, num_variables, num_rows, num_variables, check_matrix);

    ulog("\nRREF Matrix:");
    print_matrix(num_rows, num_variables, check_matrix);
    //ulog("HERE");

    //initialize solutions: matrix of num_variables rows and num_variables+1 columns
    //first column is solution to inhomogeneous equation
    //remaining columns are a basis of solutions to homogeneous equation

//    int num_sols = solutions_from_rref(num_rows, num_columns, num_variables, matrix, solutions);

    // INFO: we add another column which indicates if the row was already present in the original check matrix
    bool* extended_check_matrix[num_qubits_main];
    for(size_t i=0;i<num_qubits;i++){
    	row = (bool*) malloc(sizeof(bool) * (num_variables));
	extended_check_matrix[i] = &(row[0]);
    }

    //initialise the top part of extended_check_matrix to equal check_matrix; the rest of the rows only contain zeroes
    for(size_t i=0;i<num_rows;i++){
    	for(size_t j=0;j<num_variables;j++){
	    extended_check_matrix[i][j] = check_matrix[i][j];
	}
    }
    for(size_t i=num_rows;i<num_qubits;i++){
    	for(size_t j=0;j<num_variables;j++){
	    extended_check_matrix[i][j] = false;
	}
    }


    extend_rref_check_matrix(num_rows, num_qubits, extended_check_matrix);

    printf("Extended check matrix:\n");
    print_matrix(num_qubits, num_variables, extended_check_matrix);
    
    // cleaning up

    for(size_t i=0;i<num_rows;i++){
	    free(check_matrix[i]);
    }
    for(size_t i=0;i<num_qubits;i++){
	    free(extended_check_matrix[i]);
    }

	return 0;
}
