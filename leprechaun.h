#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#define HEADER_INFO 2

struct TimeTest{
    int first_result;
    int second_result;
    int third_result;
    int avarage_result;
};

typedef struct TimeTest T_TimeTest;

struct AnalyticsData {
    int comparisonCount;
    int swapCount;
    T_TimeTest completionTime;
};

typedef struct AnalyticsData TAnalyticsData;

struct DataSet {
    int size;
    unsigned int *data;
    bool is_ordered;
    bool is_desc;
};

typedef struct DataSet T_DataSet;

//DataSet Creation
T_DataSet create_filled_data_set(int size, int seed);

T_DataSet create_empty_data_set(int size);


//DataSet Operations
void copy_data_set(T_DataSet source, T_DataSet destination);

void reverse_data_set(T_DataSet data_set);

void shuffle_data_set(T_DataSet data_set);


//Sort Algorithms without analytics
void selection_sort(int array[], int length);

void bubble_sort(int array[], int length);

void insertion_sort(int array[], int length);

void merge_sort(int array[], int left, int right);

void merge_sorted_arrays(int array[], int left, int right, int middle);

void quick_sort(int array[], int left, int right);

int quick_sort_partition(int array[], int left, int right);


//Sort Algorithms w/ analytics
void and_selection_sort(int array[], int length, TAnalyticsData *anData);

void and_bubble_sort(int array[], int length, TAnalyticsData *anData);

void and_insertion_sort(int array[], int length, TAnalyticsData *anData);

void and_merge_sort(int array[], int left, int right, TAnalyticsData *anData);

void and_merge_sorted_arrays(int array[], int left, int right, int middle, TAnalyticsData *anData);

void and_quick_sort(int array[], int left, int right, TAnalyticsData *anData);

int and_quick_sort_partition(int array[], int left, int right, TAnalyticsData *anData);

