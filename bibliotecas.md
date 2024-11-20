# Descripción del Proyecto

Este proyecto es un juego basado en consola escrito en C++. A continuación se explica el uso de las bibliotecas y las constantes en el código.

## Bibliotecas

Las siguientes bibliotecas están incluidas en el proyecto:

1. **`<iostream>`**: Proporciona funcionalidades para operaciones de entrada y salida.
   - Usada para flujos de entrada y salida estándar.

2. **`<windows.h>`**: Contiene declaraciones para todas las funciones de la API de Windows.
   - Usada para funciones de manipulación de la consola como ocultar el cursor y establecer el color del texto.

3. **`<conio.h>`**: Proporciona funciones de entrada/salida de consola.
   - Usada para funciones como `_kbhit()` para detectar la entrada del teclado.

4. **`<ctime>`**: Contiene funciones para manipular la fecha y la hora.
   - Usada para generar números aleatorios basados en la hora actual.

5. **`<cstdio>`**: Proporciona funcionalidades para operaciones de entrada y salida al estilo C.
   - Usada para funciones como `_getch()` para obtener un carácter de la consola.

6. **`<cstdlib>`**: Incluye funciones para realizar funciones generales como asignación de memoria, control de procesos, conversiones y otras.
   - Usada para funciones como `exit()` para terminar el programa.

7. **`<chrono>`**: Proporciona un conjunto de tipos para representar puntos en el tiempo, duraciones y relojes.
   - Usada para medir el tiempo de ejecución.

## Constantes

Las siguientes constantes están definidas en el proyecto:

1. **`CUBO`**: Representa el carácter utilizado para dibujar un cubo.
   - `const char CUBO = 219;`

2. **`COLOR_COCHE_PRINCIPAL`**: Representa el color del coche principal.
   - `const int COLOR_COCHE_PRINCIPAL = 15;`

3. **`NUM_ENEMY_CARS`**: Representa el número de coches enemigos.
   - `const int NUM_ENEMY_CARS = 9;`

4. **`vidas`**: Representa el número de vidas que tiene el jugador.
   - `int vidas = 3;`

Estas bibliotecas y constantes son esenciales para la funcionalidad y representación visual del juego.