#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

struct AnalyticsData {
    int comparisonCount;
    int swapCount;
    int completionTime;
};

typedef struct AnalyticsData TAnalyticsData;

struct DataSet {
    int size;
    int *data;
    bool ordered;
    bool is_desc;
};

typedef struct DataSet T_DataSet;

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