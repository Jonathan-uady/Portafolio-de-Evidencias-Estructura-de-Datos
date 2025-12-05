/* main.c */
#include "estudiante.h"
#include <stdlib.h>

int main() {
    SlotTabla tabla[TAMANO_TABLA];
    int opcion, mat;
    Estudiante tempEst;
    
    inicializarTabla(tabla);
    
    do {
        printf("\n--- SISTEMA DE ESTUDIANTES (HASHING LINEAL) ---\n");
        printf("1. Agregar Estudiante\n");
        printf("2. Buscar Estudiante\n");
        printf("3. Eliminar Estudiante\n");
        printf("4. Mostrar Todos\n");
        printf("5. Salir\n");
        printf("Seleccione: ");
        
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n'); 
            opcion = 0;
            continue;
        }
        
        switch(opcion) {
            case 1:
                printf("\nIngrese Matricula (max 6 digitos): ");
                scanf("%d", &tempEst.matricula);
                // Limpiar buffer
                while(getchar() != '\n'); 
                
                printf("Ingrese Nombre: ");
                fgets(tempEst.nombre, 50, stdin);
                tempEst.nombre[strcspn(tempEst.nombre, "\n")] = 0;
                
                printf("Ingrese Carrera: ");
                fgets(tempEst.carrera, 30, stdin);
                tempEst.carrera[strcspn(tempEst.carrera, "\n")] = 0;

                if (agregarEstudiante(tabla, tempEst)) {
                    printf(">> Estudiante registrado con exito.\n");
                }
                break;
                
            case 2:
                printf("\nIngrese Matricula a buscar: ");
                scanf("%d", &mat);
                
                if (buscarEstudiante(tabla, mat, &tempEst)) {
                    printf(">> ENCONTRADO:\n   Nombre: %s\n   Carrera: %s\n", tempEst.nombre, tempEst.carrera);
                } else {
                    printf(">> Estudiante no encontrado.\n");
                }
                break;
                
            case 3:
                printf("\nIngrese Matricula a eliminar: ");
                scanf("%d", &mat);
                
                if (eliminarEstudiante(tabla, mat)) {
                    printf(">> Estudiante eliminado (logicamente) con exito.\n");
                } else {
                    printf(">> No se pudo eliminar (no existe).\n");
                }
                break;
                
            case 4:
                imprimirTabla(tabla);
                break;
                
            case 5:
                printf("Saliendo del sistema de registro...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
        
    } while (opcion != 5);
    
    return 0;
}