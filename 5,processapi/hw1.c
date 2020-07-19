#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 


int main() {
    int x = 100;
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("X value of child process is %d\n", x);
        x = 200;
        printf("X value of child process after changing is %d\n", x);
    } else {
        int rc_wait = wait(NULL);
        printf("X value of parent process is %d\n", x);
    }
    return 1;
}
