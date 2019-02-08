#include"read.h"
#include<ctype.h>

int ok(int fd, char *want){

    /* Binary Search variables */
    long int bot = 0;
    long int top = (lseek(fd, 0, SEEK_END) + 1) / WORD_SIZE;    
    long int mid = (bot + top) / 2;

    /* dictionary word */
    char *have = malloc (sizeof(char) * (WORD_SIZE + 1));

    int len = strlen(want);
    /* Search loop */
    while (1) {
        
        /* Position proper read position */       
        lseek(fd, mid * WORD_SIZE, SEEK_SET);                
        //printf("%ld\n", mid); 
        if (mid == bot || mid == top) break;  /* Edge/base case to check. No longer need to loop */
        reed(fd, have);
        int ret = strcmp(want, have);
        printf("ret is %d\n", ret);
        printf("bot is %ld, mid: %ld, top: %ld\n", bot, mid, top);
        printf("have is <%s>\n\n\n", have);
        switch(strCheck(want, have)){
            case -1:  /* Word we are searching for comes before the one we have */
                printf("case -1\n");
                top = mid;
                mid = (bot + top) / 2; 
                break;

            case 0:  /* match */
                printf("case 0\n");
                free(have);
                return 1;

            case 1: /* Word we are searching for comes after one we have */
                printf("case 1\n");
                bot = mid;
                mid = (bot + top) / 2;
        } 
        printf("get here?\n");
    }

    printf("bot: %ld, mid:%ld, top:%ld\n", bot, mid ,top);

    /* Two words left in search space */

    lseek(fd, mid * WORD_SIZE, SEEK_SET); 
    reed(fd, have);
    if (!strcmp(want, have)) {
        free(have);
        return 1;
    }
    
    (mid == bot) ? top: bot;  

    lseek(fd, mid * WORD_SIZE, SEEK_SET);
    reed(fd, have);
    if (!strcmp(want, have)) {
        free(have);
        return 1;
    }
    
    free(have);
    return 0;
}

void reed(int fd, char *buf){
   
    /* read word from file */ 
    if ((read(fd, buf, WORD_SIZE) != WORD_SIZE)){
        printf("error reading word from dictionary\n");
        free(buf);
        exit(1);
    }

    /* Remove trailing whitespace and null-terminate */
    int i = WORD_SIZE;
    buf[i] = '\0';

    while (isspace(buf[--i])) buf[i] = '\0';
    printf("spaceless string <%s>\n", buf);
}

/* wrapper for strcmp */
int strCheck(char *s1, char *s2){

    int ret = strcmp(s1, s2);
   
    if (ret < 0) return -1;
    if (ret == 0) return 0;
    if (ret > 0) return 1; 
}
