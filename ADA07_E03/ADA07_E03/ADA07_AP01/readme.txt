SISTEMA DE REGISTRO DE ESTUDIANTES CON TABLA HASH (SONDEO LINEAL)

Este proyecto implementa un sistema básico de registro de estudiantes utilizando una Tabla Hash para un acceso eficiente. La matrícula del estudiante se usa como clave, y las colisiones se resuelven mediante el método de Direccionamiento Abierto (específicamente, Sondeo Lineal).

ESTRUCTURA DEL PROYECTO

El proyecto está dividido en dos archivos:

estudiante.h: Contiene la definición de las estructuras de datos, las constantes, y la implementación completa de todas las funciones (Hash, Agregar, Buscar, Eliminar, Inicializar y Mostrar).

main.c: Contiene la función principal (main) y el menú de interacción, haciendo únicamente las llamadas a las funciones definidas en estudiante.h.

EJECUCIÓN Y COMPILACIÓN

Para compilar y ejecutar este programa, necesitarás un compilador de C (como GCC o Clang).

COMPILACIÓN

Asegúrate de que los archivos estudiante.h y main.c estén en el mismo directorio.

Ejecuta el siguiente comando en tu terminal:

gcc main.c -o sistema