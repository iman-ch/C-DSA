/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {
    BSTNODE *node = bst_search(ds->root, record.name);
    if (node == NULL){
        bst_insert(&(ds->root), record);    
        
        float count = (float)ds->count;
        float newCount = count + 1.0f;
        float newMean = (count * ds->mean + record.score) / newCount;
        float newVariance = (((count * (ds->stddev * ds->stddev)) + (record.score - ds->mean) * (record.score - newMean)) / newCount);

        ds->count = (int)newCount;
        ds->mean = newMean;
        ds->stddev = sqrtf(newVariance);

    }
}

void remove_record(BSTDS *ds, char *name) {
    BSTNODE *node = bst_search(ds->root, name);
    if (node != NULL){
        int score = node->data.score;
        bst_delete(&(ds->root), name);

        float count = (float)ds->count;
        float newCount = count - 1.0f;
        float newMean = (count * ds->mean - score) / newCount;
        float newVariance = ((count * (ds->stddev * ds->stddev) - (score - ds->mean) * (score - newMean)) / newCount);

        ds->count = (int)newCount;
        ds->mean = newMean;
        ds->stddev = sqrtf(newVariance);

        if (ds->count == 0){
            clean_bstds(ds);
        }

    } else if (ds->count == 1) {
        bst_delete(&(ds->root), name);
    }
}

void clean_bstds(BSTDS *ds) {
  clean_bst(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}