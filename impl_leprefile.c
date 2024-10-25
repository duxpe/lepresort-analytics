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

    for(unsigned int l = 0; l < data_set.size; l++){
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
                printf("Reading file...");
                break;
            case 1:
                size = atoi(separator+1);
                if(size){
                    data_set.size = size+HEADER_INFO;
                    unsigned int *arr = (unsigned int *)malloc((size+HEADER_INFO+5) * sizeof(unsigned int));
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
    return data_set;
}

// FILE* write_results_to_csv(T_AnalyticsData analytics); //TODO: Escrever função que guarda resultados do teste.