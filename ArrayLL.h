#ifndef NORMAL_LL_H

#define NORMAL_LL_H

#include <stdbool.h>

typedef struct ArrayLL ArrayLL;
typedef void *ListObj;

ArrayLL *arrayLLCreate(void);
void freeArrayLL(ArrayLL **l);

int arrayLLLength(ArrayLL *l);
int arrayLLIndex(ArrayLL *l);
ListObj arrayLLFront(ArrayLL *l);
ListObj arrayLLBack(ArrayLL *l);
ListObj arrayLLGet(ArrayLL *l);

void arrayLLClear(ArrayLL *l, bool freeValues);
void arrayLLSet(ArrayLL *l, ListObj value);
void arrayLLMoveFront(ArrayLL *l);
void arrayLLMoveBack(ArrayLL *l);
void arrayLLMovePrev(ArrayLL *l);
void arrayLLMoveNext(ArrayLL *l);
void arrayLLPrepend(ArrayLL *l, ListObj value);
void arrayLLAppend(ArrayLL *l, ListObj value);
void arrayLLInsertBefore(ArrayLL *l, ListObj value);
void arrayLLInsertAfter(ArrayLL *l, ListObj value);
ListObj arrayLLDeleteFront(ArrayLL *l);
ListObj arrayLLDeleteBack(ArrayLL *l);
ListObj arrayLLDelete(ArrayLL *l);

#endif
