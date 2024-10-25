#include "leprefile.h"
#include <stdio.h>

void main(){
    T_DataSet dataset = create_filled_data_set(1000000,0);
    T_AnalyticsData analytics[algorithm_size][test_type_size];

    run_all_test_cases(dataset, analytics);

    // //create_filled_data_set recebe: -Tamanho do data_set
    // //                               -Seed(se for 0, um valor aletório é
    // //                                     escolhido, se for definido o 
    // //                                     resultado é sempre igual);   
    // T_DataSet original_data_set = create_filled_data_set(1000000,0);

    // //create_empty_data_set recebe: -Tamaho do data_set(apenas aloca memória)
    // T_DataSet first_copy = create_empty_data_set(1000000);
    // T_DataSet second_copy = create_empty_data_set(1000000);

    // //copy_data_set recebe: -data_set de origem
    // //                      -data_set de destino
    // //nota: ele copia todos os outros atributos do data_set, não apenas o data;
    // copy_data_set(original_data_set, first_copy);
    // copy_data_set(original_data_set, second_copy);

    // //reverse_data_set recebe: -data_set para performar o reverse
    // //nota: Inverte a array data e marca ou desmarcar os is_desc;
    // reverse_data_set(first_copy);

    // //shuffle_data_set recebe: -data_set para performar o embaralhamento
    // //nota: Ele pega a seed salva na array data do data_set e usa ela para
    // //      embaralhar. Por tanto o resultado é reproduzível.
    // shuffle_data_set(second_copy);

    // char file_name[MAX_FILE_NAME] = "teste_file";

    // //write_dataset_to_csv recebe: -data_set que será salvo
    // //                             -string com nome do arquivo
    // //                             -boolean(has_index), para definir se vai
    // //                              ou não salvar com index.
    // //                             -char separador
    // write_dataset_to_csv(first_copy,file_name,true,';');


    // //load_dataset_from_csv recebe: -nome do arquivo
    // //nota: Caso não seja encontrado, retorna um data_set vazio de tamanho 1;
    // T_DataSet data_set_read = load_dataset_from_csv(file_name);

    // print_array(data_set_read.data, data_set_read.size);
    // printf("size=%d, seed=%u",data_set_read.size, data_set_read.data[1]);

    // char file_name2[MAX_FILE_NAME] = "teste_file2";
    // write_dataset_to_csv(data_set_read,file_name2,true,';');
}