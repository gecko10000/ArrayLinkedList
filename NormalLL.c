#include "NormalLL.h"

#include <string.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    ListObj value;
    Node *prev;
    Node *next;
};

struct NormalLL {
    int length;
    int index;
    Node *first;
    Node *last;
    Node *current;
};

NormalLL *normalLLCreate() {
    NormalLL *l = calloc(1, sizeof(*l));
    l->index = -1;
    return l;
}

void freeNormalLL(NormalLL **l) {
    free(*l);
    *l = NULL;
}

int normalLLLength(NormalLL *l) {
    return l->length;
}

int normalLLIndex(NormalLL *l) {
    return l->index;
}

ListObj normalLLFront(NormalLL *l) {
    return l->first->value;
}

ListObj normalLLBack(NormalLL *l) {
    return l->last->value;
}

ListObj normalLLGet(NormalLL *l) {
    return l->current == NULL ? NULL : l->current->value;
}

Node *createNormalNode(ListObj val) {
    Node *n = calloc(1, sizeof(*n));
    n->value = val;
    return n;
}

void freeNormalNode(Node **n) {
    free(*n);
    *n = NULL;
}

void normalLLClear(NormalLL *l, bool freeValues) {
    Node *n = l->first, *prev;
    while (n != NULL) {
        ListObj o = n->value;
        if (freeValues) {
            free(o);
        }
        prev = n;
        n = n->next;
        freeNormalNode(&prev);
    }
    memset(l, 0, sizeof(*l));
    l->index = -1;
}

void normalLLSet(NormalLL *l, ListObj value) {
    if (l->current == NULL) {
        return;
    }
    l->current->value = value;
}

void normalLLMoveFront(NormalLL *l) {
    l->current = l->first;
    l->index = 0;
}

void normalLLMoveBack(NormalLL *l) {
    l->current = l->last;
    l->index = l->length - 1;
}

void normalLLMovePrev(NormalLL *l) {
    if (l->index <= 0) {
        l->index = -1;
        l->current = NULL;
        return;
    }
    l->index--;
    l->current = l->current->prev;
}

void normalLLMoveNext(NormalLL *l) {
    if (l->index == -1)
        return;
    if (l->index == l->length - 1) {
        l->index = -1;
        l->current = NULL;
        return;
    }
    l->index++;
    l->current = l->current->next;
}

void normalLLPrepend(NormalLL *l, ListObj value) {
    Node *n = createNormalNode(value);
    Node *first = l->first;
    l->first = n;
    l->index += l->index == -1 ? 0 : 1;
    if (l->length++ == 0) {
        l->last = n;
        return;
    }
    first->prev = n;
    n->next = first;
}

void normalLLAppend(NormalLL *l, ListObj value) {
    Node *n = createNormalNode(value);
    Node *last = l->last;
    l->last = n;
    if (l->length++ == 0) {
        l->first = n;
        return;
    }
    last->next = n;
    n->prev = last;
}

void normalLLInsertBefore(NormalLL *l, ListObj value) {
    if (l->index < 0)
        return;
    Node *n = createNormalNode(value);
    Node *cur = l->current;
    Node *prev = cur->prev;
    cur->prev = n;
    n->next = cur;
    if (prev != NULL) {
        prev->next = n;
        n->prev = prev;
    } else {
        l->first = n;
    }
    l->index++;
    l->length++;
}

void normalLLInsertAfter(NormalLL *l, ListObj value) {
    if (l->index < 0)
        return;
    Node *n = createNormalNode(value);
    Node *cur = l->current;
    Node *next = cur->next;
    cur->next = n;
    n->prev = cur;
    if (next != NULL) {
        next->prev = n;
        n->next = next;
    } else {
        l->last = n;
    }
    l->length++;
}

ListObj normalLLDeleteFront(NormalLL *l) {
    if (l->length == 0) {
        return NULL;
    }
    ListObj o = l->first->value;
    if (l->length == 1) {
        normalLLClear(l, false);
        return o;
    }
    Node *first = l->first;
    l->first = first->next;
    l->first->prev = NULL;
    freeNormalNode(&first);
    l->length--;
    if (l->index == -1)
        return o;
    if (l->index-- == 0) {
        l->current = NULL;
    }
    return o;
}

ListObj normalLLDeleteBack(NormalLL *l) {
    if (l->length == 0) {
        return NULL;
    }
    ListObj o = l->last->value;
    if (l->length == 1) {
        normalLLClear(l, false);
        return o;
    }
    Node *last = l->last;
    l->last = last->prev;
    l->last->next = NULL;
    freeNormalNode(&last);
    if (l->index == l->length - 1) {
        l->index = -1;
        l->current = NULL;
    }
    l->length--;
    return o;
}

ListObj normalLLDelete(NormalLL *l) {
    if (l->index < 0)
        return NULL;
    if (l->index == 0)
        return normalLLDeleteFront(l);
    if (l->index == l->length - 1)
        return normalLLDeleteBack(l);
    Node *curr = l->current;
    ListObj value = curr->value;
    Node *prev = curr->prev, *next = curr->next;
    prev->next = next;
    next->prev = prev;
    freeNormalNode(&curr);
    l->index = -1;
    l->current = NULL;
    l->length--;
    return value;
}
