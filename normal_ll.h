#ifndef NORMAL_LL_H

#define NORMAL_LL_H

#include <stdbool.h>

typedef struct NormalLL NormalLL;
typedef void *ListObj;

NormalLL *normal_ll_create(void);
void normal_ll_delete(NormalLL **l);

int length(NormalLL *l);
int index(NormalLL *l);
ListObj front(NormalLL *l);
ListObj back(NormalLL *l);
ListObj get(NormalLL *l);

void clear(NormalLL *l, bool free);
void set(NormalLL *l, ListObj value);
void moveFront(NormalLL *l);
void moveBack(NormalLL *l);
void movePrev(NormalLL *l);
void moveNext(NormalLL *l);
void prepend(NormalLL *l, ListObj value);
void append(NormalLL *l, ListObj value);
void insertBefore(NormalLL *l, ListObj value);
void insertAfter(NormalLL *l, ListObj value);
void deleteFront(NormalLL *l, ListObj value);
void delete (NormalLL *l);

#endif
