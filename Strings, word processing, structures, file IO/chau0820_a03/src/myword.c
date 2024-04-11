/**
 * -------------------------------------
 * @file  myword.c
 * 
 * -------------------------------------
 * @author Iman Chaudhry
 *
 * @version 2024-02-03
 *
 * ------------------------------------- */

#include <stdio.h>
#include <string.h>
#include "myword.h"
#include "mystring.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

// You can copy here the functions in mysttring.c if you want to use them in the
// following functions. You can also add other auxiliary functions here. 

/*
 * Define enumeration type BOOLEAN with value FASLE = 0 and TRUE 1.
 */

/*
 * Define structure type WORD consists of char word[20] to store a word, int count to hold frequency of the word.
 */

/*
 * Define structure type WORDSTATS consisting of int line_count, int word_count, and int keyword_count to represent
 * to represent the number of lines, number of all words, and the number of different non-common-word in text data.
 */

/*
 * Find the index of a word in the given array of WORD structures.
 * 
 * @param *words - WORD pointer to an array of WORD structures.
 * @param size - Size of the array.
 * @param *target - char pointer to the word being searched for.
 * @return - Index of the word in the array if found, -1 otherwise.
 */
int find_word_index(WORD *words, int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(words[i].word, target) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Insert a new word at the end of the given array of WORD structures.
 * 
 * @param *words - WORD pointer to an array of WORD structures.
 * @param *size - Pointer to the size of the array. Updated if insertion is successful.
 * @param *new_word - char pointer to the new word to be inserted.
 */
void insert_word_at_end(WORD *words, int *size, const char *new_word) {
    if (*size < MAX_WORDS) {
        strcpy(words[*size].word, new_word);
        words[*size].count = 1;
        (*size)++;
    }
}

/*
 * Load word data from file, and insert words a directory represented by char array.
 * 
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored. 
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.   
 */
int create_dictionary(FILE *fp, char *dictionary) {
    char line[1000];
    char delimiters[] = " .,\n\t\r";
    char *token;
    int count = 0;
    while (fgets(line, 1000, fp) != NULL) {
        token = (char*) strtok(line, delimiters);
        while (token != NULL) {
            str_lower(token);
            strcat(dictionary, token);
            strcat(dictionary, ",");

            token = strtok(NULL, delimiters); // Get the next word from the line.
            count++;
        }
    }
    return count;
}

/*
 * Determine if a given word is contained in the given dictionary.  
 * 
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.  
 *                     
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.   
 */
BOOLEAN contain_word(char *dictionary, char *word) {
    if (word == NULL || *word == '\0') return 0;
    else {
        char temp[20] = {0};
        strcpy(temp, ",");
        strcat(temp, word);
        strcat(temp, ",");
        return strstr(dictionary, temp) != NULL ? 1 : 0;
    }
}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.   
 * 
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.    
 *                     
 * @return - WORDSTATS value of processed word stats information.   
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
    WORDSTATS ws = { 0 };
    char line[MAX_LINE_LEN];
    char delimiters[] = " .,\n\t\r";
    char *word_token;

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        ws.line_count++;
        str_lower(line);

        word_token = strtok(line, delimiters);

        while (word_token != NULL) {
            ws.word_count++;

            if (!contain_word(dictionary, word_token)) {
                int index = find_word_index(words, ws.keyword_count, word_token);

                if (index == -1) {
                    insert_word_at_end(words, &ws.keyword_count, word_token);
                } else {
                    words[index].count++;
                }
            }

            word_token = strtok(NULL, delimiters);
        }
    }

    return ws;
}