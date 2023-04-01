#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(char *arr[], int n);
void selectionSort(char *arr[], int n);
void insertionSort(char *arr[], int n);

int main()
{
    char **arr;
    int n;
    int escolha;

    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &n);

    arr = (char**) malloc(n * sizeof(char*));
    if (arr == NULL) {
        printf("Erro ao alocar a memória.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        char buffer[256];
        fscanf(arquivo, "%s", buffer);
        arr[i] = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (arr[i] == NULL) {
            printf("Erro ao alocar a memória.\n");
            exit(1);
        }
        strcpy(arr[i], buffer);
    }

    fclose(arquivo);

    printf("Escolha um algoritmo de ordenação:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            bubbleSort(arr, n);
            break;
        case 2:
            selectionSort(arr, n);
            break;
        case 3:
            insertionSort(arr, n);
            break;
        default:
            printf("Escolha inválida.\n");
            exit(1);
    }

    printf("Array ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}

void bubbleSort(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        char *temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void insertionSort(char *arr[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
