/*
 * your program signature
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

HASHNODE *hashtable_search(HASHTABLE *ht, char *key) {
    int i = hash(key, ht->size); // compute the hash index of name
    HASHNODE *p = ht->hna[i]; // get the linked list of the hash value
    while(p != NULL) { // search the linked list, if name is matched, return the node
        if (strcmp(p->key, key) == 0) {
            return p;
        }
        p = p->next;
    }        
    return NULL;
}

int hashtable_insert(HASHTABLE *ht, char *key, int value) {
    int index = hash(key, ht->size);
    HASHNODE *newNode = (HASHNODE *)malloc(sizeof(HASHNODE));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    if (ht->hna[index] == NULL) {
        ht->hna[index] = newNode;
    } else {
        HASHNODE *current = ht->hna[index];
        HASHNODE *prev = NULL;
        while (current != NULL && strcmp(current->key, key) < 0) {
            prev = current;
            current = current->next;
        }
        if (current != NULL && strcmp(current->key, key) == 0) {
            current->value = value;
            free(newNode);
            return 0;
        }
        if (prev == NULL) {
            newNode->next = current;
            ht->hna[index] = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
    ht->count++;
    return 1;
}

int hashtable_delete(HASHTABLE *ht, char *key) {
    int index = hash(key, ht->size);
    HASHNODE *curr = ht->hna[index];
    HASHNODE *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (prev == NULL) {
                ht->hna[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            ht->count--;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}


int hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key++;
    }
    return hash % size;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    ht->hna = (HASHNODE**) malloc(sizeof(HASHNODE**) * size);
    int i;
    for (i = 0; i < size; i++)
        *(ht->hna + i) = NULL;

    ht->size = size;
    ht->count = 0;
    return ht;
}


void hashtable_clean(HASHTABLE **htp) {
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HASHNODE *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++) {
        p = ht->hna[i];
        while (p) {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;
}