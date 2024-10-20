#include "utils.h"

void swap(int array[], int i, int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void unsigned_swap(unsigned int array[], unsigned int i, unsigned int j){
    unsigned int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


void print_array(int array[], int length){
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int get_array_length(int sizeofArray, int sizeofType){
    return  sizeofArray / sizeofType;
}