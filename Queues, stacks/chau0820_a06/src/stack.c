/*
 * your program signature
 */ 
#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {
    np->next = sp->top;
    sp->top = np;
    sp->length++;
}

NODE *pop(STACK *sp) {
    NODE *popped = NULL;
    if(sp->top != NULL) {
        popped = sp->top;
        NODE *temp = sp->top;
        sp->top = sp->top->next;
        popped->next = NULL;
    }
    sp->length--;
    return popped;
}

void clean_stack(STACK *sp) {
  clean(&(sp->top));
  sp->top = NULL;
  sp->length=0;
}