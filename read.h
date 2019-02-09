#define WORD_SIZE 16
#define DICTIONARY "./dictionaries/tiny"

/* Error exit codes */
#define ERR_ARG 1           /* 1: issue parsing arguments */
#define ERR_LSEEK 2         /* 2: lseek failed */
#define ERR_DICT_READ 3     /* 3: issue reading word from dictionary */
#define ERR_DICT_OPEN 4     /* 4: failed to open dictionary */

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>


int ok(int, char *);

/* docs say off_t is "..no narrower than an int". storing it in a long int should be fine..? */
off_t elseek(int, off_t, int);
void reed(int, char *);
int strCheck(char *, char *);
