#include "NormalLL.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void) {
    NormalLL *l = normalLLCreate();
    int *ints = malloc(SIZE * sizeof(*ints));
    for (int i = 0; i < SIZE; i++) {
        ints[i] = i;
        normalLLAppend(l, ints + i);
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", *(int *) normalLLDeleteBack(l));
    }
    return EXIT_SUCCESS;
}
