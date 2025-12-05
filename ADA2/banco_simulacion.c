#include "banco_simulacion.h"

void inicializar_cola(Cola *c) {
    c->frente = NULL;
    c->final = NULL;
    c->tamano = 0;
}

bool esta_vacia(Cola *c) {
    return c->frente == NULL;
}

void encolar(Cola *c, Cliente nuevo_cliente) {
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        perror("Error de asignación de memoria para el nodo");
        return;
    }
    
    nuevo_nodo->cliente = nuevo_cliente;
    nuevo_nodo->siguiente = NULL;

    if (esta_vacia(c)) {
        c->frente = nuevo_nodo;
        c->final = nuevo_nodo;
    } else {
        c->final->siguiente = nuevo_nodo;
        c->final = nuevo_nodo;
    }
    c->tamano++;
}

bool desencolar(Cola *c, Cliente *cliente_atendido) {
    if (esta_vacia(c)) {
        return false;
    }

    Nodo *nodo_a_eliminar = c->frente;

    *cliente_atendido = nodo_a_eliminar->cliente;

    c->frente = c->frente->siguiente;

    if (c->frente == NULL) {
        c->final = NULL;
    }

    free(nodo_a_eliminar);
    c->tamano--;
    return true;
}

Cliente generar_cliente(int id_cliente, int tiempo_actual) {
    Cliente nuevo;
    nuevo.id = id_cliente;
    nuevo.tiempo_servicio = (rand() % 10) + 1; 
    nuevo.tiempo_llegada = tiempo_actual;
    nuevo.num_cola = rand() % NUM_CAJAS; 
    
    return nuevo;
}

void imprimir_estadisticas(Estadisticas stats) {
    printf("\n============================================\n");
    printf("        ESTADÍSTICAS FINALES DEL BANCO        \n");
    printf("============================================\n");
    
    for (int i = 0; i < NUM_CAJAS; i++) {
        int clientes = stats.clientes_atendidos[i];
        int tiempo_total = stats.suma_tiempos_espera[i];
        
        printf("\n--- Caja/Cola %d ---\n", i + 1);
        printf("Clientes atendidos: %d\n", clientes);
        
        if (clientes > 0) {
            float promedio = (float)tiempo_total / clientes;
            printf("Tiempo promedio de espera: %.2f unidades de tiempo\n", promedio);
        } else {
            printf("Tiempo promedio de espera: N/A (0 clientes atendidos)\n");
        }
    }
    printf("\n============================================\n");
}


int main() {
    srand(time(NULL));

    Cola colas[NUM_CAJAS];
    for (int i = 0; i < NUM_CAJAS; i++) {
        inicializar_cola(&colas[i]);
    }
    
    Cliente *caja_cliente[NUM_CAJAS] = {NULL, NULL, NULL}; 
    int tiempo_restante_caja[NUM_CAJAS] = {0, 0, 0}; 

    Estadisticas stats = {{0}, {0}};

    int tiempo_actual = 0;
    int max_tiempo_simulacion = 100;
    int id_siguiente_cliente = 1;

    printf("--- INICIO DE LA SIMULACIÓN BANCARIA (Tiempo Total: %d) ---\n", max_tiempo_simulacion);

    while (tiempo_actual < max_tiempo_simulacion) {
        tiempo_actual++;
        printf("\n[TIEMPO %d] ", tiempo_actual);

        if (rand() % 10 < 3) { 
            Cliente nuevo_cliente = generar_cliente(id_siguiente_cliente++, tiempo_actual);
            int cola_idx = nuevo_cliente.num_cola;
            
            encolar(&colas[cola_idx], nuevo_cliente);
            
            printf("-> LLEGADA: Cliente %d (Servicio: %d) ingresa a COLA %d. Tamaño cola: %d.\n", 
                   nuevo_cliente.id, nuevo_cliente.tiempo_servicio, cola_idx + 1, colas[cola_idx].tamano);
        } else {
             printf("-> No hay llegadas.\n");
        }

        for (int i = 0; i < NUM_CAJAS; i++) {
            
            if (caja_cliente[i] != NULL) {
                tiempo_restante_caja[i]--;
                
                if (tiempo_restante_caja[i] == 0) {
                    int t_llegada = caja_cliente[i]->tiempo_llegada;
                    int t_servicio = caja_cliente[i]->tiempo_servicio;
                    int t_salida = tiempo_actual;
                    
                    int tiempo_espera = t_salida - t_llegada - t_servicio;
                    stats.suma_tiempos_espera[i] += tiempo_espera;
                    stats.clientes_atendidos[i]++;
                    
                    printf("  -> CAJA %d: Cliente %d SALIÓ (Espera: %d). CAJA LIBRE.\n", 
                           i + 1, caja_cliente[i]->id, tiempo_espera);
                    
                    free(caja_cliente[i]);
                    caja_cliente[i] = NULL; 
                } else {
                    printf("  -> CAJA %d: Atendiendo a Cliente %d. Le quedan %d unid. de tiempo.\n", 
                           i + 1, caja_cliente[i]->id, tiempo_restante_caja[i]);
                }
            }
            
            if (caja_cliente[i] == NULL && !esta_vacia(&colas[i])) {
                Cliente cliente_nuevo_en_caja;
                
                if (desencolar(&colas[i], &cliente_nuevo_en_caja)) {
                    caja_cliente[i] = (Cliente*)malloc(sizeof(Cliente));
                    if (caja_cliente[i] == NULL) {
                        perror("Error al asignar memoria para cliente en caja");
                        break;
                    }
                    *caja_cliente[i] = cliente_nuevo_en_caja;
                    tiempo_restante_caja[i] = cliente_nuevo_en_caja.tiempo_servicio;
                    
                    printf("  -> CAJA %d: Cliente %d INICIA atención. Servicio: %d. Cola restante: %d.\n", 
                           i + 1, cliente_nuevo_en_caja.id, tiempo_restante_caja[i], colas[i].tamano);
                }
            } else if (caja_cliente[i] == NULL) {
                 printf("  -> CAJA %d: Libre (Cola %d vacía).\n", i + 1, i + 1);
            }
        }
    }

    printf("\n--- SIMULACIÓN FINALIZADA ---\n");
    
    for (int i = 0; i < NUM_CAJAS; i++) {
        if (caja_cliente[i] != NULL) {
            free(caja_cliente[i]);
        }
    }
    
    imprimir_estadisticas(stats);

    return 0;
}