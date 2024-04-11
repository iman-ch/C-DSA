/**
 * -------------------------------------
 * @file  myword.h
 * 
 * -------------------------------------
 * @author Iman Chaudhry
 *
 * @version 2024-02-03
 *
 * ------------------------------------- */
#ifndef MYWORD_H
#define MYWORD_H

typedef enum boolean {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef struct word {
    char word[20];
    int count;
} WORD;

typedef struct wordstats {
    int line_count;
    int word_count;
    int keyword_count;
} WORDSTATS;

int create_dictionary(FILE *fp, char *dictrionay);

BOOLEAN contain_word(char *dictionary, char *word);

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary);

#endif