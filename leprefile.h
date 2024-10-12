#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "leprechaun.h"

#define MAX_FILE_NAME 4096

struct CSV{
    char file_name[MAX_FILE_NAME];
    char **column_names;
    int column_ammount;
    int line_ammount;
    char separator;
    bool has_index;
};

typedef CSV T_CSV;


FILE* write_csv(T_CSV csv);

FILE* read_csv(T_CSV csv);

FILE* write_dataset_to_csv(T_CSV csv, T_DataSet data_set);

FILE* load_dataset_from_csv(T_CSV csv, T_DataSet data_set);

FILE* write_results_to_csv(T_CSV csv, T_DataSet data_set);