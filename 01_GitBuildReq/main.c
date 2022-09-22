#include "stdio.h"


int main(void){
    char inputChar = getchar();

    printf("Hello, ");
    while(inputChar != EOF && inputChar != '\n'){
        putchar(inputChar);
        inputChar = getchar();
    }

    printf("!");
    return 0;
}