#ifndef PILA_H
#define PILA_H

// Definimos el tamanio maximo de la pila.
#define MAX_SIZE 100

// La estructura de la pila.
typedef struct {
    int items[MAX_SIZE]; // ¡Importante! Cambiamos 'char' a 'int'
    int top; 
} Pila;

// Prototipos de las funciones de la pila.
void inicializarPila(Pila *p);
int estaVacia(Pila *p);
void push(Pila *p, int valor); // ¡Importante! El valor que se empuja ahora es un entero
int pop(Pila *p);
int peek(Pila *p);

#endif // PILA_H