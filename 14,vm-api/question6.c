#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main() {
    for (int i = 0; i < 10; i++) {
        int * a = malloc(100 * sizeof(int));
        sleep(3000);
    }
}