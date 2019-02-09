#include"read.h"

void checkArgs(int, char *[]);

int main(int argc, char *argv[]) {

    /* quick check for argument validity */
    checkArgs(argc, argv);     

    /* open file */
    int fd;
    if ((fd = open(DICTIONARY, O_RDONLY)) == -1) {  // This works
        fprintf(stderr, "Error reading from dictionary.\n%s\n", strerror(errno));        
        exit(ERR_DICT_OPEN);
    }

    /* search dictionary */
    if(ok(fd, argv[1])) { 
        printf("yes\n");
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

