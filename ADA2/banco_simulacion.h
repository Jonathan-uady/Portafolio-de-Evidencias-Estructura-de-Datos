#ifndef BANCO_SIMULACION_H
#define BANCO_SIMULACION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Cliente {
    int id;
    int tiempo_servicio;
    int tiempo_llegada;
    int num_cola;
} Cliente;

typedef struct Nodo {
    Cliente cliente;
    struct Nodo *siguiente;
} Nodo;

typedef struct Cola {
    Nodo *frente;
    Nodo *final;
    int tamano;
} Cola;

#define NUM_CAJAS 3

typedef struct Estadisticas {
    int clientes_atendidos[NUM_CAJAS];
    int suma_tiempos_espera[NUM_CAJAS];
} Estadisticas;

void inicializar_cola(Cola *c);
bool esta_vacia(Cola *c);
void encolar(Cola *c, Cliente nuevo_cliente);
bool desencolar(Cola *c, Cliente *cliente_atendido);

Cliente generar_cliente(int id_cliente, int tiempo_actual);
void imprimir_estadisticas(Estadisticas stats);

#endif