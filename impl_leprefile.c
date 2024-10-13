#include "leprefile.h"

FILE* write_dataset_to_csv(T_CSV csv, T_DataSet data_set){
    FILE *file = fopen(strcat(csv.file_name,".csv"),"w");

    if(!file){
        printf("Error while opening dataset %s", csv.file_name);
        return NULL;
    }

    csv.separator[1]='\0';

    for(int l = 0; l < data_set.size; l++){
        char line[MAX_LINE_LENGTH] = "";
        for(int c = 0; c < csv.column_ammount; c++){
            if(l == 0){
                if(csv.has_index){
                    strcat(strcat(line,"index"),csv.separator);
                }
                strcat(strcat(line,csv.column_names[c]),csv.separator);
            }else{
                if(csv.has_index){
                    sprintf(line, "%d", l);
                    strcat(line,csv.separator);
                }
                sprintf(line,"%d",data_set.data[l]);
                strcat(line,csv.separator);
            }
        }
        strcat(line,"\n");
    }

    fclose(file);
}

FILE* load_dataset_from_csv(T_CSV csv, T_DataSet data_set){

}

FILE* write_results_to_csv(T_CSV csv, TAnalyticsData analytics); //TODO: Escrever função que guarda resultados do teste.