#include "leprechaun.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILE_NAME 4096
#define MAX_LINE_LENGTH 1024

struct CSV {
    char *file_name;
    char column_names[100][MAX_LINE_LENGTH];
    int column_ammount;
    int line_ammount;
    char *separator;
    bool has_index;
};

typedef struct CSV T_CSV;

FILE* write_dataset_to_csv(T_CSV csv, T_DataSet data_set);

FILE* load_dataset_from_csv(T_CSV csv, T_DataSet data_set);

FILE* write_results_to_csv(T_CSV csv, TAnalyticsData analytics);