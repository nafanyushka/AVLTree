//
// Created by Nafany on 09.05.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int getInt(){
    int a;
    while(scanf("%d", &a) != 1) {
        printf("Попробуйте еще раз: ");
        while(getchar() != '\n');
    }
    getchar();
    return a;
}

float getFloat(){
    float a;
    while(scanf("%f", &a) != 1){
        printf("Попробуйте еще раз: ");
        while(getchar() != '\n');
    }
    getchar();
    return a;
}

char* get_String(){
    char* a = (char*)malloc(1);
    char buf[11];
    int n, size = 0;
    *a = '\0';
//    scanf("%*[^\n]"); //Очистка входного буфера
//    scanf("%*c"); //Очистка входного буфера
    do{
        n = scanf("%10[^\n]", buf);
        if(n < 0){
            free(a);
            a = NULL;
            continue;
        }
        if(n == 0)
            scanf("%*c");
        else{
            size += (int)strlen(buf);
            a = (char*)realloc(a, size + 1);
            strcat(a, buf);
        }
    }while(n > 0);
    if(*(a + strlen(a) - 1) == ' '){
        for(int i = strlen(a) - 1; *(a + i) == ' '; i--)
            *(a+i) = '\0';
    }
    return a;
}