#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 


int main () {
    int pfd[2];
    if (pipe(pfd) == -1) { 
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        printf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("pid of child process %d\n.", getpid());
    } else {
        close(pfd[0]);
        wait(NULL);
        int rc_wait = waitpid(-1, NULL, NULL);
        printf("Wait id %d\n", rc_wait);
    }
    return 1;
}


//     if (cpid == 0) {    /* Child reads from pipe */
//         close(pfd[1]);          /* Close unused write end */
//         while (read(pfd[0], &buf, 1) > 0)
//             write(STDOUT_FILENO, &buf, 1);
//         write(STDOUT_FILENO, "\n", 1);
//         close(pfd[0]);
//         _exit(EXIT_SUCCESS);
//     } else {            /* Parent writes argv[1] to pipe */
//         close(pfd[0]);          /* Close unused read end */
//         write(pfd[1], argv[1], strlen(argv[1]));
//         close(pfd[1]);          /* Reader will see EOF */
//         wait(NULL);             /* Wait for child */
//         exit(EXIT_SUCCESS);
//     }
