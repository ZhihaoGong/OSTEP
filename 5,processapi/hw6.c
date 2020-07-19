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
        printf("pid of child process %d\n.", getpid());
    } else {
        int rc_wait = waitpid(-1, NULL, NULL);
        printf("Wait id %d\n", rc_wait);
    }
    return 1;
}
