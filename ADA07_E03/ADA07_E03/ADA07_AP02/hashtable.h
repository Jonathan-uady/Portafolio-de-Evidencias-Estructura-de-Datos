#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "node.h"

#define TABLE_SIZE 50

typedef struct {
    Node* table[TABLE_SIZE]; 
} HashTable;

void initTable(HashTable* ht);
unsigned int hash(const char* key);
void insertSymbol(HashTable* ht, Symbol s);
Symbol* searchSymbol(HashTable* ht, const char* key);
int removeSymbol(HashTable* ht, const char* key);

#endif
