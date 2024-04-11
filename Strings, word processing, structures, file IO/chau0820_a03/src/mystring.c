/**
 * -------------------------------------
 * @file  mystring.c
 * 
 * -------------------------------------
 * @author Iman Chaudhry
 *
 * @version 2024-02-03
 *
 * ------------------------------------- */
 
#include "mystring.h"


/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.  
 *
 * @param s - char pointer to a str
 * @return - return the number of words. 
 */
int str_words(char *s) {
    if (!s) {
        return -1;
    } else {
        int count = 0;
        char *p = s;

        while (*p){
            if ((*p != ' ') && (*(p-1) == ' ' || p == s)){
                count ++;
                }
            p++;
        }
        return count;
    }

}

/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a str
 * @return - return the number of actual flips.   
 */
int str_lower(char *s) {
    if (!s) {
        return -1;
    } else {
        int count = 0;

        while (*s){
            if (*s >= 'A' && *s <= 'Z') {
                *s = *s + ('a' - 'A');
                count ++;
                }
            s++;
        }
        return count;
    }
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a str
 */
void str_trim(char *s) {
    char *p=s, *dp=s;
    while (*p) {
    if (*p!= ' ' || (*p > s && *(p-1) != ' ')) { // pattern
        *dp = *p;
        dp++;  // action
    }   
    p++; // next
    }
}