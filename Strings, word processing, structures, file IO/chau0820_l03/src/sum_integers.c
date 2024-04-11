/**
 * -------------------------------------
 * @file  sum_integers.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2024-01-25
 *
 * -------------------------------------
 */
#include "functions.h"
#include <ctype.h>

int sum_integers(void) {

    int input;
    int sum = 0;
    printf("Enter integers, one per line:\n");

    while(scanf("%d", &input)==1){; 
        sum += input;
    }
    
    return sum;

}