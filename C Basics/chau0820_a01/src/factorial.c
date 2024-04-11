#include <stdio.h>
/**
 * Compute the factorial n! and does overflow detection. 
 *
 * @param n - a positive integer value
 * @return -  the factorial n! if it is not overflow; otherwise 0. 
 */

int factorial(int n){
    int f = 1;
    if(n >= 1) {
        for(int i = 1; i <= n; i++) {
        int temp = f;
        f *= i;
            if ((f > temp) && (temp != f/i)) {
                return 0;
            }
        }
    }
return f;

}
