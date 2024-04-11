/**
 * -------------------------------------
 * @file  file name
 * Assignment 1  Header File
 * -------------------------------------
 * @author your name, your WLU ID, your WLU email
 *
 * @version the date of creating this file in format like 2024-01-08
 *
 * ------------------------------------- */
#include "mychar.h"

/**
 * Determine the type of a char character. 
 *
 * @param c - char type value
 * @return - 0 if c is a digit, 1 if c is an arithmetic operator, 2 if c is an English letter; otherwise -1. 
 */
int mytype(char c) {
    int i = -1;
    if (c >= '0' && c <= '9') {
        i=0;
    }
    else if (c >= '+' && c <= '/' && c != ','){
        i=1;
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        i=2;
    }

    return i;

}


/**
 * Flip the case of an English character. 
 *
 * @param c - char type value of ASCII code of English letter.
 * @return  -  c's upper/lower case letter if c is a lower/upper case English letter. 
 */
char case_flip(char c) {
    if (c >= 'A' && c <= 'Z'){
        c = c + ('a' - 'A');
    }
    else if (c >= 'a' && c <= 'z'){
        c = c - ('a' - 'A');
    }

    else {
        printf("invalid c.  \n");
    }

    return c;
}

/**
 * Convert digit character to the corresponding integer value.
 *
 * @param c - char type value of ASCII code of digit charactor.
 * @return - its corresponding integer value if c is a digit character. 
 */
int char_to_int(char c) {
    int i = c - '0';
    return i;
}