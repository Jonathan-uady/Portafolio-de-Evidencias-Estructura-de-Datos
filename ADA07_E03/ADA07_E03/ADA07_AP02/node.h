#ifndef NODE_H
#define NODE_H

#include "symbol.h"

typedef struct Node {
    Symbol data;
    struct Node* next;
} Node;

#endif
