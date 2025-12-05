#include "conversion.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int esDigito(char c) {
    return c >= '0' && c <= '9';
}

int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int prioridad(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

int infijoAPostfijo(char* infijo, char* postfijo) {
    Pila pilaOperadores;
    inicializarPila(&pilaOperadores);

    int i, j;
    i = 0;
    j = 0;

    while (infijo[i] != '\0' && infijo[i] != ';') {
        char caracter = infijo[i];

        if (caracter == ' ') {
            i++;
            continue;
        } else if (esDigito(caracter)) {
            while (esDigito(infijo[i])) {
                postfijo[j++] = infijo[i++];
            }
            postfijo[j++] = ' ';
            i--;
        } else if (caracter == '(') {
            push(&pilaOperadores, caracter);
        } else if (caracter == ')') {
            while (!estaVacia(&pilaOperadores) && peek(&pilaOperadores) != '(') {
                postfijo[j++] = pop(&pilaOperadores);
                postfijo[j++] = ' ';
            }
            if (!estaVacia(&pilaOperadores) && peek(&pilaOperadores) == '(') {
                pop(&pilaOperadores);
            } else {
                return 0;
            }
        } else if (esOperador(caracter)) {
            while (!estaVacia(&pilaOperadores) && prioridad(peek(&pilaOperadores)) >= prioridad(caracter)) {
                postfijo[j++] = pop(&pilaOperadores);
                postfijo[j++] = ' ';
            }
            push(&pilaOperadores, caracter);
        } else {
            return 0;
        }
        i++;
    }

    while (!estaVacia(&pilaOperadores)) {
        if (peek(&pilaOperadores) == '(') {
            return 0;
        }
        postfijo[j++] = pop(&pilaOperadores);
        postfijo[j++] = ' ';
    }
    
    if (j > 0 && postfijo[j - 1] == ' ') {
        j--;
    }
    postfijo[j] = '\0';
    return 1;
}
