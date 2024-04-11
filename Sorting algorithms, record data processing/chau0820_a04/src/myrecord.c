/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mysort.h"
#include "myrecord.h"

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77) B=[70, 73),
 * C+=[67, 70), C=[63, 77), C-=[60, 63), D+=[57,60),D=[53,57),D=[50,53), F=[0,50).
 *
 * @param score -  percetage grade.
 *
 * @return - letter grade wrapped in GRADE structure type.
 */
GRADE grade(float score){
   GRADE r = {"F"}; 
   int p = (int) round(score);
   char g[14][5] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};
   int b[] = {100, 90, 85, 80, 77, 73, 70, 67, 63, 60, 57, 53, 50, 0};
   int i=0, n = sizeof(b)/sizeof(float);
   for (i=0; i<n; i++) {
      if (score >= b[i+1]) break;
   }
   strcpy(r.letter_grade, g[i]);
   return r;
}

/*
 *  Take the RECORD data array as input, compute the average score, standard deviation,
 *  median of the score values of the record data, and returns the results in STATS type.
 *
 *  @param dataset -  input record data array.
 *  @param count -  the number of data record in dataset array.
 *  @return  -  stats value in STATS type.
 */
STATS process_data(RECORD *dataset, int count) {    
   STATS stats = {0};
   // mean
   stats.count = count;
   float sum = 0;
   for(int i=0; i<count; i++) sum += dataset[i].score;
   stats.mean = sum/count;

   // stddev
   float var = 0;
   for(int i=0; i<count; i++) var += pow(dataset[i].score - stats.mean, 2);
   stats.stddev = sqrt(var / count);

   // median
   float *scores[count];
   for(int i = 0; i < count; i++) scores[i] = &dataset[i].score;
   quick_sort_inc(scores, 0, count-1);
   if (count % 2 != 0){
      stats.median = *scores[count/2];
   } else {
      stats.median = (*scores[count /2-1] + *scores[count /2])/2;
   }
   return stats;
}

/*
 *  Import record data from file and retrieves and stores all record entries
 *  in the RECORD array passed by records, and returns the number of record count.
 *
 *  @param *fp -  FILE pointer to intput file.
 *  @param dataset - array of RECODR type to store record data.
 *  @return   - number record count
 */
int import_data(FILE *fp, RECORD *dataset) {
   char delimiters[] = " ,\n\r";
   char line[512];
   int i = 0;

   while (fgets (line, sizeof(line), fp) != NULL ){
      sscanf(line, "%[^, ],%f", dataset[i].name, &dataset[i].score);
      i++;
   }
   return i;
}

/*
 *  This function takes output file named outfilename, 
 *  RECORD array by records,and output stats information,
 *   and processed record data to files in required format.
 *
 *  @param *fp -  FILE pointer to output file.
 *  @param count -  the number of data record in dataset array.
 *  @return - returns 1 if successful; 0 if count < 1
 */
int report_data(FILE *fp, RECORD *dataset, int count) {
   if (count < 1){
      return 0;
   }
   fprintf(fp, "\nName,Score,Grade\n");
   for (int i = 0; i < count; i++) {
      fprintf(fp, "\n%s,%.1f,%c", dataset[i].name, dataset[i].score, grade(dataset[i].score));
   }
   return 1;
}
