#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome_time[100];
    char nome_adversario[100];
    char resultado[100];
    int vitorias;
    int derrotas;
    int empates;
    int pontos;
    int saldo_gols;
    int gols_pro;
    int gols_contra;
} Partida;


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
        char* adversario = strtok(NULL, " ");
        strcpy(partidas[i].nome_time, time);
        strcpy(partidas[i].resultado, resultado);
        strcpy(partidas[i].nome_adversario, adversario);
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
