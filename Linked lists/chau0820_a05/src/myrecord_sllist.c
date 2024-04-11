/**
 * -------------------------------------
 * @file  myrecord_slist.c
 * Assignment 1  C File
 * -------------------------------------
 * @author Iman Chaudhry 210650820
 *
 * @version 2024-02-17
 *
 * ------------------------------------- */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myrecord_sllist.h"

/**
 * Search singly linked list by the key name.
 * 
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE *sll_search(SLL *sllp, char *name) {
    NODE *r=NULL; 
    NODE *np = sllp->start;
    while (np != NULL) {
        if (strcmp(np->data.name, name) == 0) {
            r = np;
        } else {
            np = np->next;
        }
    }
    return r;
}

/**
 * Insert a new record to linked list at the position sorted by record name field.
 *
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - name field of the new record.
 * @param float score - the score data of the new record.
 */
void sll_insert(SLL *sllp, char *name, float score) {
    NODE *np = (NODE *) malloc(sizeof(NODE)); // create a node and set data value
    strcpy(np->data.name, name);
    np->data.score = score;
    np->next = NULL;
    NODE *prev = NULL, *p = sllp->start;
    while (p!=NULL && strcmp(p->data.name, name) < 0) {
        prev = p;
        p = p->next;
    }
    if (prev == NULL) { // empty linked list or found at start
        sllp->start = np; // insert at beginning
        np->next = p;
    } else { // found the node or not found, i.e. p = NULL
        prev->next = np; // insert between between prev and p,
        np->next = p;
    }
}

/**
 * Delete a node of record matched by the name key from linked list.
 * 
 * @param SLL *sllp provides the address of a singly linked list structure.
 * @param name - key used to find the node for deletion. 
 * @return 1 if deleted a matched node, 0 otherwise. 
 */
int sll_delete(SLL *sllp, char *name) {
    NODE *curr = sllp->start;
    NODE *prev = NULL;
    while(curr != NULL){                         
        if(strcmp(curr->data.name, name) == 0){      
            if(prev == NULL){                     
                sllp->start = curr->next;         
            }else{
                prev->next = curr->next;            
            }        
            free(curr);                              
            sllp->length--;                    
            return 1;          
        }
        prev = curr;                                 
        curr = curr->next;                             
    }
    return 0;
}

/**
 * Clean singly linked list, delete all nodes. 
 * @param @param SLL *sllp provides the address of a singly linked list structure.
 */
void sll_clean(SLL *sllp) {
    NODE *temp, *ptr = sllp->start;
    while (ptr != NULL) {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    sllp->start = NULL;
    sllp->length = 0;
}