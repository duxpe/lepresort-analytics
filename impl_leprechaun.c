#include "leprechaun.h"
#include <string.h>
#include <time.h>

//DataSet Creation
T_DataSet create_filled_data_set (int size, int seed){
    unsigned int *arr = (unsigned int *)malloc(
        (size+HEADER_INFO) * sizeof(unsigned int));

    if(arr == NULL){
        perror("Memory allocation failed :(");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    arr[0] = size;
    arr[1] = seed == 0? (10 + rand()%12345) : seed;
    for (unsigned int i = HEADER_INFO; i <= size+HEADER_INFO; i++){
        arr[i]=arr[i-1]+((arr[1]/100))+1;
    }

    T_DataSet data_set;
    data_set.size = size+HEADER_INFO;
    data_set.data = arr;
    data_set.is_ordered = true;
    data_set.is_desc = false;
    return data_set;
}

T_DataSet create_empty_data_set(int size){
    unsigned int *arr = (unsigned int *)malloc(
        (size+HEADER_INFO+5) * sizeof(unsigned int));
    T_DataSet data_set;
    data_set.size = size+HEADER_INFO;
    data_set.data = arr;
    data_set.is_ordered = true;
    data_set.is_desc = false;
    return data_set;
}


//DataSet Operations
void copy_data_set(T_DataSet source, T_DataSet destination){
    memcpy(destination.data, source.data, 
    ((source.size+HEADER_INFO) * sizeof(unsigned int)));

    destination.size = source.size;
    destination.is_ordered = source.is_ordered;
    destination.is_desc = source.is_desc;
}

void reverse_data_set(T_DataSet data_set){
    unsigned int left = HEADER_INFO, right = data_set.size-1;
    data_set.is_desc = !data_set.is_desc;
    while(right > left){
    unsigned_swap(data_set.data, left, right);
    left+=1;
    right-=1;
    }
}

void shuffle_data_set(T_DataSet data_set){
    unsigned int seed = data_set.data[1];
    unsigned int start = HEADER_INFO, end = data_set.size-1;
    unsigned int iterations = 0, limit = data_set.size*2;
    srand(seed);
    data_set.is_desc = false;
    data_set.is_ordered = false;

    while(iterations < limit){
        if (end < data_set.size/2+1) end = data_set.size-1;
        if (start > data_set.size/2-1) start = HEADER_INFO;
        end -= rand()%(10+iterations/(data_set.size/10));
        unsigned_swap(data_set.data, start, end);
        start += rand()%(10+iterations/(data_set.size/10));
        iterations++;
    }
}

int get_avarage_time(int results[]){
    int avarage = 0;
    for(int i = 0; i < TEST_SAMPLE_QTT; i++){
        avarage += results[i];
    }
    return avarage/TEST_SAMPLE_QTT;
}

//Test Wrapper Functions
T_AnalyticsData run_test_case(T_DataSet data_set, enum Algorithm algorithm, enum TestType test_type){
    T_AnalyticsData analytics;
    analytics.algorithm = algorithm;
    analytics.test_type = test_type;
    printf("93\n");
    for(int i = 0; i < TEST_SAMPLE_QTT+1; i++){
        T_DataSet new_data = create_empty_data_set(data_set.size);
        copy_data_set(data_set, new_data);
        printf("97\n");
        switch(test_type){
            case avarageScenario:
                printf("100\n");
                shuffle_data_set(new_data);
            break;
            case worstScenario:
                printf("104\n");
                reverse_data_set(new_data);
            break;
            default:
            break;
        }
        printf("107\n");
        clock_t start, duration;
        if(i < TEST_SAMPLE_QTT ){
            switch(algorithm){
                case selection:
                    start = clock();
                    selection_sort(new_data.data, new_data.size);
                break;
                case bubble:
                    start = clock();
                    bubble_sort(new_data.data, new_data.size);
                break;
                case insertion:
                    start = clock();
                    insertion_sort(new_data.data, new_data.size);
                break;
                case merge:
                    start = clock();
                    merge_sort(new_data.data, 0, new_data.size);
                break;
                case quick:
                    start = clock();
                    quick_sort(new_data.data, 0, new_data.size);
                break;
            }
            duration = clock() - start;
            analytics.completionTime.results[i] = duration * 1000 / CLOCKS_PER_SEC;
        }else{
            analytics.completionTime.avarage_result = get_avarage_time(analytics.completionTime.results);
            switch(algorithm){
                case selection:
                    and_selection_sort(new_data.data,new_data.size,&analytics);
                break;
                case bubble:
                    and_bubble_sort(new_data.data, new_data.size,&analytics);
                break;
                case insertion:
                    and_insertion_sort(new_data.data, new_data.size,&analytics);
                break;
                case merge:
                    and_merge_sort(new_data.data, 0, new_data.size,&analytics);
                break;
                case quick:
                    and_quick_sort(new_data.data, 0, new_data.size,&analytics);
                break;
            }
            
        }
        free(new_data.data);
    }
    return analytics;
}

void run_all_test_cases(T_DataSet data_set, T_AnalyticsData analytics[algorithm_size][test_type_size]){
    for (int algorithms = 0; algorithms < algorithm_size; algorithms++){
        for(int scenarios = 0; scenarios < test_type_size; scenarios++){
            printf("+start a: %d, t: %d \n", algorithms, scenarios);
            switch(algorithms){
                case selection:
                    printf("164\n");
                    analytics[algorithms][scenarios] = run_test_case(data_set, selection, scenarios);
                break;
                case bubble:
                    analytics[algorithms][scenarios] = run_test_case(data_set, bubble, scenarios);
                break;
                case insertion:
                    analytics[algorithms][scenarios] = run_test_case(data_set, insertion, scenarios);
                break;
                case merge:
                    analytics[algorithms][scenarios] = run_test_case(data_set, merge, scenarios);

                break;
                case quick:
                    analytics[algorithms][scenarios] = run_test_case(data_set, quick, scenarios);
                break;
            }
            printf("+done a: %d, t: %d \n", algorithms, scenarios);
            printf("analytics comp: %d, swap: %d, time: %d \n \n", analytics[algorithms][scenarios].comparisonCount, analytics[algorithms][scenarios].swapCount, analytics[algorithms][scenarios].completionTime.avarage_result);
        }
    }
}


//Sort Algorithms without analytics
void selection_sort(int array[], int length){
    for(int i = 0; i<length-1; i++){
        int smallest_position = i;
        
        for(int j = i+1; j < length; j++){
            if(array[j] < array[i]){
                smallest_position = j;
            }
        }
        if(smallest_position != i){
            int temp = array[smallest_position];
            array[smallest_position] = array[i];
            array[i] = temp;
        }
    }
}

void bubble_sort(int array[], int length){
    int i, j, aux;
    
    for(i = 0; i < length; i++){
        for(j = 0; j < length - 1; j++){
            if(array[j] > array[j + 1]){
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}

void insertion_sort(int array[], int length){    
    for(int i = 1; i<length; i++){
        int current = array[i];
        int j = i-1;

        while(j>=0 && array[j] > current){
            array[j+1] = array[j];
            j--; 
        }
        array[j+1] = current;
    }

}

void merge_sort(int array[], int left, int right){
    int middle;
    if(left < right){
        middle = (left + right) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);
        merge_sorted_arrays(array, left, right, middle);
    }
}

void merge_sorted_arrays(int array[], int left, int right, int middle){
    int free_pos, start_file1, start_file2, index;
    int aux_file[INT_MAX];
    start_file1 = left;
    start_file2 = middle + 1;
    free_pos = left;

    while (start_file1 <= middle && start_file2 <= right){
        if(array[start_file1] <= array[start_file2]){
            aux_file[free_pos] = array[start_file1];
            start_file1++;
        }else{
            aux_file[free_pos] = array[start_file1];
            start_file2++;
        }
        free_pos++;
    }
    for(index = start_file1; index <= middle; index++, free_pos++){
        aux_file[free_pos] = array[index];
    }
    for(index = start_file2; index <= left; index++, free_pos++){
        aux_file[free_pos] = array[index];
    }
    for(index = left; index <= right; index++){
        array[index] = aux_file[index];
    }
    
}

void quick_sort(int array[], int left, int right){
    if(left < right){
        int pivot_index = quick_sort_partition(array, left, right);

        quick_sort(array, left, pivot_index - 1);
        quick_sort(array, pivot_index + 1, right);
    }
}

int quick_sort_partition(int array[], int left, int right){
    int pivot_index = left + (right - left) / 2;
    swap(array, pivot_index, right);

    int pivot_value = array[right];
    int index = left;

    for(int j = left; j < right; j++){
        if(array[j] <= pivot_value){
            swap(array,j,index);
            index++;
        }
    }
    swap(array, index, right);
    return index;
}


//Sort Algorithms w/ analytics
void and_selection_sort(int array[], int length, T_AnalyticsData *anData){
    for(int i = 0; i<length-1; i++){
        int smallest_position = i;
        
        for(int j = i+1; j < length; j++){
            anData->comparisonCount++;
            if(array[j] < array[i]){
                smallest_position = j;
            }
        }
        if(smallest_position != i){
            swap(array,smallest_position, i);
            anData->swapCount++;
        }
    }
}

void and_bubble_sort(int array[], int length, T_AnalyticsData *anData){
        int i, j, aux;
    
    for(i = 0; i < length; i++){
        anData->comparisonCount++;
        for(j = 0; j < length - 1; j++){
            anData->comparisonCount++;
            if(array[j] > array[j + 1]){
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                anData->swapCount++;
                anData->comparisonCount++;
            }
        }
    }
}

void and_insertion_sort(int array[], int length, T_AnalyticsData *anData){    
    for(int i = 1; i<length; i++){
        int current = array[i];
        int j = i-1;

        anData->comparisonCount++;
        while(j>=0 && array[j] > current){
            array[j+1] = array[j];
            j--;
            anData->comparisonCount++;
            anData->swapCount++;
        }
        array[j+1] = current;
        anData->swapCount++;
    }

}

void and_merge_sort(int array[], int left, int right, T_AnalyticsData *anData){
        int middle;
    if(left < right){
        anData->swapCount++;
        middle = (left + right) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);
        merge_sorted_arrays(array, left, right, middle);
    }
}

void and_merge_sorted_arrays(int array[], int left, int right, int middle, T_AnalyticsData *anData){
        int free_pos, start_file1, start_file2, index;
    int aux_file[INT_MAX];
    start_file1 = left;
    start_file2 = middle + 1;
    free_pos = left;

    while (start_file1 <= middle && start_file2 <= right){
        if(array[start_file1] <= array[start_file2]){
            aux_file[free_pos] = array[start_file1];
            start_file1++;
            anData->comparisonCount++;
            anData->swapCount++;
        }else{
            aux_file[free_pos] = array[start_file1];
            start_file2++;
            anData->comparisonCount++;
            anData->swapCount++;
        }
        free_pos++;
    }
    for(index = start_file1; index <= middle; index++, free_pos++){
        aux_file[free_pos] = array[index];
        anData->comparisonCount++;
    }
    for(index = start_file2; index <= left; index++, free_pos++){
        aux_file[free_pos] = array[index];
        anData->comparisonCount++;
    }
    for(index = left; index <= right; index++){
        array[index] = aux_file[index];
        anData->comparisonCount++;
    }
}

void and_quick_sort(int array[], int left, int right, T_AnalyticsData *anData){
    if(left < right){
        int pivot_index = and_quick_sort_partition(array, left, right, anData);

        and_quick_sort(array, left, pivot_index - 1, anData);
        and_quick_sort(array, pivot_index + 1, right, anData);
    }
}

int and_quick_sort_partition(int array[], int left, int right, T_AnalyticsData *anData){
    int pivot_index = left + (right - left) / 2;
    swap(array, pivot_index, right);
    anData->swapCount++;

    int pivot_value = array[right];
    int index = left;

    for(int j = left; j < right; j++){
        anData->comparisonCount++;
        if(array[j] <= pivot_value){
            swap(array,j,index);
            anData->swapCount++;
            index++;
        }
    }
    swap(array, index, right);
    anData->swapCount++;
    return index;
}