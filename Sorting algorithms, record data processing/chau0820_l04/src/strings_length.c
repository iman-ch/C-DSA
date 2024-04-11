/**
 * -------------------------------------
 * @file  strings_length.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2024-02-03
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_length(strings_array *data, FILE *fp_short, FILE *fp_long, int length) {
    for (int i =0; i < (*data).lines; i++) {
        if (strlen((*data).strings[i]) <= length) {
            fputs((*data).strings[i], fp_short);
        }
        else if (strlen((*data).strings[i]) > length) {
            fputs((*data).strings[i], fp_long);
        }
    }
    return;
}
