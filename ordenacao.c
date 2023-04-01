#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome_time[100];
    char nome_adversario[100];
    char resultado[100];
    //int vitorias;
    //int derrotas;
    //int empates;
    //int pontos;
} Partida;


int main(){
    Partida partidas[100];

    FILE* arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int i = 0;
    while(arquivo != EOF){
        char linha[100];
        fgets(linha, 100, arquivo);
        char* time = strtok(linha, " ");
        char* resultado = strtok(NULL, " ");
        char* adversario = strtok(NULL, " ");
        printf("%s\n", strcpy(partidas[i].nome_time, time));
        printf("%s\n", strcpy(partidas[i].resultado, resultado));
        printf("%s\n", strcpy(partidas[i].nome_adversario, adversario));
        i++;
    }

    fclose(arquivo);
/*
    for(int j = 0; j < i; j++){
        printf("%s\n%s\n%s\n", partidas[j].nome_time, partidas[j].resultado, partidas[j].nome_adversario);
    }
*/
    return 0;
}
