=========================================
SISTEMA DE TABLA DE SÍMBOLOS (HASH TABLE)
=========================================

Este programa implementa una Tabla Hash (Tabla de Símbolos) con encadenamiento para almacenar y gestionar identificadores.

-----------------------------------------
CÓMO USAR EL PROGRAMA
-----------------------------------------

Para ejecutar el programa se debe usar ".\ADA07_E03\ADA07_AP02\tabla_simbolos.exe"

Al ejecutar el programa, se presentará el menú principal con las siguientes 5 opciones. Solo debe ingresar el número de la opción deseada (1 a 5) y presionar Enter.

### 1. Agregar identificador (Insertar Símbolo)

Esta opción le permite añadir un nuevo identificador (variable, función, etc.) a la Tabla de Símbolos. El programa le pedirá los siguientes 4 campos, uno a la vez. Ingrese el valor para cada campo y presione Enter.

* **Nombre del identificador:** La clave principal del símbolo (ej., 'contador', 'calcularArea').
* **Tipo:** El tipo de dato asociado (ej., 'int', 'float', 'void', 'string').
* **Ámbito:** El contexto donde se utiliza (ej., 'global', 'funcion_main', 'bloque_if').
* **Valor:** El valor actual o inicial (ej., '10', '3.1415', 'N/A').

Si el nombre ya existe, se añadirá un *nuevo* nodo con el mismo nombre en caso de colisión, pero la función de búsqueda solo devolverá el *más reciente* agregado a esa posición de la tabla.

### 2. Buscar identificador (Consultar Símbolo)

Esta opción le permite buscar un identificador por su **Nombre**.

* Ingrese el **Nombre del identificador** que desea buscar.
* Si se encuentra, se mostrarán todos sus atributos (Nombre, Tipo, Ámbito, Valor).
* Si no se encuentra, recibirá un mensaje de error.

### 3. Eliminar identificador (Eliminar Símbolo)

Esta opción le permite eliminar un identificador de la tabla.

* Ingrese el **Nombre del identificador** que desea eliminar.
* Si se encuentra, el nodo será eliminado de la lista enlazada en su posición de la Tabla Hash, y la memoria será liberada.
* Si el identificador es eliminado, recibirá un mensaje de confirmación. Si no se encuentra, recibirá un mensaje de error.

### 4. Mostrar tabla completa

Esta opción recorre toda la Tabla Hash (los 50 índices) y muestra el contenido de cada índice donde se haya almacenado al menos un símbolo.

* El formato de salida es: `[Índice] -> Nombre (Tipo, Ámbito, Valor) -> ... -> NULL`
* Esto es útil para visualizar las colisiones (varios símbolos en el mismo índice).

### 5. Salir

Finaliza la ejecución del programa.

---
**NOTA IMPORTANTE SOBRE ENTRADAS DE TEXTO:**
Para la entrada de datos (opciones 1, 2 y 3), el programa está configurado para leer cadenas de texto de hasta 49 caracteres. Si ingresa más texto, este podría ser truncado.
