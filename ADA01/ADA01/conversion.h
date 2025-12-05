#ifndef CONVERSION_H
#define CONVERSION_H

#include "pila.h"

int esOperador(char c);
int prioridad(char c);
void infijoAPostfijo(char* infijo, char* postfijo);

#endif // CONVERSION_H


