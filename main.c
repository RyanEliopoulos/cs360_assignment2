#include<fcntl.h>
#include"read.h"
#include<errno.h>


int main(int argc, char *argv[]) {
    
    //char want[10] = "horse"; 
    //char want[WORD_SIZE + 1];
    //printf("%s\n", argv[1]);
    //strcpy(want, argv[1]);
    
    char *want = argv[1];
    printf("<%s>\n", want);   
 
    int fd = open("./dictionaries/webster", O_RDONLY);
    printf("%s\n", strerror(errno));

    printf("%d\n", fd);
    if(ok(fd, want)) {
        printf("yes\n");
        return 1; 
    } 
    else {
        printf("No\n");
        return 2;
    }

}
