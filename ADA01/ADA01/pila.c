#include "pila.h"
#include <stdio.h>

void inicializarPila(Pila *p) {
    p->top = -1;
}

int estaVacia(Pila *p) {
    return p->top == -1;
}

void push(Pila *p, int valor) { // ¡Importante! El valor que se empuja ahora es un entero
    if (p->top >= MAX_SIZE - 1) {
        printf("Error: Pila llena\n");
        return;
    }
    p->items[++(p->top)] = valor;
}

int pop(Pila *p) {
    if (estaVacia(p)) {
        printf("Error: Pila vacia\n");
        return -1;
    }
    return p->items[(p->top)--];
}

int peek(Pila *p) {
    if (estaVacia(p)) {
        printf("Error: Pila vacia\n");
        return -1;
    }
    return p->items[p->top];
}