//
// Created by Nafany on 09.05.2021.
//

#include "tree.h"

int max(int a, int b){
    if((a - b) > 0)
        return a;
    return b;
}

void freeBranch(AVLTree* branch){
    free(branch->info);
    free(branch);
}

AVLTree* rightRotate(AVLTree* A, AVLTree* B){
    //
    int ahl, ahr, bhl, bhr;
    bhr = 3;
    bhl = bhr - B->balance;
    ahl = max(bhr, bhl);
    ahr = ahl + A->balance;

    A->balance = ahr - bhr;
    B->balance = (1 + max(ahr, bhr)) - bhl;

    //
    A->left = B->right;
    B->right = A;
    return B;
}

AVLTree* leftRotate(AVLTree* A, AVLTree* B){
    //
    int ahl, ahr, bhl, bhr;

    bhl = 3;
    bhr = bhl - B->balance;
    ahr = 1 + max(bhl, bhr);
    ahl = ahr - A->balance;

    A->balance = bhl - ahl;
    B->balance = bhr - (1 + max(bhl, ahl));

    //
    A->right = B->left;
    B->left = A;
    return B;
}

AVLTree* newTree(int key, char* info){
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->key = key;
    tree->info = info;
    tree->balance = 0;
    tree->right = NULL;
    tree->left = NULL;
    return tree;
}
int add(AVLTree** root, AVLTree* tree, AVLTree* plug){
/*
     ЛЕВОЕ ЛЕВОЕ РЕТЮРН -30
     ЛЕВОЕ ПРАВОЕ ЛЕВОЕ РЕТЮРН -31
     ЛЕВОЕ ПРАВОЕ ПРАВОЕ РЕТЮРН -32
     ПРАВОЕ ПРАВОЕ РЕТЮРН -33
     ПРАВОЕ ЛЕВОЕ ПРАВОЕ РЕТЮРН -34
     ПРАВОЕ ЛЕВОЕ ЛЕВОЕ РЕТЮРН -35
                                     */
    if(plug->key == tree->key) {
        freeBranch(plug);
        return 0;
    }
    if(plug->key < tree->key){
        if(tree->left == NULL){
            tree->left = plug;
            tree->balance--;
            if(tree->balance != 0)
                return 1;
            else
                return 0;
        }
        int k = add(root, tree->left, plug);
        if(k != 0) {
            if(k == 1) {
                tree->balance -= 1;
/* TODO:
                 *  Сделать проверку на рут дерева.
                                                                    */
                if (tree->balance == -2) { //НАРУШЕНИЕ
                    if (tree->left->balance == -1) {
                        tree->balance = 0;
                        tree->left->balance = 0;
                        if(tree == *root){
                            *root = rightRotate(tree, tree->left);
                            return 0;
                        }
                        return -30;
                    }
                    if(tree->left->balance == 1){
                        if(tree->left->right->balance == -1){
                            tree->balance = +1;
                            tree->left->balance = 0;
                            tree->left->right->balance = 0;
                            tree->left = leftRotate(tree->left, tree->left->right);
                            if(tree == *root){
                                *root = rightRotate(tree, tree->left);
                                return 0;
                            }
                            return -31;
                        }
                        if(tree->left->right->balance == 1){
                            tree->balance = 0;
                            tree->left->balance = -1;
                            tree->left->right->balance = 0;
                            tree->left = leftRotate(tree->left, tree->left->right);
                            if(tree == *root){
                                *root = rightRotate(tree, tree->left);
                                return 0;
                            }
                            return -32;
                        }
                        if(tree->left->right->balance == 0){
                            tree->balance = 0;
                            tree->left->balance = 0;
                            tree->left->right->balance = 0;
                            tree->left = leftRotate(tree->left, tree->left->right);
                            if(tree == *root){
                                *root = rightRotate(tree, tree->left);
                                return 0;
                            }
                            return -32;
                        }
                    }
                }
            }
            AVLTree* A = tree->left;
            if(k == -30){
                tree->left = rightRotate(A, A->left);
                return 0;
            }
            if(k == -31){
                tree->left = rightRotate(A, A->left);
                return 0;
            }
            if(k == -32){
                tree->left = rightRotate(A, A->left);
                return 0;
            }
            if(k == -33){
                tree->left = leftRotate(A, A->right);
                return 0;
            }
            if(k == -34){
                tree->left = leftRotate(A, A->right);
                return 0;
            }
            if(k == -35){
                tree->left = leftRotate(A, A->right);
                return 0;
            }

        }
        else
            return 0;
        if(tree->balance == 0)
            return 0;
        else
            return 1;
    }
    if(plug->key > tree->key){
        if(tree->right == NULL){
            tree->right = plug;
            tree->balance++;
            if(tree->balance != 0)
                return 1;
            else
                return 0;
        }
        int k = add(root, tree->right, plug);
        if(k != 0) {
            if (k == 1) {
                tree->balance += 1;

                if(tree->balance == 2){
                    if(tree->right->balance == 1){
                        tree->balance = 0;
                        tree->right->balance = 0;
                        if(tree == *root){
                            *root = leftRotate(tree, tree->right);
                            return 0;
                        }
                        return -33;
                    }
                    if(tree->right->balance == -1){
                        if(tree->right->left->balance == 1){
                            tree->balance = -1;
                            tree->right->balance = 0;
                            tree->right->left->balance = 0;
                            tree->right = rightRotate(tree->right, tree->right->left);
                            if(tree == *root){
                                *root = leftRotate(tree, tree->right);
                                return 0;
                            }
                            return -34;
                        }
                        if(tree->right->left->balance == -1){
                            tree->balance = 0;
                            tree->right->balance = 1;
                            tree->right->left->balance = 0;
                            tree->right = rightRotate(tree->right, tree->right->left);
                            if(tree == *root){
                                *root = leftRotate(tree, tree->right);
                                return 0;
                            }
                            return -35;
                        }
                        if(tree->right->left->balance == 0){
                            tree->balance = 0;
                            tree->right->balance = 0;
                            tree->right->left->balance = 0;
                            tree->right = rightRotate(tree->right, tree->right->left);
                            if(tree == *root){
                                *root = leftRotate(tree, tree->right);
                                return 0;
                            }
                            return -35;
                        }
                    }
                }
            }
            AVLTree* A = tree->right;
            if (k == -30) {
                tree->right = rightRotate(A, A->left);
                return 0;
            }
            if (k == -31) {
                tree->right = rightRotate(A, A->left);
                return 0;
            }
            if (k == -32) {
                tree->right = rightRotate(A, A->left);
                return 0;
            }
            if (k == -33) {
                tree->right = leftRotate(A, A->left);
                return 0;
            }
            if (k == -34) {
                tree->right = leftRotate(A, A->left);
                return 0;
            }
            if (k == -35) {
                tree->right = leftRotate(A, A->left);
                return 0;
            }
        }
        else
            return 0;
        if(tree->balance == 0)
            return 0;
        else
            return 1;
    }
}

int rem(AVLTree* tree, int key){

    return 0;
}
char* find(AVLTree* tree, int key){
    AVLTree* finder = tree;
    while(finder != NULL){
        if(key == finder->key)
            return finder->info;
        if(key < finder->key)
            finder = finder->left;
        if(key > finder->key)
            finder = finder->right;
    }
    return NULL;
}
char* findFar(AVLTree* tree, int key){
    return NULL;
}
void freeAVLTree(AVLTree* tree){
    if(tree == NULL){
        return;
    }
    freeAVLTree(tree->left);
    freeAVLTree(tree->right);
    free(tree->info);
    free(tree);
}

void printTreeKeys(AVLTree* tree, int i){
    if(tree == NULL) {
        return;
    }
    printTreeKeys(tree->right, i + 1);
    for(int space = 0; space < i; space++){
        printf(" ");
    }
    printf("%d\n", tree->key);
    printTreeKeys(tree->left, i + 1);
}