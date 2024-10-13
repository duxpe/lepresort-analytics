#include "leprefile.h"

FILE* write_dataset_to_csv(T_CSV csv, T_DataSet data_set){
    FILE *file = fopen(strcat(csv.file_name,".csv"),"w");

    if(!file){
        printf("Error while opening dataset %s", csv.file_name);
        return NULL;
    }

    for(int l = -1; l < data_set.size; l++){
        char line[MAX_LINE_LENGTH] = "";
        for(int c = 0; c < csv.column_ammount; c++){
            char buffer[100];
            if(l == -1){
                if(csv.has_index){
                    strcat(strcat(line,"index"),csv.separator);
                }
                strcat(strcat(line,csv.column_names[c]),csv.separator);
            }else{
                if(csv.has_index){
                    sprintf(buffer,"%d",l);
                    strcat(line,buffer);
                    strcat(line,csv.separator);
                }
                sprintf(buffer,"%d",data_set.data[l]);
                strcat(line,buffer);
                strcat(line,csv.separator);
            }
        }
        strcat(line,"\n");
        fprintf(file,"%s",line);

    }

    fclose(file);
}


// int split_csv_line(char *line, char *columns[], int max_columns) {
//     int count = 0;
//     char *token = strtok(line, ";");
//     while (token != NULL && count < max_columns) {
//         columns[count++] = token;
//         token = strtok(NULL, ";");
//     }
//     return count;  // Return number of columns found
// }


FILE* load_dataset_from_csv(T_CSV csv, T_DataSet data_set){
    // FILE *file = fopen(strcat(csv.file_name,".csv"),"r");

    // if(!file){
    //     printf("Error while opening dataset %s", csv.file_name);
    //     return NULL;
    // }

    // char line[MAX_LINE_LENGTH];
    // char *columns[100];
    // int line_count = 0;
    // int column_count = 0;
    // printf("ya");
    // int array[10000];
    // printf("yb");
    // int index_index = 0;
    
    // while(fgets(line, sizeof(line), file) != NULL){
    //     int current_column = -1;
        
    //     line[strcspn(line, "\n")] = 0;
    //     printf("ye");
    //     char *token = strtok(line,csv.separator);
    //     while(token != NULL){
    //         current_column++;
    //         if(line_count == 0){
    //             if(token == "index"){
    //                 csv.has_index = true;
    //                 index_index = current_column;
    //             }
    //             column_count++;
    //             strcpy(csv.column_names[column_count], token);
    //         }else{
    //             if(current_column != index_index) array[line_count-1] = atoi(token);
    //             data_set.size++;
    //         }
    //         line_count++;
    //         token = strtok(NULL, csv.separator);
    //         printf("yo");
    //     }
    // }
    //     data_set.data = array;
    //     csv.column_ammount = column_count;
    //     csv.line_ammount = line_count;
    //     printf("i reached here\n");
    //     print_array(data_set.data,data_set.size);

}

FILE* write_results_to_csv(T_CSV csv, TAnalyticsData analytics); //TODO: Escrever função que guarda resultados do teste.