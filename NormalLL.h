#ifndef NORMAL_LL_H

#define NORMAL_LL_H

#include <stdbool.h>

typedef struct NormalLL NormalLL;
typedef void *ListObj;

NormalLL *normalLLCreate(void);
void freeNormalLL(NormalLL **l);

int normalLLLength(NormalLL *l);
int normalLLIndex(NormalLL *l);
ListObj normalLLFront(NormalLL *l);
ListObj normalLLBack(NormalLL *l);
ListObj normalLLGet(NormalLL *l);

void normalLLClear(NormalLL *l, bool freeValues);
void normalLLSet(NormalLL *l, ListObj value);
void normalLLMoveFront(NormalLL *l);
void normalLLMoveBack(NormalLL *l);
void normalLLMovePrev(NormalLL *l);
void normalLLMoveNext(NormalLL *l);
void normalLLPrepend(NormalLL *l, ListObj value);
void normalLLAppend(NormalLL *l, ListObj value);
void normalLLInsertBefore(NormalLL *l, ListObj value);
void normalLLInsertAfter(NormalLL *l, ListObj value);
ListObj normalLLDeleteFront(NormalLL *l);
ListObj normalLLDeleteBack(NormalLL *l);
ListObj normalLLDelete(NormalLL *l);

#endif
