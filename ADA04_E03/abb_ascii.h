#ifndef ABB_ASCII_H
#define ABB_ASCII_H
#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

static void imprimirArbolAscii(NodoABB *raiz, int espacio){
    if (raiz == NULL) {
        return;
    }

    espacio += 6; 

    imprimirArbolAscii(raiz->der, espacio);

    printf("\n");

    for (int i = 6; i < espacio; i++) {
        printf(" ");
    }

    printf("%d | %s %s | Prom: %.2f\n",
           raiz->info.matricula,
           raiz->info.nombre,
           raiz->info.apellido,
           calcularPromedio(&(raiz->info)));

    imprimirArbolAscii(raiz->izq, espacio);
}
static inline void mostrarArbolAscii(NodoABB *raiz){
    if (raiz == NULL) {
        printf("=========================================\n");
        printf("🌳 Árbol vacío\n");
        printf("=========================================\n");
        return;
    }

    printf("\n=========================================\n");
    printf("📊 Representación ASCII del Árbol Binario\n");
    printf("=========================================\n");

    imprimirArbolAscii(raiz, 0); 
    
    printf("=========================================\n\n");
}
#endif 