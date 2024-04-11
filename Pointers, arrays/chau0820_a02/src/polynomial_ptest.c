/*
--------------------------------------------------
File:    polynomial_ptest.c
About:   public test driver
Author:  HBF
Version: 2024-01-15
Compile: gcc -std=c99 polynomial.c polynomial_ptest.c
--------------------------------------------------
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "polynomial.h"

void display_polynomial(float p[], int n) {
	printf("p(x)=");
	for (int i = 0; i < n - 1; i++) {
		printf("%.2f*x^%d+", p[i], n - i - 1);
	}
	printf("%.2f", p[n - 1]);
}

void test_horner() {
	printf("------------------\n");
	printf("Test: horner\n\n");
	float p[] = { 1, 2, 3, 4 };
	int n = sizeof(p) / sizeof(float);
	display_polynomial(p, n);
	printf("\n");
	float x[] = { 0, 1, 10 };
	int count = sizeof(x) / sizeof(float);
	for (int i = 0; i < count; i++) {
		printf("horner(p %.2f): %.2f\n", x[i], horner(p, n, x[i]));
	}
	printf("\n");
}

void test_bisection()
{
	printf("------------------\n");
	printf("Test: bisection\n\n");
	float p[] = { 1, 2, 3, 4 };
	int n = sizeof(p) / sizeof(float);

	float a = -2, b = 2;
	float pa = horner(p, n, a);
	printf("p(%.2f): %.2f\n", a, pa);
	float pb = horner(p, n, b);
	printf("p(%.2f): %.2f\n", b, pb);
	if (pa * pb <= 0) {
		float root = bisection(p, n, a, b);
		printf("bisection(p %.2f %.2f): %.2f\n", a, b, root);
		printf("p(%.2f): %.2f\n", root, horner(p, n, root));
	}
	printf("\n");
}

int main() {
	test_horner();
	test_bisection();
	return 0;
}
