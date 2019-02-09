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
