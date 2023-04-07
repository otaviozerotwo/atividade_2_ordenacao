#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_SIZE 15
#define MAX_TIMES 12

typedef struct{
    char nome_time[100];
    int vitorias;
    int derrotas;
    int empates;
    int pontos;
    int saldo_gols;
    int gols_pro;
    int gols_contra;
} Time;

void mostrar_menu(Time* arr){
    int op = 0;

    do{
        printf("Escolha qual metodo de ordenacao deseja usar:\n\n");
        printf("1: Bubble Sort\n");
        printf("2: Selection Sort\n");
        printf("3: Insertion Sort\n");
        printf("9: Sair\n");
        scanf("%d", &op);

        switch(op){
        case 1:
            bubble_sort(arr);
            imprimir_tabela(arr);
            exit(0);
        case 2:
            selection_sort(arr);
            imprimir_tabela(arr);
            exit(0);
        case 3:
            //insertion_sort(arr);
            imprimir_tabela(arr);
            exit(0);
        case 9:
            exit(0);
        default:
            printf("Opcao invalida!\n\n");
            break;
        }
    }while(op != 9);
}

void imprimir_tabela(Time* arr){
    printf("TIME\t");
    printf("PONTOS\t");
    printf("VITORIAS\t");
    printf("EMPATES\t");
    printf("DERROTAS\t");
    printf("SALDO\t");
    printf("GOLS_PRO\t");
    printf("GOLS_CONTRA\n");

    for(int j = 0; j < MAX_TIMES; j++){
            printf("%s\t", arr[j].nome_time);
            printf("  %d\t", arr[j].pontos);
            printf("  %d\t\t", arr[j].vitorias);
            printf("  %d\t", arr[j].empates);
            printf("  %d\t\t", arr[j].derrotas);
            printf("  %d\t", arr[j].saldo_gols);
            printf("  %d\t\t", arr[j].gols_pro);
            printf("  %d\n", arr[j].gols_contra);
    }
}

int ler_arquivo(char* nome_arquivo, Time* arr){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int num_times = 0;
    int num_partidas = 0;

    while(!feof(arquivo)){
        char time_1[MAX_LINE_SIZE], time_2[MAX_LINE_SIZE];
        int gols_pro, gols_contra;

        //Lê a partida do arquivo
        fscanf(arquivo, "%s %dX%d %s", time_1, &gols_pro, &gols_contra, time_2);

        //Verifica se se time_1 e time_2 já estão cadastrados
        int time_1_existe = -1, time_2_existe = -1;
        for(int i = 0; i < num_times; i++){
            if(strcmp(arr[i].nome_time, time_1) == 0){
                time_1_existe = i;
            }
            if(strcmp(arr[i].nome_time, time_2) == 0){
                time_2_existe = i;
            }
        }

        //Se time_1 não está cadastrado, cadastra ele
        if(time_1_existe == -1){
            strcpy(arr[num_times].nome_time, time_1);
            arr[num_times].pontos = 0;
            arr[num_times].vitorias = 0;
            arr[num_times].empates = 0;
            arr[num_times].derrotas = 0;
            arr[num_times].gols_pro = 0;
            arr[num_times].gols_contra = 0;
            arr[num_times].saldo_gols = 0;
            time_1_existe = num_times;
            num_times++;
        }

        //Se time_2 não está cadastrado, cadastra ele
        if(time_2_existe == -1){
            strcpy(arr[num_times].nome_time, time_2);
            arr[num_times].pontos = 0;
            arr[num_times].vitorias = 0;
            arr[num_times].empates = 0;
            arr[num_times].derrotas = 0;
            arr[num_times].gols_pro = 0;
            arr[num_times].gols_contra = 0;
            arr[num_times].saldo_gols = 0;
            time_2_existe = num_times;
            num_times++;
        }

        //Atualiza os dados dos times
        if(gols_pro > gols_contra){ //Vitória do time_1
            arr[time_1_existe].vitorias++;
            arr[time_1_existe].pontos += 3;
            arr[time_2_existe].derrotas++;
        }else if(gols_contra > gols_pro){ //Vitória do time_2
            arr[time_2_existe].vitorias++;
            arr[time_2_existe].pontos += 3;
            arr[time_1_existe].derrotas++;
        }else{ //Empate
            arr[time_1_existe].pontos++;
            arr[time_2_existe].pontos++;
            arr[time_1_existe].empates++;
            arr[time_2_existe].empates++;
        }

        arr[time_1_existe].gols_pro += gols_pro;
        arr[time_1_existe].gols_contra += gols_contra;
        arr[time_1_existe].saldo_gols += gols_pro - gols_contra;
        arr[time_2_existe].gols_pro += gols_contra;
        arr[time_2_existe].gols_contra += gols_pro;
        arr[time_2_existe].saldo_gols += gols_contra - gols_pro;

        num_partidas++;
    }

    fclose(arquivo);

    return 1;
}

void bubble_sort(Time *arr){
    Time temp;

    for(int i = 0; i < MAX_TIMES - 1; i++){
        for(int j = 0; j < MAX_TIMES - i - 1; j++){
            if(arr[j].pontos < arr[j+1].pontos){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }else if(arr[j].pontos == arr[j+1].pontos){
                if(arr[j].vitorias > arr[j+1].vitorias){
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }else if(arr[j].vitorias == arr[j+1].vitorias){
                    if(arr[j].saldo_gols > arr[j+1].saldo_gols){
                        temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                    }
                }

            }
        }
    }
}

void selection_sort(Time *arr) {
    Time temp;

    for(int i = 0; i < MAX_TIMES - 1; i++){
        for(int j = i + 1; j < MAX_TIMES; j++){
            if(arr[i].pontos < arr[j].pontos){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }else if(arr[i].pontos == arr[j].pontos){
                if(arr[i].vitorias < arr[j].vitorias){
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }else if(arr[i].vitorias == arr[j].vitorias){
                    if(arr[j].saldo_gols < arr[j+1].saldo_gols){
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }

            }
        }
    }

}

void insertion_sort(Time *arr){
    int i, j;
    Time temp;

    for(i = 1; i < MAX_TIMES; i++){
        temp = arr[i];
        j = i - 1;

        //compara primeiro os pontos
        while(j >= 0 && arr[j].pontos == temp.pontos){
            //em caso de empate nos pontos, compara as vitórias
            if(arr[j].vitorias < temp.vitorias){
                arr[j+1] = arr[j];
                j = j - 1;
            }else if(arr[j].vitorias == temp.vitorias){
                //Em caso de empate nas vitórias, compara o saldo de gols
                if(arr[j].saldo_gols < temp.saldo_gols){
                    arr[j+1] = arr[j];
                    j = j - 1;
                }else if(arr[j].saldo_gols == temp.saldo_gols){
                    //Em caso de empate no saldo de gols, compara os gols pró
                    if(arr[j].gols_pro < temp.gols_pro){
                        arr[j+1] = arr[j];
                        j = j + 1;
                    }else{
                        break;
                    }
                }else{
                    break;
                }
            }else{
                break;
            }
        }

        arr[j+1] = temp;
    }
}

int main(){
    char nome_arquivo[] = "dados.txt";

    Time time[MAX_TIMES];

    ler_arquivo(nome_arquivo, time);

    mostrar_menu(time);

    return 0;
}
