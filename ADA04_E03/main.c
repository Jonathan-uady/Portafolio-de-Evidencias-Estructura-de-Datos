#include <stdio.h>
#include <stdlib.h>
#include "abb_ascii.h"
// Incluimos nuestro super archivo .h
#include "abb.h"

// --- Función para leer los datos de un nuevo estudiante ---
Estudiante leerNuevoEstudiante() {
    Estudiante e;

    printf("--- Insertar Nuevo Estudiante ---\n");
    printf("Matricula: ");
    scanf("%d", &e.matricula);
    
    // Limpiar buffer de entrada
    while(getchar() != '\n'); 

    printf("Nombre: ");
    // Usamos fgets para leer nombres con espacios, es más seguro
    fgets(e.nombre, 50, stdin);
    e.nombre[strcspn(e.nombre, "\n")] = 0; // Quitar el \n

    printf("Apellido: ");
    fgets(e.apellido, 50, stdin);
    e.apellido[strcspn(e.apellido, "\n")] = 0; // Quitar el \n

    printf("Cuantas calificaciones iniciales (0 si ninguna): ");
    scanf("%d", &e.numCalificaciones);

    if (e.numCalificaciones > 0) {
        // Pedimos memoria para sus calificaciones
        e.calificaciones = (float*)malloc(e.numCalificaciones * sizeof(float));
        if (e.calificaciones == NULL) {
            printf("Error de memoria.\n");
            exit(1);
        }
        printf("Ingresa las %d calificaciones:\n", e.numCalificaciones);
        for (int i = 0; i < e.numCalificaciones; i++) {
            printf("Calificacion %d: ", i + 1);
            scanf("%f", &e.calificaciones[i]);
        }
    } else {
        // Importante inicializar el puntero a NULL si no hay calificaciones
        e.calificaciones = NULL; 
        e.numCalificaciones = 0;
    }
    
    return e;
}

// --- Función Principal (Menú) ---
int main() {
    NodoABB* raiz = NULL;
    int opcion;
    int matricula, nivel;

    // Para que se vea más "pro", vamos a meter unos datos de prueba
    // Estudiante e1 = {100, "Juan", "Perez", (float*)malloc(3*sizeof(float)), 3};
    // e1.calificaciones[0] = 80; e1.calificaciones[1] = 90; e1.calificaciones[2] = 100; // Prom 90
    // insertar(&raiz, e1);
    
    // Estudiante e2 = {50, "Maria", "Gomez", (float*)malloc(2*sizeof(float)), 2};
    // e2.calificaciones[0] = 60; e2.calificaciones[1] = 65; // Prom 62.5
    // insertar(&raiz, e2);
    
    // Estudiante e3 = {150, "Carlos", "Lopez", (float*)malloc(4*sizeof(float)), 4};
    // e3.calificaciones[0] = 70; e3.calificaciones[1] = 70; e3.calificaciones[2] = 80; e3.calificaciones[3] = 90; // Prom 77.5
    // insertar(&raiz, e3);
    
    // Estudiante e4 = {75, "Ana", "Diaz", (float*)malloc(1*sizeof(float)), 1};
    // e4.calificaciones[0] = 69; // Prom 69
    // insertar(&raiz, e4);

    do {
        printf("\n--- Sistema de Gestion de Estudiantes (ABB) ---\n");
        printf("1. Reporte de estudiantes (por Matricula)\n");
        printf("2. Reporte de estudiantes (por Promedio)\n");
        printf("3. Reporte de estudiantes (Promedio < 70)\n");
        printf("4. Reporte de estudiantes (Promedio >= 70)\n");
        printf("5. Insertar nuevo estudiante\n");
        printf("6. Eliminar estudiante (por Matricula)\n");
        printf("7. Actualizar calificaciones de estudiante\n");
        printf("8. Contar alumnos con promedio menor (dada Matricula)\n");
        printf("9. Mostrar nodos de un Nivel\n");
        printf("10. Mostrar Arbol (Grafico ASCII)\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        
        // Es buena práctica leer la opción como caracter
        // para evitar bucles infinitos si el usuario mete una letra.
        // Pero para un trabajo de clase, scanf("%d") está bien.
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("\n--- Reporte por Matricula (In-Orden) ---\n");
                reportePorMatricula(raiz);
                if(raiz == NULL) printf("Arbol vacio.\n");
                break;
            case 2:
                printf("\n--- Reporte por Promedio ---\n");
                reportePorPromedio(raiz);
                break;
            case 3:
                printf("\n--- Reporte Promedio < 70 ---\n");
                reporteMenor70(raiz);
                if(raiz == NULL) printf("Arbol vacio.\n");
                break;
            case 4:
                printf("\n--- Reporte Promedio >= 70 ---\n");
                reporteMayorIgual70(raiz);
                if(raiz == NULL) printf("Arbol vacio.\n");
                break;
            case 5:
                { // Usamos llaves para poder declarar 'e' dentro del case
                    Estudiante e = leerNuevoEstudiante();
                    insertar(&raiz, e);
                }
                break;
            case 6:
                printf("Ingresa la matricula a eliminar: ");
                scanf("%d", &matricula);
                // La función 'eliminar' devuelve la nueva raíz
                raiz = eliminar(raiz, matricula);
                break;
            case 7:
                printf("Ingresa la matricula a actualizar: ");
                scanf("%d", &matricula);
                actualizarCalificaciones(raiz, matricula);
                break;
            case 8:
                printf("Ingresa la matricula de referencia: ");
                scanf("%d", &matricula);
                contarMenoresPromedio(raiz, matricula);
                break;
            case 9:
                printf("Ingresa el nivel a mostrar (0 es la raiz): ");
                scanf("%d", &nivel);
                mostrarNivel(raiz, nivel);
                break;
            case 10:
                printf("\n--- Arbol Grafico (visto de lado) ---\n");
                mostrarArbolGrafico(raiz, 0);
                if(raiz == NULL) printf("Arbol vacio.\n");
                break;
            case 0:
                printf("Liberando memoria y saliendo...\n");
                liberarMemoria(raiz); // ¡Muy importante!
                break;
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");
                // Limpiar el buffer por si metieron letras
                while(getchar() != '\n'); 
                break;
        }

    } while (opcion != 0);

    return 0;
}