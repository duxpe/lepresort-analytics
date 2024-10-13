#include "leprechaun.h"

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

void bubble_sort(int array[], int length); //TODO: Implementar Bubble Sort

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

void merge_sort(int array[], int left, int right); //TODO: Implementar Merge Sort

void merge_sorted_arrays(int array[], int left, int right, int middle);//TODO: Implementar Merge Sort

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
void and_selection_sort(int array[], int length, TAnalyticsData *anData){
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

void and_bubble_sort(int array[], int length, TAnalyticsData *anData); //TODO: Implementar Bubble Sort com Analytics

void and_insertion_sort(int array[], int length, TAnalyticsData *anData){    
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

void and_merge_sort(int array[], int left, int right, TAnalyticsData *anData); //TODO: Implementar Merge Sort com Analytics

void and_merge_sorted_arrays(int array[], int left, int right, int middle, TAnalyticsData *anData); //TODO: Implementar Merge Sort com Analytics

void and_quick_sort(int array[], int left, int right, TAnalyticsData *anData){
    if(left < right){
        int pivot_index = and_quick_sort_partition(array, left, right, anData);

        and_quick_sort(array, left, pivot_index - 1, anData);
        and_quick_sort(array, pivot_index + 1, right, anData);
    }
}

int and_quick_sort_partition(int array[], int left, int right, TAnalyticsData *anData){
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