#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

void mostrarMenu() {
    printf("\n====== TABLA DE SÍMBOLOS ======\n");
    printf("1. Agregar identificador\n");
    printf("2. Buscar identificador\n");
    printf("3. Eliminar identificador\n");
    printf("4. Mostrar tabla completa\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

void mostrarSymbol(Symbol* s) {
    if (s == NULL) return;

    printf("\n--- Identificador encontrado ---\n");
    printf("Nombre: %s\n", s->name);
    printf("Tipo: %s\n", s->type);
    printf("Ámbito: %s\n", s->scope);
    printf("Valor: %s\n", s->value);
}

void mostrarTabla(HashTable* ht) {
    printf("\n====== CONTENIDO DE LA TABLA HASH ======\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht->table[i];
        if (temp != NULL) {
            printf("[%d] -> ", i);
            while (temp != NULL) {
                printf("%s (%s, %s, %s) -> ",
                    temp->data.name,
                    temp->data.type,
                    temp->data.scope,
                    temp->data.value);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    HashTable ht;
    initTable(&ht);

    int opcion;
    char key[MAX_STR];

    while (1) {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar(); // limpiar salto de linea

        if (opcion == 1) {
            Symbol s;

            printf("Ingrese el nombre del identificador: ");
            fgets(s.name, MAX_STR, stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Ingrese el tipo: ");
            fgets(s.type, MAX_STR, stdin);
            s.type[strcspn(s.type, "\n")] = 0;

            printf("Ingrese el ámbito: ");
            fgets(s.scope, MAX_STR, stdin);
            s.scope[strcspn(s.scope, "\n")] = 0;

            printf("Ingrese el valor: ");
            fgets(s.value, MAX_STR, stdin);
            s.value[strcspn(s.value, "\n")] = 0;

            insertSymbol(&ht, s);
            printf("✔ Identificador agregado correctamente.\n");

        } else if (opcion == 2) {
            printf("Ingrese el nombre del identificador a buscar: ");
            fgets(key, MAX_STR, stdin);
            key[strcspn(key, "\n")] = 0;

            Symbol* result = searchSymbol(&ht, key);

            if (result == NULL)
                printf("❌ Identificador no encontrado.\n");
            else
                mostrarSymbol(result);

        } else if (opcion == 3) {
            printf("Ingrese el nombre del identificador a eliminar: ");
            fgets(key, MAX_STR, stdin);
            key[strcspn(key, "\n")] = 0;

            if (removeSymbol(&ht, key))
                printf("✔ Identificador eliminado correctamente.\n");
            else
                printf("❌ No se encontró el identificador.\n");

        } else if (opcion == 4) {
            mostrarTabla(&ht);

        } else if (opcion == 5) {
            printf("Saliendo...\n");
            break;

        } else {
            printf("⚠ Opción inválida. Intente nuevamente.\n");
        }
    }

    return 0;
}
