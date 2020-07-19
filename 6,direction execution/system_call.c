#include <stdlib.h>
#include <stdio.h>

static int i = 0;

int test_func() {
    printf("hello world again\n");
}

int main() {
  /*   for (int i = 0; i < 500; i++) {
        printf("hello world\n");
    }
    
    printf("hello world again\n");
    printf("hello world again\n");
    printf("hello world again\n");
    printf("hello world again\n"); */
    test_func();
    void * mem = malloc(10000);
  /*   printf("%s", mem); */
}