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
} Time;

void mostrar_menu(Time* arr, int n){
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
            bubble_sort(arr, n);
            imprimir_tabela(arr, n);
            exit(0);
        case 2:
            selection_sort(arr, n);
            imprimir_tabela(arr, n);
            exit(0);
        case 3:
            insertion_sort(arr, n);
            imprimir_tabela(arr, n);
            exit(0);
        case 9:
            exit(0);
        default:
            printf("Opcao invalida!\n\n");
            break;
        }
    }while(op != 0);
}

void imprimir_tabela(Time* time, int* num_times){
    printf("TIME\t");
    printf("PONTOS\t");
    printf("VITORIAS\t");
    printf("EMPATES\t");
    printf("DERROTAS\t");
    printf("SALDO\t");
    printf("GOLS_PRO\t");
    printf("GOLS_CONTRA\n");

    for(int j = 0; j < num_times; j++){
            printf("%s\t", time[j].nome_time);
            printf("  %d\t", time[j].pontos);
            printf("  %d\t\t", time[j].vitorias);
            printf("  %d\t", time[j].empates);
            printf("  %d\t\t", time[j].derrotas);
            printf("  %d\t", time[j].saldo_gols);
            printf("  %d\t\t", time[j].gols_pro);
            printf("  %d\n", time[j].gols_contra);
    }
}

int ler_arquivo(char* nome_arquivo, Time* time, int* num_times) {
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
            if (strcmp(time[i].nome_time, time_1) == 0) {
                time_1_existe = i;
            }
            if (strcmp(time[i].nome_time, time_2) == 0) {
                time_2_existe = i;
            }
        }
        if (time_1_existe == -1) {
            strcpy(time[*num_times].nome_time, time_1);
            time[*num_times].gols_pro = 0;
            time[*num_times].gols_contra = 0;
            time_1_existe = (*num_times)++;
        }
        if (time_2_existe == -1) {
            strcpy(time[*num_times].nome_time, time_2);
            time[*num_times].gols_pro = 0;
            time[*num_times].gols_contra = 0;
            time_2_existe = (*num_times)++;
        }
        time[time_1_existe].gols_pro += gols_pro;
        time[time_1_existe].gols_contra += gols_contra;

        for(int i = 0; i < *num_times; i++){
            time[i].saldo_gols = time[i].gols_pro - time[i].gols_contra;
        }

        if(time[time_1_existe].gols_pro > time[time_2_existe].gols_contra){
            time[time_1_existe].vitorias++;
            time[time_1_existe].pontos += 3;
            time[time_2_existe].derrotas++;
        }else if(time[time_2_existe].gols_contra > time[time_1_existe].gols_pro){
            time[time_2_existe].vitorias++;
            time[time_2_existe].pontos += 3;
            time[time_1_existe].derrotas++;
        }else if(time[time_1_existe].gols_pro == time[time_2_existe].gols_contra){
            time[time_1_existe].empates++;
            time[time_1_existe].pontos += 1;
        }else if(time[time_2_existe].gols_contra == time[time_1_existe].gols_pro){
            time[time_2_existe].empates++;
            time[time_2_existe].pontos += 1;
        }

    }

    fclose(arquivo);

    return 1;
}

void bubble_sort(Time *arr, int n){
    Time temp;
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

void selection_sort(Time *arr, int n) {
    Time temp;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
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

void insertion_sort(Time *arr, int n){
    Time temp;
    for(int i = 1; i < n; i++){
        temp = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j].pontos == temp.pontos){
            if(arr[j].vitorias < temp.vitorias){
                arr[j+1] = arr[j];
                j = j - 1;
            }else if(arr[j].vitorias == temp.vitorias){
                if(arr[j].saldo_gols < temp.saldo_gols){
                    arr[j+1] = arr[j];
                    j = j - 1;
                }else if(arr[j].saldo_gols == temp.saldo_gols){
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
    Time time[MAX_TEAMS];
    int num_times = 0;

    ler_arquivo(nome_arquivo, time, &num_times);

    mostrar_menu(time, num_times);

    return 0;
}
