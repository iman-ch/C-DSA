/**
 * -------------------------------------
 * @file  file name
 * 
 * -------------------------------------
 * @author your name, your WLU ID, your WLU email
 *
 * @version the date of creating this file in format like 2024-01-08
 *
 * ------------------------------------- */
#ifndef MATRIX_H
#define MATRIX_H
 
float norm(float *v, int n);
float dot_product(float *v1, float *v2, int n);
void matrix_multiply_vector(float *m, float *v1, float *v2, int n);
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n);

#endif