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

void print_test_info(enum Algorithm algorithm, enum TestType test_type){
    switch(algorithm){
        case selection:
            printf("Starting Selection Sort Test. Case: %s.\n", test_type == worstScenario ?
                     "Worst Case" : test_type == avarageScenario ?
                     "Avarage Case": 
                     "Best Case");
            break;
        case bubble:
            printf("Starting Bubble Sort Test. Case: %s.\n", test_type == worstScenario ?
                "Worst Case" : test_type == avarageScenario ?
                "Avarage Case": 
                "Best Case");
        break;
        case insertion:
            printf("Starting Insertion Sort Test. Case: %s.\n", test_type == worstScenario ?
                "Worst Case" : test_type == avarageScenario ?
                "Avarage Case": 
                "Best Case");
        break;
        case merge:
            printf("Starting Merge Sort Test. Case: %s.\n", test_type == worstScenario ?
                "Worst Case" : test_type == avarageScenario ?
                "Avarage Case": 
                "Best Case");
        break;
        case quick:
            printf("Starting Quick Sort Test. Case: %s.\n", test_type == worstScenario ?
                "Worst Case" : test_type == avarageScenario ?
                "Avarage Case": 
                "Best Case");
        break;
    }
}