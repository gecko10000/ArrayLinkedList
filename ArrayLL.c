#include "ArrayLL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Node *arr;
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

void freeArrayLL(ArrayLL **l) {
    free((*l)->arr);
    free(*l);
    *l = NULL;
}

bool isNull(ArrayLL *l, int i) {
    return l->arr[i].prev == 0 && l->arr[i].next == 0;
}

void setNull(ArrayLL *l, int index) {
    memset(l->arr + index, 0, sizeof(*l->arr));
}

int arrayLLLength(ArrayLL *l) {
    return l->length;
}

int arrayLLIndex(ArrayLL *l) {
    return l->index;
}

ArrListObj arrayLLFront(ArrayLL *l) {
    return l->first == -1 ? NULL : l->arr[l->first].value;
}

ArrListObj arrayLLBack(ArrayLL *l) {
    return l->last == -1 ? NULL : l->arr[l->last].value;
}

ArrListObj arrayLLGet(ArrayLL *l) {
    return l->index == -1 ? NULL : l->arr[l->current].value;
}

void arrayLLClear(ArrayLL *l) {
    /*int i = l->first;
    Node *n = l->arr[i];
    int nextOffset;
    do {
        ArrListObj o = l->arr[i].value;
        if (freeValues)
            free(o);
        nextOffset = l->arr[i].next;
        l->arr[i] = NULL;
        i += nextOffset;
        n = l->arr[i];
    } while (nextOffset != 0);*/
    l->length = 0;
    l->index = -1;
    l->first = -1;
    l->last = -1;
    l->current = -1;
    memset(l->arr, 0, l->maxSize * sizeof(*l->arr));
}

void arrayLLSet(ArrayLL *l, ArrListObj value) {
    if (l->index == -1)
        return;
    l->arr[l->current].value = value;
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
    l->current += l->arr[l->current].prev;
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
    l->current += l->arr[l->current].next;
}

void arrayLLPrepend(ArrayLL *l, ArrListObj value) {
    int original = l->first, i = l->first;
    // if the array already has 1+ values
    if (original != -1) {
        while (!isNull(l, i)) {
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
    Node *n = l->arr + i;
    n->value = value;
    // ex. inserting new node into index 0, original is 1
    // prev becomes -1, next is 1
    // these are offsets
    if (original != -1) {
        l->arr[original].prev = i - original;
        n->next = original - i;
    }
    l->first = i;
    l->index += l->index == -1 ? 0 : 1;
    l->length++;
}

void arrayLLAppend(ArrayLL *l, ArrListObj value) {
    int original = l->last, i = l->last;
    if (original != -1) {
        while (!isNull(l, i)) {
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
    Node *n = l->arr + i;
    n->value = value;
    if (original != -1) {
        l->arr[original].next = i - original;
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
    int original = l->current, i = l->current;
    while (!isNull(l, i)) {
        i = (i - 1 + l->maxSize) % l->maxSize;
        if (original == i) {
            fprintf(stderr, "Array is full.");
            exit(EXIT_FAILURE);
        }
    }
    Node *n = l->arr + i;
    Node *curr = l->arr + l->current;
    int prevIndex = l->current + curr->prev;
    Node *prev = l->arr + prevIndex;
    n->value = value;
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
    int original = l->current, i = l->current;
    while (!isNull(l, i)) {
        i = (i + 1) % l->maxSize;
        if (original == i) {
            fprintf(stderr, "Array is full.");
            exit(EXIT_FAILURE);
        }
    }
    Node *n = l->arr + i;
    n->value = value;
    Node *curr = l->arr + l->current;
    int nextIndex = l->current + curr->next;
    Node *next = l->arr + nextIndex;
    next->prev = i - nextIndex;
    n->next = nextIndex - i;
    curr->next = i - original;
    n->prev = original - i;
    l->length++;
}

ArrListObj arrayLLDeleteFront(ArrayLL *l) {
    int front = l->first;
    Node *n = l->arr + front;
    ArrListObj value = n->value;
    if (l->length == 1) {
        arrayLLClear(l);
    } else {
        int next = n->next;
        l->first += next;
        (n + next)->prev = 0;
        l->length--;
        l->index -= l->index == -1 ? 0 : 1;
        setNull(l, front);
    }
    return value;
}

ArrListObj arrayLLDeleteBack(ArrayLL *l) {
    int back = l->last;
    Node *n = l->arr + back;
    ArrListObj value = n->value;
    if (l->length == 1) {
        arrayLLClear(l);
    } else {
        int prev = n->prev;
        l->last += prev;
        (n + prev)->next = 0;
        l->length--;
        if (l->index == l->length) {
            l->index = -1;
            l->current = -1;
        }
        setNull(l, back);
    }
    return value;
}

ArrListObj arrayLLDelete(ArrayLL *l) {
    if (l->current == -1)
        return NULL;
    if (l->index == 0)
        return arrayLLDeleteFront(l);
    if (l->index == l->length - 1)
        return arrayLLDeleteBack(l);
    Node *n = l->arr + l->current;
    int prev = n->prev, next = n->next;
    Node *prevNode = l->arr + prev, *nextNode = l->arr +next;
    prevNode->next = next - prev;
    nextNode->prev = prev - next;
    ArrListObj value = n->value;
    setNull(l, l->current);
    l->current = -1;
    l->index = -1;
    l->length--;
    return value;
}
