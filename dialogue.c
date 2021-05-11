//
// Created by Nafany on 09.05.2021.
//

#include "dialogue.h"

AVLTree* load(){
    FILE* fd = fopen("test", "rb");
    AVLTree* root = NULL;
    while(!feof(fd)){
        if(root == NULL){
            int key;
            char* info = (char*)malloc(3);
            fread(&key, 1, sizeof(int), fd);
            fread(info, 1, 3, fd);
            root = newTree(key, info);
        }
        else{
            int key;
            char* info = (char*)malloc(3);
            fread(&key, 1, sizeof(int), fd);
            fread(info, 1, 3, fd);
            add(&root, root, newTree(key, info));
        }
    }
    fclose(fd);
    return root;
}

void dialogue(){
//    printf("Введите корневой ключ и строку: ");
    int key;
    char* info;
//    key = getInt();
//    do{
//        info = get_String();
//    }while(strlen(info) < 1);

    AVLTree* root = load();

//    AVLTree* root = newTree(key, info);
    do{
        printf("Введите ключ и строку: ");
        key = getInt();
        do{
            info = get_String();
        }while(strlen(info) < 1);
        add(&root, root, newTree(key, info));
    } while( key != -80 );
    freeAVLTree(root);
}