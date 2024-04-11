/**
 * -------------------------------------
 * @file  bigint.c
 * Assignment 1 C File
 * -------------------------------------
 * @author Iman Chaudhry 210650820
 *
 * @version 2024-02-17
 *
 * ------------------------------------- */
 
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *p) {
  BIGINT bi = {0};
  if (p == NULL) 
    return bi;
  else if (!(*p >= '0' && *p <= '9')) {
    return bi;
  }
  else if (*p == '0' && *(p+1) == '\0') {
    dll_insert_end(&bi, new_node(*p -'0'));
    return bi;
  } else { 
    while (*p) {
      if (*p >= '0' && *p <= '9' ){
        dll_insert_end(&bi, new_node(*p -'0'));
      } else {
        dll_clean(&bi);
        break;
      }
      p++;
    }
    return bi;
  }
}

BIGINT bigint_add(BIGINT op1, BIGINT op2) {
  BIGINT sum = {NULL};
  NODE *p1 = op1.end;
  NODE *p2 = op2.end;
  int c=0, a, b, s;

  while (p1 || p2) { 
    a = 0;
    b = 0;
    if (p1) {
      a = p1->data; 
      p1 = p1->prev;
    }
    if (p2) {
      b = p2->data; 
      p2 = p2->prev;
    }
        
    s = a + b + c;
    c = s/10;

    dll_insert_start(&sum, new_node(s % 10));
  }

  if (c==1) {
    dll_insert_start(&sum, new_node(1));
  }
    
  return sum;
}

BIGINT bigint_fibonacci(int n) {
  BIGINT temp = bigint(NULL);
  BIGINT f1 = bigint("0");
  BIGINT f2 = bigint("1");

	if (n == 0) return f1;
	else if (n == 1) return f2;
	else {
		for (int i = 2; i <= n; i++) {
			temp = bigint_add(f1, f2);
			dll_clean(&f1);
			f1 = f2;
			f2 = temp;
		}
		dll_clean(&temp);
	}

	return f2;
}