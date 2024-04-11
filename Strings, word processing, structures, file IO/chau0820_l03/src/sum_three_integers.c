/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2023-09-09
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {

    int num1, num2, num3;


    while (1) {
        printf("Enter three comma-separated integers: ");

        if (scanf("%d,%d,%d", &num1, &num2, &num3) == 3) {
            return num1 + num2 + num3;
        } else {
            while (getchar() != '\n');
            printf("Invalid input. Please try again.\n");
        }
    }

}