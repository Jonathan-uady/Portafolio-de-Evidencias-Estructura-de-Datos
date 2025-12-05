#include "evaluacion.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // ¡Importante! Añadimos math.h para usar pow()

int evaluarPostfijo(char* postfijo) {
    Pila pilaOperandos;
    inicializarPila(&pilaOperandos);

    char temp[256];
    strcpy(temp, postfijo);

    char* token = strtok(temp, " ");
    while (token != NULL) {
        // isdigit() es una funcion para checar si un caracter es un numero
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            int numero = atoi(token); // Convierte el string a entero
            push(&pilaOperandos, numero);
        } else {
            int operando2 = pop(&pilaOperandos);
            int operando1 = pop(&pilaOperandos);
            
            if (operando1 == -1 || operando2 == -1) {
                printf("Error: Expresion postfija invalida.\n");
                return 0;
            }

            switch (token[0]) {
                case '+':
                    push(&pilaOperandos, operando1 + operando2);
                    break;
                case '-':
                    push(&pilaOperandos, operando1 - operando2);
                    break;
                case '*':
                    push(&pilaOperandos, operando1 * operando2);
                    break;
                case '/':
                    if (operando2 == 0) {
                        printf("Error: Division por cero.\n");
                        return 0;
                    }
                    push(&pilaOperandos, operando1 / operando2);
                    break;
                case '^':
                    // Agregamos la logica para el operador de potencia
                    // La funcion pow() devuelve un double, por lo que convertimos el resultado a int.
                    push(&pilaOperandos, (int)pow(operando1, operando2));
                    break;
            }
        }
        token = strtok(NULL, " ");
    }
    
    int resultado = pop(&pilaOperandos);
    if (!estaVacia(&pilaOperandos)) {
        printf("Error: Expresion postfija invalida, la pila no esta vacia al final.\n");
        return 0;
    }
    return resultado;
}
