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
#include "fibonacci.h"

/**
 *  computes and returns the nth Fibonacci number F(n) using 
 *  iterative algorithm, namely using a for or while loop
 * 
 * @param n - index of the Fibonacci number
 * @return - Fibonacci number F(n) 
 */
int iterative_fibonacci(int n) {
    if (n<=1) {
        return n;
    } else {
        int f1 = 0, f2 = 1, temp = 0;
        for (int i=2; i<=n; i++) {
            temp = f2;
            f2 = f1 + f2;
            f1 = temp;
        }
        return f2;
    }
}

/**
 *  computes and returns the nth Fibonacci number F(n) using 
 *  recursive algorithm, namely using recursion function
 * 
 * @param n - index of the Fibonacci number
 * @return - Fibonacci number F(n)
 */
int recursive_fibonacci(int n) {
    if (n<=1) {
        return n;
    } else {
        return recursive_fibonacci(n-2) + recursive_fibonacci(n-1);
    }
}

/**
 *  computes and returns the nth Fibonacci number F(n) using 
 *  using dynamic programming bottom-up method with external array 
 *  f[n+1] of initial value -1 for all elements. The algorithm fills 
 *  up f[] by f[0]=0, f[1]=1, f[i]= f[i-2]+a[i-1] for i=2,...,n, and 
 *  return f[n].
 * 
 * @param *f - pointer to an array of integers
 * @param n - index of the Fibonacci number
 * @return - Fibonacci number F(n)
 */
int dpbu_fibonacci(int *f, int n) {
    f[0] = 0; 
    f[1] = 1;

    if (n == 0 || n == 1) {
        return f[n];
    } else {
        for (int i = 2; i <= n; i++) {
            f[i] = f[i-2] + f[i-1];
        }
        return f[n];
    }
}

/**
 *  computes and returns the Fibonacci number F(n) using dynamic 
 *  programming top-down method with external array f[n+1] of initial 
 *  value -1 for all elements. It fills up f[n+1] by recursion function 
 *  call. Specifically it returns f[n] if f[n]!=-1 else sets 
 *  f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1) and then returns f[n]
 * 
 * @param *f - pointer to an array of integers
 * @param n - index of the Fibonacci number
 * @return - Fibonacci number F(n)
 */
int dptd_fibonacci(int *f, int n) {
    if (n<=1) {
        f[n]=n; return f[n];
        }
    if (f[n] > 0) {
        return f[n];
    } else {
        f[n] = dptd_fibonacci(f, n-2) + dptd_fibonacci(f, n-1);
    return f[n];
    }   
}