#include "leprefile.h"

FILE* write_dataset_to_csv(T_DataSet data_set, char file_name[], bool has_index, char separator_character){
    char separator[2];

    separator[0] = separator_character;
    separator[1] = '\0';

    FILE *file = fopen(strcat(file_name,".csv"),"w");
    if(!file){
        printf("Error while opening or creating dataset %s", file_name);
        return NULL;
    }

    for(unsigned int l = 0; l < data_set.size+HEADER_INFO; l++){
        char line[MAX_LINE_LENGTH] = "";
        char buffer[100];
        if(l == 0){
            if(has_index){
                strcat(strcat(line,"index"),separator);
            }
            strcat(strcat(line,"data"),separator);
            strcat(line,"\n");
        }
        if(has_index){
            if(l > 1){
            sprintf(buffer,"%u",l-2);
            strcat(line,buffer);
            strcat(line,separator);
            }else{
                strcat(line, l==0? "size" : "seed");
                strcat(line,separator);
            }
        }
        sprintf(buffer,"%u",data_set.data[l]);
        strcat(line,buffer);
        strcat(line,separator);
        
        strcat(line,"\n");
        fprintf(file,"%s",line);
    }

    fclose(file);
}

T_DataSet load_dataset_from_csv(char file_name[]){
    char line[MAX_LINE_LENGTH];
    char extension[] = ".csv";
    unsigned int line_count = 0, size = 0, seed = 0;
    T_DataSet data_set = create_empty_data_set(1);

    if(strstr(file_name,extension) == NULL){
        strcat(file_name,extension);
    }

    FILE *file = fopen(file_name,"r");

    if(!file){
        printf("Error while opening dataset %s", file_name);
        return data_set;
    }

    while(fgets(line, MAX_LINE_LENGTH, file) != NULL){
        char *separator = strchr(line,';');
        if(separator != NULL){
            switch (line_count)
            {
            case 0:
                printf("Lendo Arquivo...\n");
                break;
            case 1:
                size = atoi(separator+1);
                if(size){
                    data_set.size = size;
                    unsigned int *arr = (unsigned int *)malloc((size+HEADER_INFO+10) * sizeof(unsigned int));
                    data_set.data = arr;
                    data_set.data[0] = size;
                }else{
                    printf("Error while reading [%s] - no size found[%u]", file_name,size);
                    return data_set;
                }
                break;
            case 2:
                seed = atoi(separator+1);
                if(size && seed){
                    data_set.data[1] = seed;
                }else{
                    printf("Error while reading [%s] - no seed found[%u]", file_name,seed);
                    return data_set;
                }
                break;
            default:
                unsigned int value = atoi(separator+1);
                data_set.data[line_count-1] = value;
                break;
            }
        }
        line_count++;
    }
    fclose(file);
    return data_set;
}

FILE* write_results_to_csv(T_AnalyticsData anData, char file_name[], char separator_character){
    char separator[2];
    char extension[] = ".csv";
    separator[0] = separator_character;
    separator[1] = '\0';
    
    if(strstr(file_name,extension) == NULL){
        strcat(file_name,extension);
    }

    FILE *file = fopen(file_name,"w");
    if(!file){
        printf("Error while opening or creating results file %s", file_name);
        return NULL;
    }
        char header[MAX_LINE_LENGTH] = "";
        char line[MAX_LINE_LENGTH] = "";
        char buffer[MAX_LINE_LENGTH];
        strcat(strcat(header,"algorithm"),separator);
        strcat(strcat(header,"test_type"),separator);
        strcat(strcat(header,"comparisons"),separator);
        strcat(strcat(header,"swaps"),separator);
        strcat(strcat(header,"avarage_time"),separator);
        strcat(strcat(header,"time_1"),separator);
        strcat(strcat(header,"time_2"),separator);
        strcat(strcat(header,"time_3"),separator);
        strcat(header,"\n");
        sprintf(buffer,"%u",anData.algorithm);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%u",anData.test_type);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%llu",anData.comparisonCount);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%llu",anData.swapCount);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%lf",anData.completionTime.avarage_result);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%lf",anData.completionTime.results[0]);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%lf",anData.completionTime.results[1]);
        strcat(line,buffer);
        strcat(line,separator);

        sprintf(buffer,"%lf",anData.completionTime.results[2]);
        strcat(line,buffer);
        strcat(line,separator);
        strcat(line,"\n");
        fprintf(file,"%s",header);
        fprintf(file,"%s",line);

    fclose(file);
}