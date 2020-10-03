#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>

#define NUMTHREAD 4
#define LOOP 1000000

#include <time.h>
#include <sys/time.h>

int global = 0;
int threadshold = 1000000;
__thread int counter = 0;
pthread_mutex_t lock; 


void * increase_counter() {
    int i = 0;
    do {
        if (counter == threadshold) {
            pthread_mutex_lock(&lock);
            global += counter;
            pthread_mutex_unlock(&lock);
            counter = 0;
        }
        counter++;
        i++;
    } while(i <= LOOP);
}


int main(int argc, char *argv[]) {
    // initizalize lock
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

    int error;
    pthread_t tid[NUMTHREAD];

    struct timeval t0;
    struct timeval t1;

    gettimeofday(&t0, 0);

    for (int i = 0; i < NUMTHREAD; i++) {
        error = pthread_create(&(tid[i]), 
                               NULL, 
                               &increase_counter, NULL); 

        if (error != 0) {
            printf("\nThread can't be created");
            return 1;
        }
    }

    for  (int i = 0; i < NUMTHREAD; i++) {
        pthread_join(tid[i], NULL); 
    }
    gettimeofday(&t1, 0);
    long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000000 + (t1.tv_usec-t0.tv_usec) * 1000;
    
    printf("elapsed: %lld\n", elapsed);
    printf("global variable %d", global);
    pthread_mutex_destroy(&lock); 
}

