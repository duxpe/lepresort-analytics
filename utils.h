#include <stdio.h>
#include "enums.h"

void swap(int array[], int i, int j);

void unsigned_swap(unsigned int array[], unsigned int i, unsigned int j);

void print_array(int array[], int length);

int get_array_length(int sizeofArray, int sizeofType);

void print_test_info(enum Algorithm algorithm, enum TestType test_type);