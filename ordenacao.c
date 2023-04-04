#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_SIZE 100
#define MAX_TEAMS 100

typedef struct{
    char nome_time[100];
    int vitorias[100];
    int derrotas[100];
    int empates[100];
    int pontos[100];
    int saldo_gols[100];
    int gols_pro;
    int gols_contra;
} Partida;

int read_teams_file(char* filename, Partida* partidas, int* num_teams) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char line[MAX_LINE_SIZE];

    while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
        char team1[MAX_LINE_SIZE], team2[MAX_LINE_SIZE];
        int gols_pro, gols_contra;
        sscanf(line, "%s %dX%d %s", team1, &gols_pro, &gols_contra, team2);
        int team1_exists = -1, team2_exists = -1;
        for (int i = 0; i < *num_teams; i++) {
            if (strcmp(partidas[i].nome_time, team1) == 0) {
                team1_exists = i;
            }
            if (strcmp(partidas[i].nome_time, team2) == 0) {
                team2_exists = i;
            }
        }
        if (team1_exists == -1) {
            strcpy(partidas[*num_teams].nome_time, team1);
            partidas[*num_teams].gols_pro = 0;
            partidas[*num_teams].gols_contra = 0;
            team1_exists = (*num_teams)++;
        }
        if (team2_exists == -1) {
            strcpy(partidas[*num_teams].nome_time, team2);
            partidas[*num_teams].gols_pro = 0;
            partidas[*num_teams].gols_contra = 0;
            team2_exists = (*num_teams)++;
        }
        partidas[team1_exists].gols_pro += gols_pro;
        partidas[team1_exists].gols_contra += gols_contra;
        partidas[team2_exists].gols_pro += gols_pro;
        partidas[team2_exists].gols_contra += gols_contra;

    }

    fclose(file);

    return 1;
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
    char filename[] = "dados.txt";
    Partida partidas[MAX_TEAMS];
    int num_teams = 0;

    printf("TIME\t");
    printf("PONTOS\t");
    printf("VITORIAS\t");
    printf("EMPATES\t");
    printf("DERROTAS\t");
    printf("SALDO\t");
    printf("GOLS_PRO\t");
    printf("GOLS_CONTRA\n");

    if (read_teams_file(filename, partidas, &num_teams)) {
        for(int j = 0; j < num_teams; j++){
            printf("%s\t", partidas[j].nome_time);
            printf("%s\t", partidas[j].pontos);
            printf("%s\t\t", partidas[j].vitorias);
            printf("%s\t", partidas[j].empates);
            printf("%s\t\t", partidas[j].derrotas);
            printf("%s\t", partidas[j].saldo_gols);
            printf("%d\t\t", partidas[j].gols_pro);
            printf("%d\n", partidas[j].gols_contra);
        }
    }
    return 0;
}
