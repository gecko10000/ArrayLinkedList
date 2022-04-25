#include "NormalLL.h"
#include "ArrayLL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 200000000

int vals[SIZE];

void normalTest() {
    printf("---Normal Linked List---\n");
    time_t start = time(NULL);
    NormalLL *l = normalLLCreate();
    for (int i = 0; i < SIZE; i++) {
        normalLLAppend(l, vals + i);
    }
    printf("Appended in %lu seconds.\n", time(NULL) - start);
    start = time(NULL);
    for (int i = 0; i < SIZE / 2; i++) {
        normalLLDeleteBack(l);
        normalLLDeleteFront(l);
    }
    if (SIZE % 2 == 1) {
        normalLLDeleteBack(l);
    }
    printf("Deleted in %lu seconds.\n", time(NULL) - start);
    freeNormalLL(&l);
}

void arrayTest() {
    printf("---Array Linked List---\n");
    time_t start = time(NULL);
    ArrayLL *l = arrayLLCreate(SIZE);
    for (int i = 0; i < SIZE; i++) {
        arrayLLAppend(l, vals + i);
    }
    printf("Appended in %lu seconds.\n", time(NULL) - start);
    start = time(NULL);
    for (int i = 0; i < SIZE / 2; i++) {
        arrayLLDeleteBack(l);
        arrayLLDeleteFront(l);
    }
    printf("Deleted in %lu seconds.\n", time(NULL) - start);
    freeArrayLL(&l);
}

int main(void) {
    for (int i = 0; i < SIZE; i++) {
        vals[i] = i;
    }
    normalTest();
    arrayTest();
    return EXIT_SUCCESS;
}
