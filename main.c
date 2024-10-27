#include "leprefile.h"
#include <stdio.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main(){
    int menu_screen1 = 0, menu_screen2 = 0, menu_screen3 = 0;
    int size = 0, seed = 0;
    char file_name_input[MAX_FILE_NAME];

    printf("\t\tWELCOME TO THE LEPRESORT!\n");
    puts(
        "                                   .-----.   ()()\n"
        "                                  /       \\ .'() \n"
        "                                  |__...__|/     \n"
        "                                  |_....._|      \n"
        "                                .-'  ___  '-.    \n"
        "                                \\_.-`. .`-._/    \n"
        "          __ .--. _              (|\\ (_) /|)     \n"
        "       .-;.-\"-.-;`_;-,            ( \\_=_/ )      \n"
        "     .(_( `)-;___),-;_),          _(_   _)_      \n"
        "    (.( `\\.-._)-.(   ). )       /` ||'-'|| `\\    \n"
        "  ,(_`'--;.__\\  _).;--'`_)  _  /_/ (_>o<_) \\_\\   \n"
        " // )`--..__ ``` _( o )'(';,)\\_//| || : || |\\\\   \n"
        " \\;'        `````  `\\\\   '.\\\\--' |`\"\"\"\"\"\"\"`|//   \n"
        " /                   ':.___//     \\___,___/\\_(   \n"
        "|                      '---'|      |__|__|       \n"
        ";                           ;      ;\"\"|\"\";       \n"
        " \\                         /       [] | []       \n"
        "  '.                     .'      .'  / \\  '.     \n"
        " jgs'-,.__         __.,-'        `--'   `--'     \n"
        "     (___/``````````\\___)                         \n"
    );
    printf("Vamos simular potes de ouro para os leprechauns contarem!\n");
    printf("Cada pote de ouro terá seu tesouro ordenado em 3 casos...!\n");
    printf("O melhor caso, onde todo o tesouro já está ordenado, ");
    printf("do menor valor para o maior\n");
    printf("O caso médio, onde todo o tesouro está todo bagunçado, ");
    printf("de forma aletória\n");
    printf("O pior caso, onde todo o tesouro está ordenado... ");
    printf("porém de trás pra frente...\n");

    printf("\n\n");
    printf("Escolha uma opção: \n");
    printf("1 - Gerar um novo pote de ouro \n");
    printf("2 - Carregar um pote existente \n");

    do{
        scanf("%d", &menu_screen1);
        switch(menu_screen1){
            case 1:
                printf("Ótimo vamos criar um novo pote de ouro simulado!\n");
                printf("Para seguir, informe a quantidade de itens no pote:\n");
                do{
                    scanf("%d", &size);
                    if(size == 0) printf("Valor, inválido, tente outro\n");
                }while(size == 0);
                printf("Perfeito! Agora escolha um número mágico, ou digite 0 para gerar aleatoriamente\n");
                scanf("%d",&seed);
            break;
            case 2:
                printf("Ok, vamos carregar seu pote de ouro simualdo!\n");
                clear_input_buffer();
                printf("Informe o nome do arquivo: ");
                if (fgets(file_name_input, sizeof(file_name_input), stdin) != NULL) {
                    size_t len = strlen(file_name_input);
                    if (len > 0 && file_name_input[len - 1] == '\n') {
                        file_name_input[len - 1] = '\0';
                    }
                }

                printf("File name entered: %s\n", file_name_input);
            break;
            default:
                printf("Opção inválida, selecione 1 ou 2\n");
        }
    }while(menu_screen1 != 1 && menu_screen1 != 2);


    T_DataSet data_set = menu_screen1 == 1? create_filled_data_set(size,seed) : load_dataset_from_csv(file_name_input);
    printf("Dataset com %d itens carregado!\n", data_set.size);

    T_AnalyticsData full_analytics[algorithm_size][test_type_size], analytics[test_type_size];

    if(menu_screen1 == 1){
        char data_set_name[MAX_FILE_NAME] = "gold_pot_";
        char number_buffer[100] = "";
        sprintf(number_buffer,"%d",size);
        strcat(data_set_name,number_buffer);
        write_dataset_to_csv(data_set, data_set_name, true, ';');
        printf("Data_Set gerado e salvo como: %s\n", data_set_name);
    }

    

    printf("\n\n");
    printf("Escolha uma opção para seguirmos: \n");
    printf("1 - Testar todos Algorítimos \n");
    printf("2 - Testar apenas Selection Sort \n");
    printf("3 - Testar apenas Bubble Sort \n");
    printf("4 - Testar apenas Insertion Sort \n");
    printf("5 - Testar apenas Merge Sort \n");
    printf("6 - Testar apenas Quick Sort \n");

    do{
        scanf("%d", &menu_screen2);
        switch(menu_screen2){
            case 1:
                printf("Rodando todos os casos... aguarde, pode levar um bom tempo!\n");
                run_all_test_cases(data_set,full_analytics);
            break;
            case 2:
                printf("Rodando Selection Sort.\nAguarde, pode levar tempo!\n");
                printf("Melhor cenário:\n");
                analytics[0] = run_test_case(data_set,selection,bestScenario);
                printf("Feito!\n");
                printf("Cenário Médio:\n");
                analytics[1] = run_test_case(data_set,selection,avarageScenario);
                printf("Feito!\n");
                printf("Pior Cenário:\n");
                analytics[2] = run_test_case(data_set,selection,worstScenario);
                printf("Feito!\n");
            break;
            case 3:
                printf("Rodando Bubble Sort.\nAguarde, pode levar tempo!\n");
                printf("Melhor cenário:\n");
                analytics[0] = run_test_case(data_set,bubble,bestScenario);
                printf("Feito!\n");
                printf("Cenário Médio:\n");
                analytics[1] = run_test_case(data_set,bubble,avarageScenario);
                printf("Feito!\n");
                printf("Pior Cenário:\n");
                analytics[2] = run_test_case(data_set,bubble,worstScenario);
                printf("Feito!\n");
            break;
            case 4:
                printf("Rodando Insertion Sort.\nAguarde, pode levar tempo!\n");
                printf("Melhor cenário:\n");
                analytics[0] = run_test_case(data_set,insertion,bestScenario);
                printf("Feito!\n");
                printf("Cenário Médio:\n");
                analytics[1] = run_test_case(data_set,insertion,avarageScenario);
                printf("Feito!");
                printf("Pior Cenário:\n");
                analytics[2] = run_test_case(data_set,insertion,worstScenario);
                printf("Feito!\n");
            break;
            case 5:
                printf("Rodando Merge Sort.\nAguarde, pode levar tempo!\n");
                printf("Melhor cenário:\n");
                analytics[0] = run_test_case(data_set,merge,bestScenario);
                printf("Feito!\n");
                printf("Cenário Médio:\n");
                analytics[1] = run_test_case(data_set,merge,avarageScenario);
                printf("Feito!\n");
                printf("Pior Cenário:\n");
                analytics[2] = run_test_case(data_set,merge,worstScenario);
                printf("Feito!\n");
            break;
            case 6:
                printf("Rodando Quick Sort.\nAguarde, pode levar tempo!\n");
                printf("Melhor cenário:\n");
                analytics[0] = run_test_case(data_set,quick,bestScenario);
                printf("Feito!\n");
                printf("Cenário Médio:\n");
                analytics[1] = run_test_case(data_set,quick,avarageScenario);
                printf("Feito!\n");
                printf("Pior Cenário:\n");
                analytics[2] = run_test_case(data_set,quick,worstScenario);
                printf("Feito!\n");
            break;
            default:
                printf("Opção inválida, tente outra!\n");
            break;
        }
    }while(menu_screen2 > 6 || menu_screen2 < 1);

    printf("Tudo feito, os resultados estão nos arquivos csv!\n");

    double total_time = 0.0;
    if(menu_screen2 == 1){
        
        for (int a = 0; a < algorithm_size; a++){
            for(int s = 0; s < test_type_size; s++){
                printf("Algo: %d, Test: %d, Comp: %llu, Swap: %llu, AvarageTime: %lf\n",
                    full_analytics[a][s].algorithm,
                    full_analytics[a][s].test_type,
                    full_analytics[a][s].comparisonCount,
                    full_analytics[a][s].swapCount,
                    full_analytics[a][s].completionTime.avarage_result
                );
                total_time+=full_analytics[a][s].completionTime.avarage_result;
            }
        }
    }else{
        for(int s = 0; s < test_type_size; s++){
            printf("Algo: %d, Test: %d, Comp: %llu, Swap: %llu, AvarageTime: %lf\n",
                        analytics[s].algorithm,
                        analytics[s].test_type,
                        analytics[s].comparisonCount,
                        analytics[s].swapCount,
                        analytics[s].completionTime.avarage_result
                    );
            total_time+=analytics[s].completionTime.avarage_result;
        }
    }
    printf("Tempo total dos testes: %lf\n", total_time);
    
    printf("Liberando memória... ");
    free(data_set.data);
    printf("Liberado! Adeus e até a próxima!\n");
}

