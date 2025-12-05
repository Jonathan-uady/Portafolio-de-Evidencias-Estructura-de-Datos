#include "lector_archivos.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Verificamos que se hayan pasado los argumentos de la línea de comandos
    if (argc != 2) {
        printf("Uso: %s <archivo_de_entrada>\n", argv[0]);
        return 1;
    }

    const char* archivoEntrada = argv[1];
    const char* archivoSalida = "exp_postfijas.txt";

    procesarArchivo(archivoEntrada, archivoSalida);

    printf("Conversion y evaluacion completada. Resultados guardados en %s\n", archivoSalida);

    return 0;
}
