#include "NormalLL.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    NormalLL *l = normalLLCreate();
    int a = 10;
    normalLLAppend(l, &a);
    printf("%d\n", *(int *) normalLLDeleteFront(l));
    return EXIT_SUCCESS;
}
