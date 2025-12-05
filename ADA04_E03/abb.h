#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUCTURAS ---

typedef struct {
    int matricula;
    char nombre[50];
    char apellido[50];
    float* calificaciones; // Arreglo dinámico
    int numCalificaciones;
} Estudiante;

typedef struct NodoABB {
    Estudiante info;
    struct NodoABB *izq;
    struct NodoABB *der;
} NodoABB;


// --- FUNCIONES AUXILIARES ---

/**
 * Calcula el promedio de un estudiante.
 * Maneja el caso de que no tenga calificaciones.
 */
float calcularPromedio(Estudiante* e) {
    if (e->numCalificaciones == 0) {
        return 0.0;
    }
    float suma = 0.0;
    for (int i = 0; i < e->numCalificaciones; i++) {
        suma += e->calificaciones[i];
    }
    return suma / e->numCalificaciones;
}

/**
 * Imprime la información de un estudiante de forma bonita.
 */
void imprimirEstudiante(Estudiante* e) {
    printf("----------------------------------------\n");
    printf("Matricula: %d\n", e->matricula);
    printf("Nombre:    %s %s\n", e->nombre, e->apellido);
    printf("Calificaciones: ");
    if (e->numCalificaciones == 0) {
        printf("[Sin calificaciones]\n");
    } else {
        for (int i = 0; i < e->numCalificaciones; i++) {
            printf("%.2f ", e->calificaciones[i]);
        }
        printf("\n");
    }
    printf("Promedio:  %.2f\n", calcularPromedio(e));
    printf("----------------------------------------\n");
}


/**
 * Crea un nuevo nodo para el ABB.
 */
NodoABB* crearNodo(Estudiante info) {
    NodoABB* nuevo = (NodoABB*)malloc(sizeof(NodoABB));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible.\n");
        exit(1); // Salida drástica, como le gusta al profe
    }
    nuevo->info = info; // Copia la estructura
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

/**
 * Busca un nodo por matrícula (recursivo).
 * Devuelve el nodo si lo encuentra, o NULL si no.
 */
NodoABB* buscar(NodoABB* raiz, int matricula) {
    if (raiz == NULL) {
        return NULL; // No encontrado
    }
    if (raiz->info.matricula == matricula) {
        return raiz; // Encontrado
    }
    if (matricula < raiz->info.matricula) {
        return buscar(raiz->izq, matricula);
    } else {
        return buscar(raiz->der, matricula);
    }
}

/**
 * Libera toda la memoria del árbol (Post-orden).
 * ¡Importante liberar el arreglo dinámico de calificaciones primero!
 */
void liberarMemoria(NodoABB* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMemoria(raiz->izq);
    liberarMemoria(raiz->der);
    // Liberamos el arreglo dinámico de este estudiante
    free(raiz->info.calificaciones); 
    // Ahora liberamos el nodo
    free(raiz);
}


// --- FUNCIONES DEL MENÚ (1-10) ---

/**
 * 5. Inserta un nuevo estudiante en el árbol.
 * Se usa un puntero doble a la raíz para poder modificarla.
 */
void insertar(NodoABB** raiz, Estudiante info) {
    if (*raiz == NULL) {
        *raiz = crearNodo(info);
        printf("Estudiante %d insertado.\n", info.matricula);
    } else if (info.matricula < (*raiz)->info.matricula) {
        insertar(&((*raiz)->izq), info);
    } else if (info.matricula > (*raiz)->info.matricula) {
        insertar(&((*raiz)->der), info);
    } else {
        printf("Error: La matricula %d ya existe. No se inserto.\n", info.matricula);
        // Si la matrícula ya existe, liberamos la memoria que pedimos para las calificaciones
        // del estudiante que no se va a insertar.
        free(info.calificaciones);
    }
}

/**
 * 1. Genera un reporte de todos los estudiantes (ordenados por matrícula).
 * Esto es un recorrido In-Orden simple.
 */
void reportePorMatricula(NodoABB* raiz) {
    if (raiz == NULL) {
        return;
    }
    reportePorMatricula(raiz->izq);
    imprimirEstudiante(&(raiz->info));
    reportePorMatricula(raiz->der);
}

/**
 * 3. Genera un reporte de estudiantes con promedio < 70.
 * Recorrido In-Orden con una condición.
 */
void reporteMenor70(NodoABB* raiz) {
    if (raiz == NULL) {
        return;
    }
    reporteMenor70(raiz->izq);
    if (calcularPromedio(&(raiz->info)) < 70.0) {
        imprimirEstudiante(&(raiz->info));
    }
    reporteMenor70(raiz->der);
}

/**
 * 4. Genera un reporte de estudiantes con promedio >= 70.
 * Recorrido In-Orden con una condición.
 */
void reporteMayorIgual70(NodoABB* raiz) {
    if (raiz == NULL) {
        return;
    }
    reporteMayorIgual70(raiz->izq);
    if (calcularPromedio(&(raiz->info)) >= 70.0) {
        imprimirEstudiante(&(raiz->info));
    }
    reporteMayorIgual70(raiz->der);
}


/**
 * 7. Actualiza las calificaciones de un alumno (por matrícula).
 * Permite agregar una nueva calificación o modificar una existente.
 */
void actualizarCalificaciones(NodoABB* raiz, int matricula) {
    NodoABB* nodo = buscar(raiz, matricula);
    if (nodo == NULL) {
        printf("Error: No se encontro la matricula %d.\n", matricula);
        return;
    }

    Estudiante* e = &(nodo->info);
    int opcion, index;

    printf("Estudiante encontrado: %s %s\n", e->nombre, e->apellido);
    printf("Calificaciones actuales: ");
    for (int i = 0; i < e->numCalificaciones; i++) {
        printf("[%d] %.2f ", i + 1, e->calificaciones[i]);
    }
    printf("\n");

    printf("Que deseas hacer?\n");
    printf("1. Agregar una nueva calificacion\n");
    printf("2. Modificar una calificacion existente\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        // Agregar nueva calificacion
        float nuevaCal;
        printf("Ingresa la nueva calificacion: ");
        scanf("%f", &nuevaCal);

        // Aumentamos el tamaño del arreglo dinámico
        e->numCalificaciones++;
        e->calificaciones = (float*)realloc(e->calificaciones, e->numCalificaciones * sizeof(float));
        if (e->calificaciones == NULL) {
            printf("Error de memoria al actualizar calificaciones.\n");
            exit(1);
        }
        // Agregamos la nueva calificación al final
        e->calificaciones[e->numCalificaciones - 1] = nuevaCal;
        printf("Calificacion agregada con exito.\n");

    } else if (opcion == 2) {
        // Modificar calificacion
        if (e->numCalificaciones == 0) {
            printf("El estudiante no tiene calificaciones para modificar.\n");
            return;
        }
        printf("Que numero de calificacion quieres modificar (1 a %d): ", e->numCalificaciones);
        scanf("%d", &index);

        if (index < 1 || index > e->numCalificaciones) {
            printf("Indice no valido.\n");
        } else {
            float nuevaCal;
            printf("Ingresa la nueva calificacion para [%d]: ", index);
            scanf("%f", &nuevaCal);
            e->calificaciones[index - 1] = nuevaCal; // -1 porque el usuario ve 1-based
            printf("Calificacion actualizada con exito.\n");
        }
    } else {
        printf("Opcion no valida.\n");
    }
}


/**
 * 6. Eliminar un estudiante (por matrícula).
 * Esta es la función más compleja del ABB.
 */
// Auxiliar para encontrar el nodo con el valor mínimo (sucesor in-orden)
NodoABB* buscarMin(NodoABB* nodo) {
    NodoABB* actual = nodo;
    while (actual && actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

// Función principal de eliminar
NodoABB* eliminar(NodoABB* raiz, int matricula) {
    if (raiz == NULL) {
        printf("Matricula %d no encontrada para eliminar.\n", matricula);
        return raiz; // No encontrado
    }

    // 1. Buscar el nodo
    if (matricula < raiz->info.matricula) {
        raiz->izq = eliminar(raiz->izq, matricula);
    } else if (matricula > raiz->info.matricula) {
        raiz->der = eliminar(raiz->der, matricula);
    } else {
        // 2. Nodo encontrado (raiz es el nodo a eliminar)

        // Caso 1: Cero hijos o un hijo
        if (raiz->izq == NULL) {
            NodoABB* temp = raiz->der;
            // ¡Liberar memoria del estudiante!
            free(raiz->info.calificaciones);
            free(raiz);
            printf("Estudiante %d eliminado.\n", matricula);
            return temp;
        } else if (raiz->der == NULL) {
            NodoABB* temp = raiz->izq;
            // ¡Liberar memoria del estudiante!
            free(raiz->info.calificaciones);
            free(raiz);
            printf("Estudiante %d eliminado.\n", matricula);
            return temp;
        }

        // Caso 3: Dos hijos
        // Encontrar el sucesor in-orden (el más pequeño del subárbol derecho)
        NodoABB* temp = buscarMin(raiz->der);

        // Copiar la información del sucesor a este nodo
        // OJO: No podemos hacer solo `raiz->info = temp->info;`
        // porque `temp->info.calificaciones` es un puntero. Si lo copiamos
        // y luego borramos `temp`, `raiz` apuntará a memoria liberada.
        // Tenemos que "robarle" los datos.
        
        // Primero, liberamos la memoria del nodo que VAMOS a sobreescribir (el actual)
        free(raiz->info.calificaciones);
        
        // Ahora, copiamos (o "robamos") la info del sucesor
        raiz->info = temp->info; 
        
        // IMPORTANTE: Como "robamos" la info (incluyendo el puntero a calificaciones),
        // no debemos liberar `temp->info.calificaciones` cuando eliminemos `temp`.
        // Para evitar la doble liberación, hacemos que `temp->info.calificaciones`
        // apunte a NULL antes de llamar a `eliminar` recursivamente.
        // PERO, mi función `eliminar` espera que el nodo a borrar
        // (que será `temp`) libere sus propias calificaciones.
        
        // Estrategia más simple: Copiamos los datos, no el puntero.
        // 1. Liberamos las calificaciones del nodo a borrar
        free(raiz->info.calificaciones);
        
        // 2. Copiamos los datos simples
        raiz->info.matricula = temp->info.matricula;
        strcpy(raiz->info.nombre, temp->info.nombre);
        strcpy(raiz->info.apellido, temp->info.apellido);
        raiz->info.numCalificaciones = temp->info.numCalificaciones;
        
        // 3. Creamos un *nuevo* arreglo de calificaciones para `raiz`
        raiz->info.calificaciones = (float*)malloc(temp->info.numCalificaciones * sizeof(float));
        // y copiamos los valores
        for(int i=0; i < temp->info.numCalificaciones; i++) {
            raiz->info.calificaciones[i] = temp->info.calificaciones[i];
        }

        // 4. Ahora sí, eliminamos el sucesor (que ahora es un duplicado)
        // del subárbol derecho.
        raiz->der = eliminar(raiz->der, temp->info.matricula);
        // La llamada recursiva se encargará de liberar la memoria de `temp` y sus calificaciones.
    }
    return raiz;
}


/**
 * 2. Generar un reporte de todos los estudiantes (ordenados por promedio).
 * Esta es la más difícil. El ABB ordena por matrícula, no por promedio.
 * Solución:
 * 1. Recorrer el árbol y guardar punteros a todos los Estudiantes en un arreglo.
 * 2. Usar qsort() de stdlib.h para ordenar ese arreglo usando una función de comparación.
 * 3. Imprimir el arreglo ordenado.
 */
// Auxiliar para contar nodos
int contarNodos(NodoABB* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

// Auxiliar para llenar el arreglo de punteros (In-Orden)
void llenarArrayPunteros(NodoABB* raiz, Estudiante** array, int* index) {
    if (raiz == NULL) return;
    
    llenarArrayPunteros(raiz->izq, array, index);
    
    array[*index] = &(raiz->info); // Guardamos la dirección del estudiante
    (*index)++;
    
    llenarArrayPunteros(raiz->der, array, index);
}

// Auxiliar para qsort: compara dos Estudiantes (via punteros a punteros)
int compararPromedio(const void* a, const void* b) {
    // qsort nos da punteros a los elementos del arreglo.
    // Nuestro arreglo es de (Estudiante*), así que 'a' y 'b' son (Estudiante**)
    Estudiante* estA = *(Estudiante**)a;
    Estudiante* estB = *(Estudiante**)b;

    float promA = calcularPromedio(estA);
    float promB = calcularPromedio(estB);

    if (promA < promB) return -1;
    if (promA > promB) return 1;
    return 0; // Promedios iguales
}

// Función principal del reporte por promedio
void reportePorPromedio(NodoABB* raiz) {
    if (raiz == NULL) {
        printf("El arbol esta vacio.\n");
        return;
    }

    int n = contarNodos(raiz);
    // Creamos un arreglo de PUNTEROS a Estudiante
    Estudiante** array = (Estudiante**)malloc(n * sizeof(Estudiante*));
    if (array == NULL) {
        printf("Error de memoria.\n");
        return;
    }

    int index = 0;
    llenarArrayPunteros(raiz, array, &index);

    // Ordenamos el arreglo de punteros usando nuestra función de comparación
    qsort(array, n, sizeof(Estudiante*), compararPromedio);

    printf("--- Reporte Ordenado por Promedio ---\n");
    for (int i = 0; i < n; i++) {
        imprimirEstudiante(array[i]);
    }
    printf("--- Fin del Reporte ---\n");

    // Liberamos solo el arreglo de punteros, no los estudiantes (siguen en el árbol)
    free(array);
}


/**
 * 8. Dada una matrícula, contar el número de alumnos 
 * que tienen un promedio menor a él.
 * (La instrucción "8. 9." parecía un typo, la interpreté como la 8)
 * (Interpreté "calificación menor a él" como "promedio menor al de él")
 */
// Auxiliar recursivo que recorre TODO el árbol
void contarMenoresRecursivo(NodoABB* raiz, float targetPromedio, int* contador) {
    if (raiz == NULL) {
        return;
    }
    
    // Compara el promedio del nodo actual con el promedio objetivo
    if (calcularPromedio(&(raiz->info)) < targetPromedio) {
        (*contador)++;
    }
    
    // Sigue buscando en AMBOS lados (esto no es una búsqueda de ABB)
    contarMenoresRecursivo(raiz->izq, targetPromedio, contador);
    contarMenoresRecursivo(raiz->der, targetPromedio, contador);
}

// Función principal
void contarMenoresPromedio(NodoABB* raiz, int matricula) {
    // 1. Encontrar al estudiante de referencia
    NodoABB* target = buscar(raiz, matricula);
    if (target == NULL) {
        printf("Error: No se encontro la matricula %d.\n", matricula);
        return;
    }

    float targetPromedio = calcularPromedio(&(target->info));
    printf("El promedio del estudiante %d (%s) es %.2f\n", matricula, target->info.nombre, targetPromedio);

    // 2. Contar
    int contador = 0;
    // Empezamos el conteo desde la raíz, comparando con todos
    contarMenoresRecursivo(raiz, targetPromedio, &contador);

    // El conteo se incluirá a sí mismo si su promedio es menor que él mismo (nunca pasa)
    // Así que el conteo es correcto.
    printf("Numero de alumnos con promedio MENOR a %.2f: %d\n", targetPromedio, contador);
}


/**
 * 9. Mostrar los valores de los nodos de un nivel proporcionado.
 */
// Auxiliar recursiva
void mostrarNivelRecursivo(NodoABB* raiz, int nivelActual, int nivelBuscado) {
    if (raiz == NULL) {
        return; // Nivel no alcanzado por esta rama
    }
    
    if (nivelActual == nivelBuscado) {
        // Nivel encontrado, imprimir
        imprimirEstudiante(&(raiz->info));
    } else {
        // Seguir bajando
        mostrarNivelRecursivo(raiz->izq, nivelActual + 1, nivelBuscado);
        mostrarNivelRecursivo(raiz->der, nivelActual + 1, nivelBuscado);
    }
}

// Función principal
void mostrarNivel(NodoABB* raiz, int nivel) {
    if (nivel < 0) {
        printf("Nivel no valido.\n");
        return;
    }
    printf("--- Mostrando Nivel %d ---\n", nivel);
    mostrarNivelRecursivo(raiz, 0, nivel); // Empezamos en nivel 0 (raíz)
    printf("--- Fin del Nivel %d ---\n", nivel);
}


/**
 * 10. Mostrar el árbol binario de búsqueda de manera gráfica (ASCII).
 * Se usa un recorrido In-Orden Inverso (Derecha, Raíz, Izquierda)
 * para que se vea "acostado".
 */
#define ESPACIOS_POR_NIVEL 5

void mostrarArbolGrafico(NodoABB* raiz, int espacio) {
    if (raiz == NULL) {
        return; // No imprimir nada
    }

    // Aumentar distancia entre niveles
    espacio += ESPACIOS_POR_NIVEL;

    // 1. Procesar hijo derecho (el de "arriba" en el gráfico)
    mostrarArbolGrafico(raiz->der, espacio);

    // 2. Imprimir nodo actual (Raíz)
    printf("\n");
    for (int i = ESPACIOS_POR_NIVEL; i < espacio; i++) {
        printf(" ");
    }
    // Imprimimos solo la matrícula para que sea legible
    printf("%d (%s)\n", raiz->info.matricula, raiz->info.nombre);

    // 3. Procesar hijo izquierdo (el de "abajo" en el gráfico)
    mostrarArbolGrafico(raiz->izq, espacio);
}


#endif // ABB_H