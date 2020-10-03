#include <stdio.h>
#include <stdlib.h>


int main() {
    int * mem = (int *) malloc(1000000 * sizeof(int));

    int count = 0;
    while (1) {
        count++;
        for (int i = 0; i < 1000000; i++) {
            *(mem + i) = i;
            printf("%d\n", *(mem + i));
        }
        printf("loop %d\n", count);
    }
}