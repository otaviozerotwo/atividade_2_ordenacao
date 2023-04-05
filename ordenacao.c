#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_SIZE 100
#define MAX_TEAMS 100

typedef struct{
    char nome_time[100];
    int vitorias;
    int derrotas;
    int empates;
    int pontos;
    int saldo_gols;
    int gols_pro;
    int gols_contra;
} Partida;

void imprimir_tabela(Partida* partidas, int* num_times){
    printf("TIME\t");
    printf("PONTOS\t");
    printf("VITORIAS\t");
    printf("EMPATES\t");
    printf("DERROTAS\t");
    printf("SALDO\t");
    printf("GOLS_PRO\t");
    printf("GOLS_CONTRA\n");

    for(int j = 0; j < num_times; j++){
            printf("%s\t", partidas[j].nome_time);
            printf("  %d\t", partidas[j].pontos);
            printf("  %d\t\t", partidas[j].vitorias);
            printf("  %d\t", partidas[j].empates);
            printf("  %d\t\t", partidas[j].derrotas);
            printf("  %d\t", partidas[j].saldo_gols);
            printf("  %d\t\t", partidas[j].gols_pro);
            printf("  %d\n", partidas[j].gols_contra);
    }
}

int ler_arquivo(char* nome_arquivo, Partida* partidas, int* num_times) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha_arquivo[MAX_LINE_SIZE];

    while (fgets(linha_arquivo, MAX_LINE_SIZE, arquivo) != NULL) {
        char time_1[MAX_LINE_SIZE], time_2[MAX_LINE_SIZE];
        int gols_pro, gols_contra;
        sscanf(linha_arquivo, "%s %dX%d %s", time_1, &gols_pro, &gols_contra, time_2);
        int time_1_existe = -1, time_2_existe = -1;
        for (int i = 0; i < *num_times; i++) {
            if (strcmp(partidas[i].nome_time, time_1) == 0) {
                time_1_existe = i;
            }
            if (strcmp(partidas[i].nome_time, time_2) == 0) {
                time_2_existe = i;
            }
        }
        if (time_1_existe == -1) {
            strcpy(partidas[*num_times].nome_time, time_1);
            partidas[*num_times].gols_pro = 0;
            partidas[*num_times].gols_contra = 0;
            time_1_existe = (*num_times)++;
        }
        if (time_2_existe == -1) {
            strcpy(partidas[*num_times].nome_time, time_2);
            partidas[*num_times].gols_pro = 0;
            partidas[*num_times].gols_contra = 0;
            time_2_existe = (*num_times)++;
        }
        partidas[time_1_existe].gols_pro += gols_pro;
        partidas[time_1_existe].gols_contra += gols_contra;

        for(int i = 0; i < *num_times; i++){
            partidas[i].saldo_gols = partidas[i].gols_pro - partidas[i].gols_contra;
        }

        for(int i = 0; i < *num_times; i++){
            if(partidas[i].gols_pro > partidas[i].gols_contra){
                partidas[i].pontos += 3;
                partidas[i].vitorias++;
            }else if(partidas[i].gols_pro == partidas[i].gols_contra){
                partidas[i].pontos += 1;
                partidas[i].empates++;
            }else{
                partidas[i].derrotas++;
            }
        }

    }

    fclose(arquivo);

    return 1;
}

void bubble_sort(Partida *arr, int n){
    Partida temp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
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

void selection_sort(Partida *arr, int n) {

}

void insertion_sort(Partida *arr, int n){

}

int main(){
    char nome_arquivo[] = "dados.txt";
    Partida partidas[MAX_TEAMS];
    int num_times = 0;

    ler_arquivo(nome_arquivo, partidas, &num_times);
    //imprimir_tabela(partidas, num_times);
    //bubble_sort(partidas, num_times);

    //printf("\n\n");
    imprimir_tabela(partidas, num_times);

    return 0;
}
