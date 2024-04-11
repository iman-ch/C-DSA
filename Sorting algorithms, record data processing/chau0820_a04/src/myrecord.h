/*
 * your program signature
 */ 

#ifndef MYRECORD_H
#define MYRECORD_H

typedef struct {
  char name[20];
  float score;
} RECORD;

typedef struct {
  int count;
  float mean;
  float stddev;
  float median;
} STATS;

typedef struct {
  char letter_grade[3];
} GRADE;

int binary_search_iter(int a[], int left, int right, int x);

GRADE grade(float score);

int import_data(FILE *fp, RECORD *dataset); 

STATS process_data(RECORD *dataset, int count);

int report_data(FILE *fp,  RECORD *dataset, int count);

#endif