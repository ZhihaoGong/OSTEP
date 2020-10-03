#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 


int main () {
    FILE *fp;
    fp  = fopen ("data.txt", "w");
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        fprintf(fp, "Child process lol.");
    } else {
        fprintf(fp, "Parent process lol.");
    }
    return 1;
}
