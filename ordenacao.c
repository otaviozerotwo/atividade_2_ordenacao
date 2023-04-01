#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NUM_LINES 1000

void bubble_sort(char **array, int size) {
    int i, j;
    char *tmp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (strcmp(array[j], array[j+1]) > 0) {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

int main() {
    FILE *fp = fopen("dados.txt", "r");
    if (fp == NULL) {
        printf("Error: failed to open input file\n");
        return 1;
    }

    char **lines = malloc(sizeof(char*) * MAX_NUM_LINES);
    int num_lines = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        lines[num_lines] = strdup(buffer);
        num_lines++;
        if (num_lines >= MAX_NUM_LINES) {
            printf("Error: input file has too many lines (max: %d)\n", MAX_NUM_LINES);
            return 1;
        }
    }
    fclose(fp);

    bubble_sort(lines, num_lines);

    char **matrix = malloc(sizeof(char*) * num_lines);
    for (int i = 0; i < num_lines; i++) {
        matrix[i] = lines[i];
    }

    //printf("Sorted matrix:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("%s\n", matrix[i]);
    }

    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
    free(matrix);

    //printf("Done!\n");
    return 0;
}
