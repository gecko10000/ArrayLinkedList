#include "ArrayLL.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Node Node;
struct Node {
    ListObj value;
    int prev;
    int next;
}

struct ArrayLL {
    int length;
    int index;
    int first;
    int last;
    int current;
    Node **arr;
}

ArrayLL *
    arrayLLCreate(int size) {
    ArrayLL *l = malloc(sizeof(*l));
    l->length = 0;
    l->index = -1;
    l->first = -1;
    l->last = -1;
    l->current = -1;
    l->arr = malloc(size * sizeof(*l->arr));
    return l;
}

void freeArrayLL(ArrayLL **l) {
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

ListObj arrayLLFront(ArrayLL *l) {
    return l->first == -1 ? NULL : l->arr[l->first]->value;
}

ListObj arrayLLBack(ArrayLL *l) {
    return l->last == -1 ? NULL : l->arr[l->last]->value;
}

ListObj arrayLLGet(ArrayLL *l) {
    return l->index == -1 ? NULL : l->arr[l->current]->value;
}

Node *createNode(ListObj val) {
    Node *n = calloc(1, sizeof(*n));
    n->value = val;
    return n;
}

void freeNode(Node **n) {
    free(*n);
    *n = NULL;
}

ListObj arrayLLClear(ArrayLL *l, bool freeValues) {
    int i = l->first;
    Node *n = l->arr[i];
    int nextOffset;
    do {
        ListObj o = n->value;
        if (freevalues)
            free(o);
        nextOffset = n->next;
        freeNode(&n);
        i = (i + nextOffset) % l->length;
        n = l->arr[i];
    } while (nextOffset != 0);
    l->length = 0;
    l->index = -1;
    l->first = -1;
    l->last = -1;
    l->current = -1;
}

void arrayLLSet(ArrayLL *l, ListObj value) {
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

void arrayLLMovePrev(NormalLL *l) {
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

void arrayLLMoveNext(NormalLL *l) {
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

void arrayLLPrepend(NormalLL *l, ListObj value) {
    Node *n = createNode(value);
    int original = l->first, i = l->first;
    // if the array already has 1+ values
    if (original != -1) {
        while (l->arr[i] != NULL) {
            i = (i + l->length - 1) % l->length; // circular backwards
            if (original == i) {
                fprintf(stderr, "Array is full.");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        // there is no first element
        i = 0;
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
}
