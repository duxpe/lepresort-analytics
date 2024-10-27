#include "leprefile.h"
#include <string.h>
#include <time.h>

//DataSet Creation
T_DataSet create_filled_data_set (int size, int seed){
    unsigned int *arr = (unsigned int *)malloc(
        (size+HEADER_INFO+10) * sizeof(unsigned int));

    if(arr == NULL){
        perror("Memory allocation failed :(");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    arr[0] = size;
    arr[1] = seed == 0? (10 + rand()%12345) : seed;
    for (unsigned int i = HEADER_INFO; i < size+HEADER_INFO; i++){
        arr[i]=arr[i-1]+((arr[1]/100))+1;
    }

    T_DataSet data_set;
    data_set.size = size;
    data_set.data = arr;
    data_set.is_ordered = true;
    data_set.is_desc = false;
    return data_set;
}

T_DataSet create_empty_data_set(int size){
    unsigned int *arr = (unsigned int *)malloc(
        (size+HEADER_INFO+10) * sizeof(unsigned int));
    T_DataSet data_set;
    data_set.size = size;
    data_set.data = arr;
    data_set.is_ordered = true;
    data_set.is_desc = false;
    return data_set;
}


//DataSet Operations
void copy_data_set(T_DataSet source, T_DataSet destination){
    memcpy(destination.data, source.data, 
    ((source.size+HEADER_INFO+10) * sizeof(unsigned int)));

    destination.size = source.size;
    destination.is_ordered = source.is_ordered;
    destination.is_desc = source.is_desc;
}

void reverse_data_set(T_DataSet data_set){
    unsigned int left = HEADER_INFO, right = data_set.size+HEADER_INFO-1;
    data_set.is_desc = !data_set.is_desc;
    while(right > left){
    unsigned_swap(data_set.data, left, right);
    left+=1;
    right-=1;
    }
}

void shuffle_data_set(T_DataSet data_set){
    unsigned int seed = data_set.data[1];
    unsigned int start = HEADER_INFO, end = data_set.size+HEADER_INFO-1;
    unsigned int iterations = 0, limit = data_set.size*3;
    srand(seed);
    data_set.is_desc = false;
    data_set.is_ordered = false;
    unsigned_swap(data_set.data, start, end);
    while(iterations < limit){
        end -= (rand()%((10+iterations)/(data_set.size+HEADER_INFO/10)+1))+1;
        start += (rand()%((10+iterations)/(data_set.size+HEADER_INFO/10)+1))+1;
        if (end < (data_set.size+HEADER_INFO)/2+1) end = data_set.size+HEADER_INFO-1;
        if (start > (data_set.size+HEADER_INFO)/2-1) start = HEADER_INFO;
        unsigned_swap(data_set.data, start, end);
        iterations++;
    }
}

double get_avarage_time(double results[]){
    double avarage = 0;
    for(int i = 0; i < TEST_SAMPLE_QTT; i++){
        avarage += results[i];
    }
    return avarage/(TEST_SAMPLE_QTT*1.0);
}

//Test Wrapper Functions
T_AnalyticsData run_test_case(T_DataSet data_set, enum Algorithm algorithm, enum TestType test_type){
    T_AnalyticsData analytics;
    analytics.algorithm = algorithm;
    analytics.test_type = test_type;
    analytics.swapCount = 0;
    analytics.comparisonCount = 0;
    analytics.completionTime.avarage_result = 0;

    for(int i = 0; i < TEST_SAMPLE_QTT+1; i++){
        T_DataSet new_data = create_empty_data_set(data_set.size);

        copy_data_set(data_set, new_data);
        switch(test_type){
            case avarageScenario:
                shuffle_data_set(new_data);
            break;
            case worstScenario:
                reverse_data_set(new_data);
            break;
            default:
                if(new_data.is_ordered && new_data.is_desc){
                    printf("Data set was reverse... lets undo that!");
                    reverse_data_set(new_data);
                }
            break;
        }
        clock_t start, duration;
        if(i < TEST_SAMPLE_QTT ){
            print_test_info(algorithm, test_type);
            switch(algorithm){
                case selection:
                    start = clock();
                    selection_sort(new_data.data, new_data.size+HEADER_INFO);
                break;
                case bubble:
                    start = clock();
                    bubble_sort(new_data.data, new_data.size+HEADER_INFO);
                break;
                case insertion:
                    start = clock();
                    insertion_sort(new_data.data, new_data.size+HEADER_INFO);
                break;
                case merge:
                    start = clock();
                    merge_sort(new_data.data, HEADER_INFO, new_data.size+HEADER_INFO-1);
                break;
                case quick:
                    start = clock();
                    quick_sort(new_data.data, HEADER_INFO, new_data.size+HEADER_INFO);
                break;
                default:
                break;
            }
            duration = clock();
            analytics.completionTime.results[i] = ((double) (duration - start) / CLOCKS_PER_SEC);
        }else{
            analytics.completionTime.avarage_result = get_avarage_time(analytics.completionTime.results);
            print_test_info(algorithm, test_type);
            switch(algorithm){
                case selection:
                    and_selection_sort(new_data.data,new_data.size+HEADER_INFO,&analytics);
                break;
                case bubble:
                    and_bubble_sort(new_data.data, new_data.size+HEADER_INFO,&analytics);
                break;
                case insertion:
                    and_insertion_sort(new_data.data, new_data.size+HEADER_INFO,&analytics);
                break;
                case merge:
                    and_merge_sort(new_data.data, HEADER_INFO, new_data.size+HEADER_INFO-1,&analytics);
                break;
                case quick:
                    and_quick_sort(new_data.data, HEADER_INFO, new_data.size+HEADER_INFO-1,&analytics);
                break;
                default:
                break;
            }
            
        }
        free(new_data.data);
    }
        char result_file_name[MAX_FILE_NAME];
        sprintf(result_file_name,"gold_pot_%d_results_%d_%d.csv",data_set.size,algorithm,test_type);
        write_results_to_csv(analytics,result_file_name,';');
        sprintf(result_file_name,"             ");
        return analytics;
}

void run_all_test_cases(T_DataSet data_set, T_AnalyticsData analytics[algorithm_size][test_type_size]){
    for (int algorithms = 0; algorithms < algorithm_size; algorithms++){
        for(int scenarios = 0; scenarios < test_type_size; scenarios++){
            switch(algorithms){
                case selection:
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
        }
    }
}


//Sort Algorithms without analytics
void selection_sort(int array[], int length){
    for(int i = HEADER_INFO; i<length-1; i++){
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
    
    for(i = HEADER_INFO; i < length; i++){
        for(j = HEADER_INFO; j < length - 1 - i; j++){
            if(array[j] > array[j + 1]){
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}

void insertion_sort(int array[], int length){    
    for(int i = HEADER_INFO+1; i<length; i++){
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
    if(left < right){
        int middle = left + (right - left) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);
        merge_sorted_arrays(array, left, right, middle);
    }
}

void merge_sorted_arrays(int arr[], int left, int right, int mid){
    int left_lenght = mid - left + 1;
    int right_length = right - mid;

    int left_temp[left_lenght], right_temp[right_length];

    for (int i = 0; i < left_lenght; i++){
        left_temp[i] = arr[left + i];
    }

    for (int j = 0; j < right_length; j++){
        right_temp[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < left_lenght && j < right_length) {
        if (left_temp[i] <= right_temp[j]) {
            arr[k] = left_temp[i];
            i++;
        } else {
            arr[k] = right_temp[j];
            j++;
        }
        k++;
    }

    while (i < left_lenght) {
        arr[k] = left_temp[i];
        i++;
        k++;
    }

    while (j < right_length) {
        arr[k] = right_temp[j];
        j++;
        k++;
    }
}

void quick_sort(int array[], unsigned int left, unsigned int right){
    if(left < right){
        unsigned int pivot_index = quick_sort_partition(array, left, right);
        quick_sort(array, left, pivot_index - 1);
        quick_sort(array, pivot_index + 1, right);
    }
}

unsigned int quick_sort_partition(int array[], unsigned int left, unsigned int right){
    unsigned int pivot_index = left + (right - left) / 2;
    unsigned_swap(array, pivot_index, right);

    unsigned int pivot_value = array[right];
    unsigned int index = left;

    for(int j = left; j < right; j++){
        if(array[j] <= pivot_value){
            unsigned_swap(array,j,index);
            index++;
        }
    }
    unsigned_swap(array, index, right);
    return index;
}


//Sort Algorithms w/ analytics
void and_selection_sort(int array[], int length, T_AnalyticsData *anData){
    for(int i = HEADER_INFO; i<length-1; i++){
        int smallest_position = i;
        for(int j = i+1; j < length; j++){
            anData->comparisonCount+=1;
            if(array[j] < array[smallest_position]){
                smallest_position = j;
            }
        }
        if(smallest_position != i){
            swap(array,smallest_position, i);
            anData->swapCount+=1;
        }
    }
}

void and_bubble_sort(int array[], int length, T_AnalyticsData *anData){
    int i, j, aux;
    for(i = HEADER_INFO; i < length; i++){
        bool swapped = false;
        for(j = HEADER_INFO; j < length - 1 - i; j++){
            anData->comparisonCount+=1;
            if(array[j] > array[j + 1]){
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                anData->swapCount++;
            }
        }
    }
}

void and_insertion_sort(int array[], int length, T_AnalyticsData *anData){    
    for(int i = HEADER_INFO+1; i<length; i++){
        int current = array[i];
        int j = i-1;
        
        anData->comparisonCount+=1;
        while(j>=0 && array[j] > current){
            array[j+1] = array[j];
            j--;
            anData->swapCount++;
        }
        array[j+1] = current;
    }

}

void and_merge_sorted_arrays(int arr[], int left, int right, int mid, T_AnalyticsData *anData) {
    int left_lenght = mid - left + 1;
    int right_length = right - mid;

    int left_temp[left_lenght], right_temp[right_length];

    for (int i = 0; i < left_lenght; i++){
        left_temp[i] = arr[left + i];
        anData->swapCount+=1;
    }

    for (int j = 0; j < right_length; j++){
        right_temp[j] = arr[mid + 1 + j];
        anData->swapCount+=1;
    }

    int i = 0, j = 0, k = left;
    while (i < left_lenght && j < right_length) {
        anData->comparisonCount+=1;
        if (left_temp[i] <= right_temp[j]) {
            arr[k] = left_temp[i];
            i++;
            anData->swapCount+=1;
        } else {
            arr[k] = right_temp[j];
            j++;
            anData->swapCount+=1;
        }
        k++;
    }

    while (i < left_lenght) {
        arr[k] = left_temp[i];
        i++;
        k++;
        anData->swapCount+=1;
    }

    while (j < right_length) {
        arr[k] = right_temp[j];
        j++;
        k++;
        anData->swapCount+=1;
    }
}

void and_merge_sort(int arr[], int left, int right, T_AnalyticsData *anData) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        and_merge_sort(arr, left, mid, anData);
        and_merge_sort(arr, mid + 1, right, anData);
        and_merge_sorted_arrays(arr, left, right, mid, anData);
    }
}

void and_quick_sort(int array[], unsigned int left, unsigned int right, T_AnalyticsData *anData){
    if(left < right){
        unsigned int pivot_index = and_quick_sort_partition(array, left, right, anData);

        and_quick_sort(array, left, pivot_index - 1, anData);
        and_quick_sort(array, pivot_index + 1, right, anData);
    }
}

unsigned int and_quick_sort_partition(int array[], unsigned int left, unsigned int right, T_AnalyticsData *anData){
    unsigned int pivot_index = left + (right - left) / 2;
    unsigned_swap(array, pivot_index, right);
    anData->swapCount++;

    unsigned int pivot_value = array[right];
    unsigned int index = left;

    for(int j = left; j < right; j++){
        anData->comparisonCount++;
        if(array[j] <= pivot_value){
            unsigned_swap(array,j,index);
            anData->swapCount++;
            index++;
        }
    }
    unsigned_swap(array, index, right);
    anData->swapCount++;
    return index;
}