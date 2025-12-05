#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char* key) {
    unsigned int sum = 0;
    if (key == NULL) return 0;
    while (*key) {
        sum = sum * 31 + (unsigned char)*key;
        key++;
    }
    return sum % TABLE_SIZE;
}

void initTable(HashTable* ht) {
    if (ht == NULL) return;
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;
}

void insertSymbol(HashTable* ht, Symbol s) {
    if (ht == NULL) return;
    unsigned int index = hash(s.name);

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        /* allocation failed - nothing we can do here */
        return;
    }
    newNode->data = s;
    newNode->next = ht->table[index];

    ht->table[index] = newNode;
}

Symbol* searchSymbol(HashTable* ht, const char* key) {
    if (ht == NULL || key == NULL) return NULL;
    unsigned int index = hash((char*)key);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->data.name, key) == 0)
            return &current->data;
        current = current->next;
    }

    return NULL;
}

int removeSymbol(HashTable* ht, const char* key) {
    if (ht == NULL || key == NULL) return 0;
    unsigned int index = hash((char*)key);
    Node* current = ht->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, key) == 0) {

            if (prev == NULL)
                ht->table[index] = current->next;
            else
                prev->next = current->next;

            free(current);
            return 1; // eliminado
        }

        prev = current;
        current = current->next;
    }

    return 0; // no encontrado
}
