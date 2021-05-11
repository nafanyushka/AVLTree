//
// Created by Nafany on 09.05.2021.
//

#ifndef AVLTREE_TREE_H
#define AVLTREE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

typedef struct AVLTree AVLTree;

struct AVLTree{
    int key;
    int balance;
    char* info;
    AVLTree* left;
    AVLTree* right;
};

AVLTree* newTree(int key, char* info);
int add(AVLTree** root, AVLTree* tree, AVLTree* plug);
void printTreeKeys(AVLTree* tree, int i);
int rem(AVLTree* tree, int key);
char* find(AVLTree* tree, int key);
char* findFar(AVLTree* tree, int key);
void freeAVLTree(AVLTree* tree);

#endif //AVLTREE_TREE_H
