#include "lector_archivos.h"
#include "conversion.h"
#include "evaluacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procesarArchivo(const char* archivoEntrada, const char* archivoSalida) {
    FILE* entrada = fopen(archivoEntrada, "r");
    FILE* salida = fopen(archivoSalida, "w");

    if (entrada == NULL || salida == NULL) {
        perror("Error al abrir los archivos");
        exit(1);
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), entrada)) {
        char infija[256];
        char postfija[256];
        int resultado;

        // Eliminar el salto de línea al final de la linea
        linea[strcspn(linea, "\n")] = 0;

        // Si la línea no termina en ';', es un error de formato
        if (linea[strlen(linea) - 1] != ';') {
            fprintf(salida, "Error: Formato de expresion invalido, debe terminar en ';'\n");
            continue;
        }

        strcpy(infija, linea);
        infijoAPostfijo(infija, postfija);
        resultado = evaluarPostfijo(postfija);

        fprintf(salida, "Expresion: %s; Resultado: %d\n", postfija, resultado);
    }

    fclose(entrada);
    fclose(salida);
}
