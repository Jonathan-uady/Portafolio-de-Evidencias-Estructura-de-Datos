#include "movie_list.h"

void flush_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void handle_insert_movie(Node** head) {
    Movie new_movie;
    printf("\n--- Insertar Nueva Pelicula ---\n");
    
    printf("Ingrese ID (ej. tt1234567): ");
    flush_input_buffer(); 
    if (fgets(new_movie.id, sizeof(new_movie.id), stdin) == NULL) return;
    new_movie.id[strcspn(new_movie.id, "\n")] = 0;
    
    printf("Ingrese Titulo: ");
    if (fgets(new_movie.title, sizeof(new_movie.title), stdin) == NULL) return;
    new_movie.title[strcspn(new_movie.title, "\n")] = 0;
    
    insert_movie_at_head(head, new_movie);
    printf("Insercion exitosa.\n");
}

void handle_delete_movie(Node** head) {
    char search_term[MAX_STRING_LENGTH];
    Movie deleted_movie = {0};
    char confirmation;
    
    printf("Ingrese parte o titulo completo de la pelicula a eliminar: ");
    flush_input_buffer();
    if (fgets(search_term, sizeof(search_term), stdin) == NULL) return;
    search_term[strcspn(search_term, "\n")] = 0;

    Node* current = *head;
    Node* node_to_delete = NULL;
    char lower_search_term[MAX_STRING_LENGTH];
    char lower_current_title[MAX_STRING_LENGTH];
    strncpy(lower_search_term, search_term, MAX_STRING_LENGTH - 1); to_lower_case(lower_search_term);

    while (current != NULL) {
        strncpy(lower_current_title, current->data.title, MAX_STRING_LENGTH - 1); to_lower_case(lower_current_title);
        if (strstr(lower_current_title, lower_search_term) != NULL) { node_to_delete = current; break; }
        current = current->next;
    }

    if (node_to_delete == NULL) {
        printf("No se encontro la pelicula: '%s'.\n", search_term);
        return;
    }

    printf("\nSe encontro la siguiente pelicula. Desea eliminarla? (s/n)\n");
    print_movie_info(node_to_delete->data);
    printf("Confirme su eliminacion (s/n): ");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) == 's') {
        if (delete_movie(head, search_term, &deleted_movie)) {
             printf("Pelicula '%s' eliminada exitosamente.\n", deleted_movie.title);
        } else {
             printf("Error al eliminar la pelicula.\n");
        }
    } else {
        printf("Eliminacion cancelada por el usuario.\n");
    }
}


int main() {
    Node* movie_head = NULL;
    int choice;
    char search_term[MAX_STRING_LENGTH];

    printf("--- GESTION DE PELICULAS CON LISTA DOBLEMENTE LIGADA ---\n");

    int count = import_data(&movie_head, FILE_NAME);
    if (count < 0) printf("Error al cargar el archivo '%s'.\n", FILE_NAME);
    else printf("Carga exitosa: %d peliculas importadas.\n", count);

    do {
        printf("\n\n--- MENU DE OPERACIONES ---\n");
        printf("1. Ver todas las peliculas\n");
        printf("2. Buscar por TITULO\n");
        printf("3. Insertar nueva pelicula\n");
        printf("4. Eliminar pelicula por titulo\n");
        printf("5. Actualizar datos de una pelicula\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Entrada no valida. Por favor, ingrese un numero.\n");
            choice = -1;
            flush_input_buffer(); 
            continue;
        }

        switch (choice) {
            case 1:
                print_list(movie_head);
                break;
            case 2:
                printf("Ingrese parte o titulo completo a buscar: ");
                flush_input_buffer();
                if (fgets(search_term, sizeof(search_term), stdin) == NULL) break;
                search_term[strcspn(search_term, "\n")] = 0;
                search_by_title(movie_head, search_term);
                break;
            case 3:
                handle_insert_movie(&movie_head);
                break;
            case 4:
                handle_delete_movie(&movie_head);
                break;
            case 5:
                printf("Ingrese parte o titulo completo de la pelicula a actualizar: ");
                flush_input_buffer();
                if (fgets(search_term, sizeof(search_term), stdin) == NULL) break;
                search_term[strcspn(search_term, "\n")] = 0;
                if (update_movie_data(movie_head, search_term)) {
                    printf("Datos actualizados correctamente.\n");
                } else {
                    printf("No se pudo actualizar o la operacion fue cancelada.\n");
                }
                break;
            case 0:
                printf("Saliendo y liberando memoria.\n");
                break;
            default:
                printf("Opcion no reconocida. Intente de nuevo.\n");
        }
    } while (choice != 0);

    free_list(movie_head);
    
    return 0;
}