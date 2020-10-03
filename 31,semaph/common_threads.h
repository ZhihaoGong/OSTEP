#include <pthread.h>


int Pthread_create(pthread_t * thread,
                    const pthread_attr_t * attr,
                    void * (*start_routine)(void *),
                    void *arg) {
    return pthread_create(thread, attr, start_routine, arg);
}

int Pthread_join(pthread_t thread, void **retval) {
    return pthread_join(thread, retval);
}