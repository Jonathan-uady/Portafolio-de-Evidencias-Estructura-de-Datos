#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define TAMANO_TABLA 101

typedef enum {
    VACIO,OCUPADO,ELIMINADO
} Estado;

typedef struct {
    int matricula;
    char nombre[50];
    char carrera[30];
} Estudiante;

typedef struct {
    Estudiante estudiante;
    Estado estado;
} SlotTabla;

// --- Implementación de Funciones ---
void inicializarTabla(SlotTabla tabla[]) {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        tabla[i].estado = VACIO;
    }
}

int funcionHash(int matricula) {
    return matricula % TAMANO_TABLA;
}

bool agregarEstudiante(SlotTabla tabla[], Estudiante est) {
    int indice = funcionHash(est.matricula);
    int i = 0; 

    while (tabla[indice].estado == OCUPADO) {
        // Verificar si la matrícula ya existe
        if (tabla[indice].estudiante.matricula == est.matricula) {
            printf("Error: La matricula %d ya existe.\n", est.matricula);
            return false;
        }

        indice = (indice + 1) % TAMANO_TABLA;
        i++;

        // La tabla está llena
        if (i >= TAMANO_TABLA) {
            printf("Error: Tabla llena (Overflow).\n");
            return false;
        }
    }

    tabla[indice].estudiante = est;
    tabla[indice].estado = OCUPADO;
    return true;
}

bool buscarEstudiante(SlotTabla tabla[], int matricula, Estudiante *resultado) {
    int indice = funcionHash(matricula);
    int i = 0;

    while (tabla[indice].estado != VACIO && i < TAMANO_TABLA) {
        
        if (tabla[indice].estado == OCUPADO && tabla[indice].estudiante.matricula == matricula) {
            *resultado = tabla[indice].estudiante; // Copiamos los datos
            return true;
        }
        
        indice = (indice + 1) % TAMANO_TABLA;
        i++;
    }
    
    return false;
}

bool eliminarEstudiante(SlotTabla tabla[], int matricula) {
    int indice = funcionHash(matricula);
    int i = 0;

    while (tabla[indice].estado != VACIO && i < TAMANO_TABLA) {
        
        if (tabla[indice].estado == OCUPADO && tabla[indice].estudiante.matricula == matricula) {
            tabla[indice].estado = ELIMINADO; 
            return true;
        }
        
        indice = (indice + 1) % TAMANO_TABLA;
        i++;
    }
    
    return false;
}

void imprimirTabla(SlotTabla tabla[]) {
    int contador = 0;
    printf("\n--- LISTA DE ESTUDIANTES REGISTRADOS ---\n");
    printf("| %-10s | %-50s | %-20s |\n", "Matricula", "Nombre", "Carrera");
    printf("|------------|----------------------------------------------------|----------------------|\n");
    
    for (int i = 0; i < TAMANO_TABLA; i++) {
        if (tabla[i].estado == OCUPADO) {
            Estudiante est = tabla[i].estudiante;
            // Opcional: imprimir el índice donde realmente está
            printf("| %-10d | %-50s | %-20s | (Indice: %d)\n", 
                   est.matricula, est.nombre, est.carrera, i);
            contador++;
        }
    }
    
    if (contador == 0) {
        printf("| %-93s |\n", "No hay estudiantes registrados.");
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("Total de estudiantes activos: %d\n", contador);
}

#endif