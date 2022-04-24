#include "ArrayLL.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Node Node;
struct Node {
    ArrListObj value;
    int prev;
    int next;
};

struct ArrayLL {
    int maxSize;
    int length;
    int index;
    int first;
    int last;
    int current;
    Node **arr;
};

ArrayLL *arrayLLCreate(int size) {
    ArrayLL *l = malloc(sizeof(*l));
    l->maxSize = size;
    l->length = 0;
    l->index = -1;
    l->first = -1;
    l->last = -1;
    l->current = -1;
    l->arr = calloc(size, sizeof(*l->arr));
    return l;
}

void freeArrNode(Node **n);

void freeArrayLL(ArrayLL **l) {
    for (int i = 0; i < (*l)->maxSize; i++) {
        Node *n = (*l)->arr[i];
        if (n == NULL)
            continue;
        freeArrNode(&n);
    }
    free((*l)->arr);
    free(*l);
    *l = NULL;
}

int arrayLLLength(ArrayLL *l) {
    return l->length;
}

int arrayLLIndex(ArrayLL *l) {
    return l->index;
}

ArrListObj arrayLLFront(ArrayLL *l) {
    return l->first == -1 ? NULL : l->arr[l->first]->value;
}

ArrListObj arrayLLBack(ArrayLL *l) {
    return l->last == -1 ? NULL : l->arr[l->last]->value;
}

ArrListObj arrayLLGet(ArrayLL *l) {
    return l->index == -1 ? NULL : l->arr[l->current]->value;
}

Node *createArrNode(ArrListObj val) {
    Node *n = calloc(1, sizeof(*n));
    n->value = val;
    return n;
}

void freeArrNode(Node **n) {
    free(*n);
    *n = NULL;
}

void arrayLLClear(ArrayLL *l, bool freeValues) {
    int i = l->first;
    Node *n = l->arr[i];
    int nextOffset;
    do {
        ArrListObj o = n->value;
        if (freeValues)
            free(o);
        nextOffset = n->next;
        freeArrNode(&n);
        l->arr[i] = NULL;
        i += nextOffset;
        n = l->arr[i];
    } while (nextOffset != 0);
    l->length = 0;
    l->index = -1;
    l->first = -1;
    l->last = -1;
    l->current = -1;
}

void arrayLLSet(ArrayLL *l, ArrListObj value) {
    if (l->index == -1)
        return;
    l->arr[l->current]->value = value;
}

void arrayLLMoveFront(ArrayLL *l) {
    l->current = l->first;
    l->index = 0;
}

void arrayLLMoveBack(ArrayLL *l) {
    l->current = l->last;
    l->index = l->length - 1;
}

void arrayLLMovePrev(ArrayLL *l) {
    if (l->index == -1)
        return;
    if (l->index == 0) {
        l->index = -1;
        l->current = -1;
        return;
    }
    l->index--;
    l->current += l->arr[l->current]->prev;
}

void arrayLLMoveNext(ArrayLL *l) {
    if (l->index == -1)
        return;
    if (l->index == l->length - 1) {
        l->index = -1;
        l->current = -1;
        return;
    }
    l->index++;
    l->current += l->arr[l->current]->next;
}

void arrayLLPrepend(ArrayLL *l, ArrListObj value) {
    Node *n = createArrNode(value);
    int original = l->first, i = l->first;
    // if the array already has 1+ values
    if (original != -1) {
        while (l->arr[i] != NULL) {
            i = (i + l->maxSize - 1) % l->maxSize; // circular backwards
            if (original == i) {
                fprintf(stderr, "Array is full.");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        // there is no first element
        i = 0;
        l->last = 0;
    }
    // i is now the index to put the new node into
    l->arr[i] = n;
    // ex. inserting new node into index 0, original is 1
    // prev becomes -1, next is 1
    // these are offsets
    if (original != -1) {
        l->arr[original]->prev = i - original;
        n->next = original - i;
    }
    l->first = i;
    l->index += l->index == -1 ? 0 : 1;
    l->length++;
}

void arrayLLAppend(ArrayLL *l, ArrListObj value) {
    Node *n = createArrNode(value);
    int original = l->last, i = l->last;
    if (original != -1) {
        while (l->arr[i] != NULL) {
            i = (i + 1) % l->maxSize; // circ forwards
            if (original == i) {
                fprintf(stderr, "Array is full.");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        i = 0;
        l->first = 0;
    }
    l->arr[i] = n;
    if (original != -1) {
        l->arr[original]->next = i - original;
        n->prev = original - i;
    }
    l->last = i;
    l->length++;
}

void arrayLLInsertBefore(ArrayLL *l, ArrListObj value) {
    if (l->current == -1)
        return;
    if (l->current == l->first) {
        arrayLLPrepend(l, value);
        return;
    }
    Node *n = createArrNode(value);
    int original = l->current, i = l->current;
    while (l->arr[i] != NULL) {
        i = (i - 1 + l->maxSize) % l->maxSize;
        if (original == i) {
            fprintf(stderr, "Array is full.");
            exit(EXIT_FAILURE);
        }
    }
    l->arr[i] = n;
    Node *curr = l->arr[l->current];
    int prevIndex = curr->prev;
    Node *prev = l->arr[l->current + prevIndex];
    prev->next = i - prevIndex;
    n->prev = prevIndex - i;
    curr->prev = i - original;
    n->next = original - i;
    l->length++;
    l->index++;
}

void arrayLLInsertAfter(ArrayLL *l, ArrListObj value) {
    if (l->current == -1)
        return;
    if (l->current == l->last) {
        arrayLLAppend(l, value);
        return;
    }
    Node *n = createArrNode(value);
    int original = l->current, i = l->current;
    while (l->arr[i] != NULL) {
        i = (i + 1) % l->maxSize;
        if (original == i) {
            fprintf(stderr, "Array is full.");
            exit(EXIT_FAILURE);
        }
    }
    l->arr[i] = n;
    Node *curr = l->arr[l->current];
    int nextIndex = curr->next;
    Node *next = l->arr[l->current + nextIndex];
    next->prev = i - nextIndex;
    n->next = nextIndex - i;
    curr->next = i - original;
    n->prev = original - i;
    l->length++;
}

ArrListObj arrayLLDeleteFront(ArrayLL *l) {
    int front = l->first;
    Node *n = l->arr[front];
    ArrListObj value = n->value;
    if (l->length == 1) {
        arrayLLClear(l, false);
    } else {
        l->arr[front] = NULL;
        int next = n->next;
        l->first += next;
        l->arr[front + next]->prev = 0;
        freeArrNode(&n);
        l->length--;
        l->index -= l->index == -1 ? 0 : 1;
    }
    return value;
}

ArrListObj arrayLLDeleteBack(ArrayLL *l) {
    return NULL;
}

ArrListObj arrayLLDelete(ArrayLL *l) {
    return NULL;
}
