#ifndef ARRAY_LL_H

#define ARRAY_LL_H

#include <stdbool.h>

typedef struct ArrayLL ArrayLL;
typedef void *ArrListObj;

ArrayLL *arrayLLCreate(int size);
void freeArrayLL(ArrayLL **l);

int arrayLLLength(ArrayLL *l);
int arrayLLIndex(ArrayLL *l);
ArrListObj arrayLLFront(ArrayLL *l);
ArrListObj arrayLLBack(ArrayLL *l);
ArrListObj arrayLLGet(ArrayLL *l);

void arrayLLClear(ArrayLL *l);
void arrayLLSet(ArrayLL *l, ArrListObj value);
void arrayLLMoveFront(ArrayLL *l);
void arrayLLMoveBack(ArrayLL *l);
void arrayLLMovePrev(ArrayLL *l);
void arrayLLMoveNext(ArrayLL *l);
void arrayLLPrepend(ArrayLL *l, ArrListObj value);
void arrayLLAppend(ArrayLL *l, ArrListObj value);
void arrayLLInsertBefore(ArrayLL *l, ArrListObj value);
void arrayLLInsertAfter(ArrayLL *l, ArrListObj value);
ArrListObj arrayLLDeleteFront(ArrayLL *l);
ArrListObj arrayLLDeleteBack(ArrayLL *l);
ArrListObj arrayLLDelete(ArrayLL *l);

#endif
