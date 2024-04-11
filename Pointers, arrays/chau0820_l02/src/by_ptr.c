/**
 * -------------------------------------
 * @file  by_ptr.c
 * Lab 2 Pointer Functions Source Code File
 * -------------------------------------
 * @author Iman Chaudhry
 *
 * @version 2024-01-06
 *
 * -------------------------------------
 */
#include "by_ptr.h"

void fill_values_by_ptr(int *values, int size) {

    for(int i = 0; i < size; i++) {
        *(values + i) = i + 1;
    }
}

void fill_squares_by_ptr(int *values, long int *squares, int size) {

    for(int i = 0; i < size; i++) {
        *(squares + i) = (long int)pow(*(values + i), 2);
    }

}

void print_by_ptr(int *values, long int *squares, int size) {
    
    printf("Value  Square\n");
    printf("-----  ----------\n");

    for(int i = 0; i < size; i++){
        printf("%-5d, %-10d\n", *(values + i), *(squares + i));

    }

}