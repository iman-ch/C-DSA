/**
 * -------------------------------------
 * @file  dllist.c
 * Assignment 1 C File
 * -------------------------------------
 * @author Iman Chaudhry 210650820
 *
 * @version 2024-02-17
 *
 * ------------------------------------- */ 
 
#include <stdio.h>
#include <stdlib.h> 
#include "dllist.h"

NODE *new_node(char data) {
    NODE* np = (NODE*) malloc(sizeof(NODE));      
    np->data = data;                              
    np->prev = NULL;                              
    np->next = NULL;                             

    return np;                                    
}

void dll_insert_start(DLL *dllp, NODE *np) {
    if (dllp->start == NULL) {     
        np->prev = NULL;            
        np->next = NULL;           
        dllp->start = np;        
        dllp->end = np;       
    } else {                         
        np->prev = NULL;          
        np->next = dllp->start;  //
        dllp->start->prev = np;  
        dllp->start = np;        
    }
    dllp->length++;             
}

void dll_insert_end(DLL *dllp, NODE *np) {
    if (dllp->start == NULL) {       
        np->prev = NULL;           
        np->next = NULL;           
        dllp->start = np;       
        dllp->end = np;         
    } else {                         
        np->next = NULL;           
        np->prev = dllp->end;  //
        dllp->end->next = np;   
        dllp->end = np;         
    }
    dllp->length++;
}

void dll_delete_start(DLL *dllp) {
    NODE* np = dllp->start;                 
   
    if (dllp->length == 0) {                
        return;
    } else if (dllp->length == 1) {             
        dllp->start = NULL;                  
        dllp->end = NULL;                   
    } else {
        dllp->start = np->next;     //         
        dllp->start->prev = NULL;            
    }
    free(np);                                  
    dllp->length--;                         
}

void dll_delete_end(DLL *dllp) {
    NODE* np = dllp->end;                  
   
    if (dllp->length == 0) {                
        return;
    } else if (dllp->length == 1) {           
        dllp->start = NULL;               
        dllp->end = NULL;                 
    } else {
        dllp->end = np->prev;    //         
        dllp->end->next = NULL;            
    }
    free(np);                               
    dllp->length--;                        
}

void dll_clean(DLL *dllp) {
    NODE *np = dllp->start;      

    while (np) {                    
        NODE *next = np->next;      
        free(np);                   
        np = next;                 
    }

    dllp->start = NULL;          
    dllp->end = NULL;            
    dllp->length = 0;            
}