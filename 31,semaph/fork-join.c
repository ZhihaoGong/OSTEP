#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common_threads.h"

sem_t s; 

void *child(void *arg) {
    printf("child\n");
    sem_post(&s); 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");  
    sem_init(&s, 0, -2);
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s); 
    printf("parent: end\n");
    sem_destroy(&s); 
    return 0;
}

