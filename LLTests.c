#include "NormalLL.h"
#include "ArrayLL.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void) {
    NormalLL *n = normalLLCreate();
    int *ints = malloc(SIZE * sizeof(*ints));
    for (int i = 0; i < SIZE; i++) {
        ints[i] = i;
        normalLLAppend(n, ints + i);
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", *(int *) normalLLDeleteBack(n));
    }

    ArrayLL *a = arrayLLCreate(SIZE);
    for (int i = 0; i < SIZE; i++) {
        arrayLLAppend(a, ints + i);
    }
    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", *(int *) arrayLLDeleteFront(a));
    }
    freeNormalLL(&n);
    freeArrayLL(&a);
    free(ints);
    return EXIT_SUCCESS;
}
