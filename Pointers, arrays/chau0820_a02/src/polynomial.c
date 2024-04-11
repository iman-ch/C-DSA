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
#include <stdio.h>
#include <math.h>
#include "polynomial.h"

#define EPSILON 1e-6

/**
 *  computes and returns the value of the following 
 *  polynomial p(x) of order n and coefficients 
 *  p[0], …, p[n-1], namely

 */
float horner(float *p, int n, float x){
    float r=0;
    for(int i=0; i<n;i++){
        r = r*x + p[i]; 
    }
    return r;
}

/**
 *  finds an approximate real root c in interval [a, b] of 
 *  polynomial P(x), using the bisection method. Use the 
 *  fault-tolerant 1e-6 (or 0.000001) as a stop condition, 
 *  i.e., if x0 is the actual root, stop the iteration if 
 *  |c-x0|<1e-6 or |P(c)| < 1e-6.
 */
float bisection(float *p, int n, float a, float b){
    float c = (a + b) / 2;
    while (fabs(horner(p, n, c)) > EPSILON && fabs(a - b) > EPSILON) {
        if (horner(p, n, c) * horner(p, n, a) > 0) {
            a = c;
        } else {
            b = c;
        }
        c = (a + b) / 2;
    }
    return c;
}