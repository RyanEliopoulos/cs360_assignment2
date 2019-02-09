#define WORD_SIZE 16
#define DICTIONARY "./dictionaries/webster"

/* Error exit codes */
#define ERR_ARG 1           /* 1: issue parsing arguments */
#define ERR_LSEEK 2         /* 2: lseek failed */
#define ERR_DICT_READ 3     /* 3: issue reading word from dictionary */
#define ERR_DICT_OPEN 4     /* 4: failed to open dictionary */
#define ERR_DICT_CLOSE 5    /* 5: failed to close dictionary */

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>
#include<fcntl.h>


/* primary logic here */
/* takes file descriptor and search word */
int ok(int, char *);

/* docs say off_t is "..no narrower than an int". storing it in a long int should be fine..? */
/* lseek wrapper with error handling */
/* needs to be tested */
off_t seekWrapper(int, off_t, int);

/* reads word from dictionary file into buf and removes trailing whitespace */
/* Needs to be tested. somehow The errors, anyway. The rest functions as expected */
void readCustom(int, char *);

/* takes file descriptor and exit code */
/* includes call to closeWrapper */
void exitWrapper(int, int);

/* takes file descriptor */
/* adds error check */
void closeWrapper(int);

/* strcmp wrapper */
/* bins strcmp return values into < 0, 0, > 0 */
int strCheck(char *, char *);

/* Checks program arguments for validity */
/* truncates search word to WORD_SIZE */
void checkArgs(int, char*[]);
