/**
 * -------------------------------------
 * @file  bigint.h
 * Assignment 1 Header File
 * -------------------------------------
 * @author Iman Chaudhry 210650820
 *
 * @version 2024-02-17
 *
 * ------------------------------------- */
 
#ifndef BIGINT_H
#define BIGINT_H
#include "dllist.h"

typedef DLL BIGINT;
BIGINT bigint(char *digitstr);
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2);
BIGINT bigint_fibonacci(int n);

#endif