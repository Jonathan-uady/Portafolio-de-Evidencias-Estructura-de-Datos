#ifndef SYMBOL_H
#define SYMBOL_H

#define MAX_STR 50

typedef struct {
    char name[MAX_STR];
    char type[MAX_STR];
    char scope[MAX_STR];
    char value[MAX_STR];
} Symbol;

#endif
