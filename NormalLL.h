#ifndef NORMAL_LL_H

#define NORMAL_LL_H

#include <stdbool.h>

typedef struct NormalLL NormalLL;
typedef void *ListObj;

NormalLL *normalLLCreate(void);
void normalLLDelete(NormalLL **l);

int normalLLLength(NormalLL *l);
int normalLLIndex(NormalLL *l);
ListObj normalLLFront(NormalLL *l);
ListObj normalLLBack(NormalLL *l);
ListObj normalLLGet(NormalLL *l);

void normalLLClear(NormalLL *l, bool free);
void normalLLSet(NormalLL *l, ListObj value);
void normalLLMoveFront(NormalLL *l);
void normalLLMoveBack(NormalLL *l);
void normalLLMovePrev(NormalLL *l);
void normalLLMoveNext(NormalLL *l);
void normalLLPrepend(NormalLL *l, ListObj value);
void normalLLAppend(NormalLL *l, ListObj value);
void normalLLInsertBefore(NormalLL *l, ListObj value);
void normalLLInsertAfter(NormalLL *l, ListObj value);
void normalLLDeleteFront(NormalLL *l, ListObj value);
void normalLLDelete(NormalLL *l);

#endif
