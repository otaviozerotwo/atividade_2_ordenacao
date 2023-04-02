#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome_time[100];
    int vitorias[100];
    int derrotas[100];
    int empates[100];
    int pontos[100];
    int saldo_gols[100];
    int gols_pro[100];
    int gols_contra[100];
} Partida;

void imprimir_vetor(char v[], int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", v[i]);
    }
}

void bubble_sort(Partida *arr, int n){
    Partida temp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(strcmp(arr[j].nome_time, arr[j+1].nome_time)){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    Partida partidas[100];

    FILE* arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int i = 0;

    while(!feof(arquivo)){
        char linha[100];
        fgets(linha, 100, arquivo);
        linha[strcspn(linha, "\n")] = '\0';
        char* time = strtok(linha, " ");
        char* resultado = strtok(NULL, " ");

        strcpy(partidas[i].nome_time, time);

        char* gols_pro = strtok(resultado, "X");
        char* gols_contra = strtok(NULL, " ");

        strcpy(partidas[i].gols_pro, gols_pro);
        strcpy(partidas[i].gols_contra, gols_contra);

        i++;
    }

    fclose(arquivo);

    printf("TIME\t");
    printf("PONTOS\t");
    printf("VITORIAS\t");
    printf("EMPATES\t");
    printf("DERROTAS\t");
    printf("SALDO\t");
    printf("GOLS PRO\t");
    printf("GOLS CONTRA\n");

    for(int j = 0; j < i; j++){
        printf("%s\t", partidas[j].nome_time);
        printf("%s\t", partidas[j].pontos);
        printf("%s\t\t", partidas[j].vitorias);
        printf("%s\t", partidas[j].empates);
        printf("%s\t\t", partidas[j].derrotas);
        printf("%s\t", partidas[j].saldo_gols);
        printf("%s\t\t", partidas[j].gols_pro);
        printf("%s\n", partidas[j].gols_contra);
    }
    return 0;
}
