#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#define HEADER_INFO 2

#define TEST_SAMPLE_QTT 3

enum Algorithm {
    selection,
    bubble,
    insertion,
    merge,
    quick,
    algorithm_size //Sempre manter algorithm_size como último enum
};

enum TestType {
    bestScenario,
    avarageScenario,
    worstScenario,
    test_type_size //Sempre manter test_type_size como último enum
};

struct TimeTest{
    int results[TEST_SAMPLE_QTT];
    int avarage_result;
};

typedef struct TimeTest T_TimeTest;

struct AnalyticsData {
    enum Algorithm algorithm;
    enum TestType test_type;
    int comparisonCount;
    int swapCount;
    T_TimeTest completionTime;
};

typedef struct AnalyticsData T_AnalyticsData;

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

//Test Wrapper Functions
T_AnalyticsData run_test_case(T_DataSet data_set, enum Algorithm algorithm, enum TestType test_type);

void run_all_test_cases(T_DataSet data_set, T_AnalyticsData analytics[algorithm_size][test_type_size]);


//Sort Algorithms without analytics
void selection_sort(int array[], int length);

void bubble_sort(int array[], int length);

void insertion_sort(int array[], int length);

void merge_sort(int array[], int left, int right);

void merge_sorted_arrays(int array[], int left, int right, int middle);

void quick_sort(int array[], int left, int right);

int quick_sort_partition(int array[], int left, int right);


//Sort Algorithms w/ analytics
void and_selection_sort(int array[], int length, T_AnalyticsData *anData);

void and_bubble_sort(int array[], int length, T_AnalyticsData *anData);

void and_insertion_sort(int array[], int length, T_AnalyticsData *anData);

void and_merge_sort(int array[], int left, int right, T_AnalyticsData *anData);

void and_merge_sorted_arrays(int array[], int left, int right, int middle, T_AnalyticsData *anData);

void and_quick_sort(int array[], int left, int right, T_AnalyticsData *anData);

int and_quick_sort_partition(int array[], int left, int right, T_AnalyticsData *anData);

