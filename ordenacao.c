#include<stdio.h>

void menu(){
    int opcao = 0;

    printf("Selecione o método de ordenação:\n");
    printf("1 - Bubble Sort\n"
           "2 - Selection Sort\n"
           "3 - Insertion Sort\n");

    scanf("%d", &opcao);

    switch(opcao){
    case 1:
        bubble_sort();
        break;
    case 2:
        selection_sort();
        break;
    case 3:
        insertion_sort();
        break;
    default:
        printf("Opção inválida!");
        break;
    }
}

void bubble_sort(){

}

void selection_sort(){

}

void insertion_sort(){

}

int main(){
    //Chama menu de métodos de ordenação
    menu();

    return 0;
}
