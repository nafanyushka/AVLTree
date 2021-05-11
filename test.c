//
// Created by Nafany on 11.05.2021.
//

#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* fd = fopen("test", "wb");
    int key;

    do{
        key = getInt();
        char* info;
        do{
            info = get_String();
        }while(strlen(info) < 1);
        fwrite(&key, 1, sizeof(int), fd);
        fwrite(info, 1, 3 * sizeof(char), fd);
        free(info);
    }while(key != 73);
    fclose(fd);
    return 0;
}