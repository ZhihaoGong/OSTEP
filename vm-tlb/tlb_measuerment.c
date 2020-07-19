#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <assert.h>


#define handle_error_en(en, msg) \
           do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./measure <number of pages>");
        exit(1);
    }

    // pin a thread
    cpu_set_t cpuset;
    pthread_t thread;
    thread = pthread_self();

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0)
        handle_error_en(s, "pthread_setaffinity_np");
    
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0)
        handle_error_en(s, "pthread_getaffinity_np");
    assert(CPU_ISSET(0, &cpuset));

    
    // start measurement
    struct timeval start_time;
    struct timeval end_time;
  

    int numPages = atoi(argv[1]);
    long pagesize = sysconf(_SC_PAGE_SIZE);

    int jump = pagesize / sizeof(int);
    int *a = (int *)malloc(sizeof(int) * (numPages * jump));

    int loop = 10000;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < loop; i++)
    {
        for (int j = 0; j < numPages * jump; j += jump)
        {
            a[j] += 1;
        }
    }

    gettimeofday(&end_time, NULL);

    double diff_sec = (end_time.tv_sec - start_time.tv_sec) * 1e9;
    double diff_msec = (end_time.tv_usec - start_time.tv_usec) * 1e3;
    double all_diff = (diff_sec + diff_msec);
    double result = all_diff / (numPages * loop);
    // printf("all diff %lf\n", all_diff);

    FILE *fp;
    fp = fopen("tlb_measure.dat", "a");
    fprintf(fp, "%d    %lf\n", numPages, result);
    fclose(fp);
}