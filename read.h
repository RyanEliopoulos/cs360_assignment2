#define WORD_SIZE 16
#define DICTIONARY ./dict/tiny

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ok(int, char *);
void reed(int, char *);
int strCheck(char *, char *);
