/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


BSTNODE *new_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);

BSTNODE *bst_search(BSTNODE *root, char *key) {
    if (root == NULL) return NULL;

    int cmp = strcmp(root->data.name, key);
    if (cmp == 0) return root;
    else if (cmp > 0) return bst_search(root->left, key);
    else return bst_search(root->right, key);
}


void bst_insert(BSTNODE **rootp, RECORD data) {
    BSTNODE *node = new_node(data);
    if(*rootp){
        int cmp = strcmp((*rootp)->data.name, data.name);
        if (cmp > 0){
            bst_insert(&(*rootp)->left, data);
        } else if (cmp < 0) {
            bst_insert(&(*rootp)->right, data);
        } else { 
            free(node); 
        }
    } else {
        *rootp = node;
    }
}

void bst_delete(BSTNODE **rootp, char *key) {
    if(*rootp){

        int cmp = strcmp((*rootp)->data.name, key);
        if (cmp > 0){
            bst_delete(&(*rootp)->left, key);
        } else if (cmp < 0) {
           bst_delete(&(*rootp)->right, key);

        } else {
            if ((*rootp)->left != NULL && (*rootp)->right != NULL){
                BSTNODE **successor = &(*rootp)->right;
                while ((*successor)->left != NULL){
                    successor = &(*successor)->left;
                }
                (*rootp)->data = (*successor)->data;
                bst_delete(successor, (*successor)->data.name);
                
            } else {
                BSTNODE *delete = *rootp;
                if((*rootp)->left == NULL){
                    *rootp = (*rootp)->right;
                } else if ((*rootp)->right == NULL) {
                    *rootp = (*rootp)->left;
                }
                free(delete);
            }
        }
    }

}



BSTNODE *new_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_bst(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            clean_bst(&root->left);
        if (root->right)
            clean_bst(&root->right);
        free(root);
    }
    *rootp = NULL;
}