#include "leprechaun.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILE_NAME 4096
#define MAX_LINE_LENGTH 1024


FILE* write_dataset_to_csv(T_DataSet data_set, char file_name[], bool has_index, char separator_character);

T_DataSet load_dataset_from_csv(char file_name[]);

FILE* write_results_to_csv(T_AnalyticsData anData, char file_name[], char separator_character);
