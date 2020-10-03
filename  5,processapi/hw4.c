#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 


int main () {
    int pid = fork();
    if (pid < 0) {
        printf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        char *myargs[2];
        myargs[0] = "/bin/ls";
        myargs[1] = NULL;
        // execvp(myargs[0], myargs); // runs word count
        execl(myargs[0], myargs);
    } else {
        int rc_wait = wait(NULL);
        printf("Wait id %d\n", rc_wait);
    }
    return 1;
}
