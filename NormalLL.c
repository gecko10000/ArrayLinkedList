#include "NormalLL.h"

typedef struct Node Node;
struct Node {
    ListObj value;
    Node *prev;
    Node *next;
}

struct NormalLL {
    int size;
    int index;
    Node *first;
    Node *last;
    Node *current;
}

NormalLL *
    normalLLCreate() {
    NormalLL *l = calloc(sizeof(*l));
    l->index = -1;
    return l;
}

void normalLLDelete(NormalLL **l) {
    free(*l);
    *l = NULL;
}
