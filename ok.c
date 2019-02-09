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


/* Makes sure program is given 1 word to search for */
/* truncates word if longer than WORD_SIZE */
void checkArgs(int, char *[]);

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


/* closes dictionary file before exit */
/* takes file descriptor and exit code */
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


/********           Program Begins      ********/

int main(int argc, char *argv[]) {

    /* quick check for argument validity */
    checkArgs(argc, argv);     

    /* open file */
    int fd;
    if ((fd = open(DICTIONARY, O_RDONLY)) == -1) {  
        fprintf(stderr, "Error reading from dictionary.\n%s\n", strerror(errno));        
        exit(ERR_DICT_OPEN);
    }

    /* search dictionary */
    if(ok(fd, argv[1])) { 
        printf("Yes\n");
        return 0; 
    } 
    else {
        printf("No\n");
        return -1;
    }
}


void checkArgs(int argc, char *argv[]) {

    if (argc == 1) {
        fprintf(stderr, "Must include a word to search for\n"); 
        exit(ERR_ARG); 
    }

    if (argc > 2) {
        fprintf(stderr, "Too many arguments. Include only one word to search for \n");
        exit(ERR_ARG);
    }

    /* truncate search term if length exceeds word size */
    if (strlen(argv[1]) > WORD_SIZE) {
        argv[1][WORD_SIZE - 1] = '\0';  
    }
}


int ok(int fd, char *want) {

    /* Binary Search variables */
    long int bot = 0;
    long int top = (seekWrapper (fd, 0, SEEK_END) + 1) / WORD_SIZE;    
    long int mid = (bot + top) / 2;

    /* dictionary word */
    char *have = malloc (sizeof (char) * (WORD_SIZE + 1));

    /* Search loop */
    while (1) {
        
        /* Position proper read position */       
        seekWrapper(fd, mid * WORD_SIZE, SEEK_SET);                

        if (mid == bot || mid == top) break; /* Search space is two lines ('base case'), handle after loop */

        /* Read dictionary word and compare against want */
        readCustom(fd, have);

        int ret = strcmp(want, have);
        printf("ret is %d\n", ret);
        printf("bot is %ld, mid: %ld, top: %ld\n", bot, mid, top);
        printf("have is <%s>\n\n\n", have);
        switch (strCheck (want, have)) {
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

    /* Two words left in search range */
    /* mid is equal in value either to bot or top */
    seekWrapper(fd, mid * WORD_SIZE, SEEK_SET); 
    readCustom(fd, have);
    if (!strcmp(want, have)) {
        free(have);
        return 1;
    }
    
    (mid == bot) ? top: bot; /* it wasn't the first. So check the second */

    seekWrapper(fd, mid * WORD_SIZE, SEEK_SET);
    readCustom(fd, have);
    if (!strcmp (want, have)) {
        free(have);
        return 1;
    }
    
    free(have);
    return 0;
}


off_t seekWrapper(int fd, off_t read_amount, int whence) {

    off_t ret = lseek(fd, read_amount, whence); 
    
    /* checking for lseek errors */ 
    if (ret == -1) {
        fprintf(stderr, "Error read at offset %d.\n %s\n", whence, strerror(errno));
        exitWrapper(fd, ERR_LSEEK);
    }
}


void readCustom(int fd, char *buf) {

    /* read word from file */ 
    int ret = read(fd, buf, WORD_SIZE);   

    /* check read for errors */
    if (ret  == -1) {
        fprintf(stderr, "error reading word from dictionary.\n %s", strerror(errno)); 
        free(buf);
        exitWrapper(fd, ERR_DICT_READ);
    }

    /* check for nonsense */
    if (ret < WORD_SIZE) {
        fprintf(stderr, "failed to read and entire word for some reason\n");
        free(buf);
        exitWrapper(fd, ERR_DICT_READ);
    }

    /* Remove trailing whitespace and null-terminate */
    int i = WORD_SIZE;
    buf[i] = '\0';

    while (isspace(buf[--i])) buf[i] = '\0';
}


void exitWrapper(int fd, int exit_code) {

    closeWrapper(fd);
    exit(exit_code);
}


void closeWrapper(int fd) {

    if (close(fd) == -1) {
        fprintf(stderr, "Error while closing dictionary file.\n%s\n", strerror(errno));
        exit(ERR_DICT_CLOSE); 
    }
}


int strCheck(char *s1, char *s2) {

    int ret = strcmp(s1, s2);
   
    if (ret < 0) return -1;
    if (ret == 0) return 0;
    if (ret > 0) return 1; 
}
