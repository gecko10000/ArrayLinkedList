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
        if (*(int *) normalLLDeleteBack(l) != SIZE - i - 1) {
            fprintf(stderr, "DeleteBack does not match.\n");
            exit(EXIT_FAILURE);
        }
        if (*(int *) normalLLDeleteFront(l) != i) {
            fprintf(stderr, "DeleteFront does not match.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (SIZE % 2 == 1) {
        normalLLDeleteBack(l);
    }
    if (normalLLLength(l) != 0) {
        exit(EXIT_FAILURE);
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
        if (*(int *) arrayLLDeleteBack(l) != SIZE - i - 1) {
            fprintf(stderr, "DeleteBack does not match.\n");
            exit(EXIT_FAILURE);
        }
        if (*(int *) arrayLLDeleteFront(l) != i) {
            fprintf(stderr, "DeleteFront does not match.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (SIZE % 2 == 1) {
        arrayLLDeleteBack(l);
    }
    if (arrayLLLength(l) != 0) {
        exit(EXIT_FAILURE);
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
