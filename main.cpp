#include <iostream> // Para usar las funciones de entrada y salida
#include <windows.h> // Para usar las funciones de la consola
#include <conio.h> // Para usar la función _kbhit()
#include <ctime> // Para usar la función time()
#include <cstdio> // Para usar la función _getch()
#include <cstdlib> // Para usar la función exit()
#include <chrono> // Para medir el tiempo de ejecución

using namespace std;

// Constantes
const char CUBO = 219;
const int COLOR_FONDO = 10;
const int COLOR_FONDO_NIVEL2 = 14;
const int COLOR_FONDO_NIVEL3 = 12;
const int COLOR_COCHE_PRINCIPAL = 15;
const int COLOR_COCHE_ENEMIGO = 12;
const int ANCHO = 100;
const int ALTO = 40;
const int NUM_ENEMY_CARS = 9;
int vidas = 3;

// Estructura para los coches
struct Coche
{
    int x, y; // Posición del coche
    int dx, dy; // Dirección del movimiento
    int color; // Color del coche
    int velocidad; // Velocidad del coche
};

Coche cochesEnemigos[NUM_ENEMY_CARS]; // Arreglo de coches enemigos

// FUNCIONES DE UTILIDADES

// Oculta el cursor de la consola
void ocultarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Cambia el color del texto en la consola
void color(int color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

// Mueve el cursor a la posición (x, y) en la consola
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Generar un numero aleatorio entre min y max
int generarAleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Espera a que el usuario presione la tecla ESCAPE
void esperarTecla()
{
    cout << endl << "Presione <ESCAPE> para volver al menu principal" << endl;
    char tecla;
    do
    {
        tecla = _getch();
    }
    while (tecla != 27);
}

// FUNCIONES DE DIBUJO

// Dibuja el escenario del nivel 1
void dibujarEscenarioNivel1()
{
    ocultarCursor();

    // Primer rectángulo
    color(10);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 150; j++)
        {
            cout << CUBO;
        }
    }

    // Tercer rectángulo
    color(10);
    for (int i = 35; i < 50; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 150; j++)
        {
            cout << CUBO;
        }
    }

    // Líneas blancas horizontales
    color(15); // Color blanco
    for (int j = 0; j < 150; j += 6) // Incrementa en 6 para tener 4 cubos y 2 de separación
    {
        for (int k = 0; k < 4; k++) // Dibuja 4 cubos
        {
            gotoxy(j + k, 21);
            cout << CUBO;
            gotoxy(j + k, 28);
            cout << CUBO;
        }
    }
}

// Dibuja el escenario del nivel 2
void dibujarEscenarioNivel2()
{
    // Código para dibujar el escenario del nivel 2
}

// Dibuja el escenario del nivel 3
void dibujarEscenarioNivel3()
{
    // Código para dibujar el escenario del nivel 3
}

// Dibuja un coche en la posición especificada
void dibujarCoche(const Coche& coche)
{
    color(coche.color);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gotoxy(coche.x + j, coche.y + i);
            cout << CUBO;
        }
    }
}

// Borra un coche de la pantalla
void borrarCoche(const Coche& coche)
{
    Coche cocheBorrado = coche;
    cocheBorrado.color = 0;
    dibujarCoche(cocheBorrado);
}

// Redibuja las líneas blancas horizontales
void redibujarLineas()
{
    color(15); // Color blanco
    for (int j = 0; j < 150; j += 6) // Incrementa en 6 para tener 4 cubos y 2 de separación
    {
        for (int k = 0; k < 4; k++) // Dibuja 4 cubos
        {
            gotoxy(j + k, 21);
            cout << CUBO;
            gotoxy(j + k, 28);
            cout << CUBO;
        }
    }
}

// FUNCIONES DE LA LOGICA DEL JUEGO

// Mueve un coche según la entrada del usuario
void moverCoche(Coche& coche)
{
    if (_kbhit()) // Si se presiona una tecla
    {
        char tecla = _getch(); // Leer la tecla presionada
        if (tecla == 27) exit(0); // Si se presiona la tecla ESCAPE, salir del juego
        else if (tecla == 72) // Flecha arriba
        {
            coche.dx = 0;
            coche.dy = -1; // Mover 1 unidad hacia arriba
        }
        else if (tecla == 80) // Flecha abajo
        {
            coche.dx = 0;
            coche.dy = 1; // Mover 1 unidad hacia abajo
        }
        else if (tecla == 77) // Flecha derecha
        {
            coche.dx = 1; // Mover 2 unidades a la derecha
            coche.dy = 0;
        }
        else if (tecla == 75) // Flecha izquierda
        {
            coche.dx = -1; // Mover 2 unidades a la izquierda
            coche.dy = 0;
        }
    }
    borrarCoche(coche); // Borrar el coche de la posición actual
    coche.x += coche.dx * coche.velocidad; // Movemos el coche en la dirección especificada
    coche.y += coche.dy * coche.velocidad;

    // Limitar el movimiento del coche dentro de la pista
    if (coche.x < 0) coche.x = 0;
    if (coche.x >= 150 - 10) coche.x = 150 - 10;
    if (coche.y < 15) coche.y = 15;
    if (coche.y >= 35 - 5) coche.y = 35 - 5;

    redibujarLineas(); // Redibujar las líneas blancas

    dibujarCoche(coche); // Dibujar el coche en la nueva posición
}

// Dibuja una X en la posición especificada
void dibujarX(int x, int y)
{
    color(15); // Color blanco

    gotoxy(x, y);
    cout << CUBO;
    gotoxy(x + 1, y + 1);
    cout << CUBO;
    gotoxy(x + 2, y + 2);
    cout << CUBO;
    gotoxy(x + 3, y + 3);
    cout << CUBO;
    gotoxy(x + 4, y + 4);
    cout << CUBO;

    gotoxy(x + 4, y);
    cout << CUBO;
    gotoxy(x + 3, y + 1);
    cout << CUBO;
    gotoxy(x + 2, y + 2);
    cout << CUBO;
    gotoxy(x + 1, y + 3);
    cout << CUBO;
    gotoxy(x, y + 4);
    cout << CUBO;
}

// Muestra un mensaje de nivel antes de iniciar el juego
void mostrarMensajeNivel(int nivel)
{
    system("cls");
    cout << "-------------------" << endl;
    cout << "Nivel " << nivel << endl;
    cout << "-------------------" << endl;
    Sleep(2000); // Pausa para mostrar el mensaje de nivel
}

// Muestra un mensaje de que el jugador perdió el juego
void mostrarMensajePerdio()
{
    system("cls");
    color(15);
    cout << "-------------------" << endl;
    cout << "Perdiste el juego!" << endl;
    cout << "-------------------" << endl;
    Sleep(1000); // Pausa para mostrar el mensaje de que perdió el juego
    esperarTecla(); // Espera a que el usuario presione una tecla para regresar al menú principal
}

// Muestra un mensaje de que el jugador ganó el juego
void mostrarMensajeGanasteElJuego()
{
    system("cls");
    color(15);
    cout << "-------------------" << endl;
    cout << "Felicidades! Has ganado el juego!" << endl;
    cout << "-------------------" << endl;
    cout << "Presione Enter para continuar..." << endl;
    while (_getch() != 13); // Espera a que el usuario presione Enter (código ASCII 13)
}

// Muestra un mensaje de que el jugador ganó el nivel
void mostrarMensajeGanaste()
{
    system("cls");
    color(15);
    cout << "-------------------" << endl;
    cout << "Felicidades! Has ganado el nivel!" << endl;
    cout << "-------------------" << endl;
    cout << "Presione Enter para continuar..." << endl;
    while (_getch() != 13); // Espera a que el usuario presione Enter (código ASCII 13)
}

// Inicializa los coches enemigos en posiciones aleatorias
void inicializarCochesEnemigos(int numCoches, int nivel)
{
    int posicionesY[9] = {15, 23, 30, 15, 23, 30, 15, 23, 30}; // Posiciones Y de los coches enemigos
    int coloresPermitidos[] = {1, 4, 5, 6, 8, 12, 13, 14}; // Colores permitidos
    int numColoresPermitidos = sizeof(coloresPermitidos) / sizeof(coloresPermitidos[0]); // Número de colores permitidos

    for (int i = 0; i < numCoches; ++i)
    {
        int centroX = generarAleatorio(60, 150); // Posición X aleatoria
        int velocidad = generarAleatorio(1, 3); // Velocidad aleatoria
        if (nivel >= 2 && centroX < 85) // Incrementar la velocidad para coches en la izquierda a partir del nivel 2
        {
            velocidad += 1; // Incrementar la velocidad en 1
        }

        int colorAleatorio = coloresPermitidos[generarAleatorio(0, numColoresPermitidos - 1)]; // Color aleatorio

        cochesEnemigos[i] = {centroX, posicionesY[i], -1, 0, colorAleatorio, velocidad}; // Inicializar el coche enemigo
    }
}

// Estructura para los coches aliados
struct CocheAliado
{
    int x, y; // Posición del coche
    int dx, dy; // Dirección del movimiento
    int color; // Color del coche
    int tipo; // Tipo de aliado (1: Reparación, 2: Escudo, 3: Velocidad)
    bool activo; // Indica si el coche aliado está activo
};

// Función para dibujar un coche aliado
void dibujarCocheAliado(const CocheAliado& coche)
{
    color(coche.color); // Color del coche
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gotoxy(coche.x + j, coche.y + i);
            cout << CUBO;
        }
    }
}

// Función para borrar un coche aliado
void borrarCocheAliado(const CocheAliado& coche)
{
    CocheAliado cocheBorrado = coche; // Crear una copia del coche
    cocheBorrado.color = 0;
    dibujarCocheAliado(cocheBorrado); // Dibujar el coche borrado
}

// Función para inicializar los coches aliados
void inicializarCocheAliado(CocheAliado& cocheAliado, int tipo)
{
    cocheAliado.x = 140; // Aparece en el extremo derecho
    int carriles[] = {16, 22, 29}; // Posiciones Y de los carriles
    cocheAliado.y = carriles[generarAleatorio(0, 2)]; // Aparece en una de las tres líneas específicas
    cocheAliado.dx = -1; // Moverse de derecha a izquierda
    cocheAliado.dy = 0; // No se mueve verticalmente
    cocheAliado.color = (tipo == 1) ? 15 : (tipo == 2) ? 11 : 10;
    // Color blanco para reparación, azul para escudo, verde para velocidad
    cocheAliado.tipo = tipo; // Tipo de coche aliado
    cocheAliado.activo = false; // Inicialmente inactivo
}


// Función para mover y verificar colisiones con el coche principal y coches enemigos
void moverCocheAliado(CocheAliado& cocheAliado, Coche& cochePrincipal, int& vidas, Coche cochesEnemigos[],
                      int numCochesEnemigos, bool& escudoActivo, time_t& tiempoEscudo, bool& velocidadActiva,
                      time_t& tiempoVelocidad)
{
    if (!cocheAliado.activo) return; // Si el coche aliado no está activo, no hacer nada

    borrarCocheAliado(cocheAliado); // Borrar el coche aliado de la posición actual
    cocheAliado.x += cocheAliado.dx; // Mover el coche aliado hacia la izquierda

    // Si el coche aliado llega al extremo izquierdo, desactivarlo
    if (cocheAliado.x < 0)
    {
        cocheAliado.activo = false;
    }

    // Verificar colisión con el coche principal
    if (cochePrincipal.x < cocheAliado.x + 10 &&
        cochePrincipal.x + 10 > cocheAliado.x &&
        cochePrincipal.y < cocheAliado.y + 5 &&
        cochePrincipal.y + 5 > cocheAliado.y)
    {
        if (cocheAliado.tipo == 1) // Reparación
        {
            vidas++;
            cocheAliado.activo = false;
        }
        else if (cocheAliado.tipo == 2) // Escudo
        {
            escudoActivo = true;
            tiempoEscudo = time(0);
            cocheAliado.activo = false;
        }
        else if (cocheAliado.tipo == 3) // Velocidad
        {
            velocidadActiva = true;
            tiempoVelocidad = time(0);
            cochePrincipal.velocidad = 2;
            cocheAliado.activo = false;
        }
    }

    // Verificar colisión con los coches enemigos
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        if (cochesEnemigos[i].x < cocheAliado.x + 12 &&
            cochesEnemigos[i].x + 12 > cocheAliado.x &&
            cochesEnemigos[i].y < cocheAliado.y + 5 &&
            cochesEnemigos[i].y + 5 > cocheAliado.y)
        {
            borrarCoche(cochesEnemigos[i]);
            cochesEnemigos[i].x += 10;
        }
    }

    // Dibujar el coche aliado en la nueva posición
    if (cocheAliado.activo)
    {
        dibujarCocheAliado(cocheAliado);
    }
}

// FUNCION PRINCIPAL DEL JUEGO

// Función principal que controla el flujo del juego según el nivel actual
void juego(int nivel, int& vidas);

// Juega un nivel del juego
void jugarNivel(int nivel, int tiempoNivel, int siguienteNivel, int& vidas)
{
    mostrarMensajeNivel(nivel);
    system("cls");
    ocultarCursor();

    // Inicializar el coche principal
    int centroY = 15 + (35 - 15) / 2 - 2;
    Coche cochePrincipal = {0, centroY, 0, 0, COLOR_COCHE_PRINCIPAL, 1};

    // Inicializar los coches enemigos
    int numCochesEnemigos = 3 + (nivel - 1) * 2;
    inicializarCochesEnemigos(numCochesEnemigos, nivel);

    // Inicializar los coches aliados
    CocheAliado cocheReparacion;
    inicializarCocheAliado(cocheReparacion, 1);

    CocheAliado cocheEscudo;
    inicializarCocheAliado(cocheEscudo, 2);

    CocheAliado cocheVelocidad;
    inicializarCocheAliado(cocheVelocidad, 3);

    // Variables para controlar el tiempo de los coches aliados
    bool escudoActivo = false;
    time_t tiempoEscudo = 0;
    int tiempoRestanteEscudo = 0;

    bool velocidadActiva = false;
    time_t tiempoVelocidad = 0;
    int tiempoRestanteVelocidad = 0;

    // Dibujar el escenario según el nivel
    switch (nivel)
    {
    case 1:
        dibujarEscenarioNivel1();
        break;
    case 2:
        dibujarEscenarioNivel2();
        break;
    case 3:
        dibujarEscenarioNivel3();
        break;
    }

    dibujarCoche(cochePrincipal); // Dibujar el coche principal

    // Dibujar los coches enemigos
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        dibujarCoche(cochesEnemigos[i]);
    }

    // Variables para controlar el flujo del juego
    bool juegoActivo = true; // Indica si el juego está activo
    time_t tiempoInicio = time(0); // Tiempo de inicio del juego
    int tiempoAparicionReparacion = generarAleatorio(0, 16); // Tiempo de aparición del coche de reparación
    int tiempoAparicionEscudo = generarAleatorio(0, 13); // Tiempo de aparición del coche de escudo
    int tiempoAparicionVelocidad = generarAleatorio(0, 19); // Tiempo de aparición del coche de velocidad

    // Bucle principal del juego
    while (juegoActivo)
    {
        // Mostrar información del juego
        gotoxy(160, 5);
        color(15);
        cout << "Vidas: " << vidas;

        // Mostrar el tiempo transcurrido
        time_t tiempoActual = time(0);
        int tiempoRestante = tiempoNivel - difftime(tiempoActual, tiempoInicio);
        gotoxy(160, 3);
        cout << "Tiempo: " << tiempoRestante << " s ";

        // Verificar si se ha agotado el tiempo del nivel
        if (tiempoRestante <= 0)
        {
            juegoActivo = false;
            if (nivel == 3)
            {
                mostrarMensajeGanasteElJuego();
            }
            else
            {
                mostrarMensajeGanaste();
                if (siguienteNivel != 0)
                {
                    juego(siguienteNivel, vidas);
                }
            }
            return;
        }

        // Verificar si es el momento de activar los coches aliados
        if (tiempoRestante == tiempoNivel - tiempoAparicionReparacion)
        {
            cocheReparacion.activo = true;
        }

        if (tiempoRestante == tiempoNivel - tiempoAparicionEscudo)
        {
            cocheEscudo.activo = true;
        }

        if (tiempoRestante == tiempoNivel - tiempoAparicionVelocidad)
        {
            cocheVelocidad.activo = true;
        }

        // Verificar si el escudo está activo
        if (escudoActivo)
        {
            tiempoRestanteEscudo = 10 - difftime(tiempoActual, tiempoEscudo);
            if (tiempoRestanteEscudo <= 0)
            {
                escudoActivo = false;
                tiempoRestanteEscudo = 0;
                gotoxy(160, 9);
                cout << "                ";
            }
            else
            {
                gotoxy(160, 9);
                cout << "Escudo: " << tiempoRestanteEscudo << " s ";
            }
        }

        // Verificar si la velocidad está activa
        if (velocidadActiva)
        {
            tiempoRestanteVelocidad = 10 - difftime(tiempoActual, tiempoVelocidad);
            if (tiempoRestanteVelocidad <= 0)
            {
                velocidadActiva = false;
                tiempoRestanteVelocidad = 0;
                cochePrincipal.velocidad = 1;
                gotoxy(160, 11);
                cout << "                ";
            }
            else
            {
                gotoxy(160, 11);
                cout << "Velocidad: " << tiempoRestanteVelocidad << " s ";
            }
        }

        // Mover los coches
        moverCoche(cochePrincipal);
        moverCocheAliado(cocheReparacion, cochePrincipal, vidas, cochesEnemigos, numCochesEnemigos, escudoActivo,
                         tiempoEscudo, velocidadActiva, tiempoVelocidad);
        moverCocheAliado(cocheEscudo, cochePrincipal, vidas, cochesEnemigos, numCochesEnemigos, escudoActivo,
                         tiempoEscudo, velocidadActiva, tiempoVelocidad);
        moverCocheAliado(cocheVelocidad, cochePrincipal, vidas, cochesEnemigos, numCochesEnemigos, escudoActivo,
                         tiempoEscudo, velocidadActiva, tiempoVelocidad);

        // Mover los coches enemigos
        for (int i = 0; i < numCochesEnemigos; ++i)
        {
            borrarCoche(cochesEnemigos[i]);
            cochesEnemigos[i].x += cochesEnemigos[i].dx * cochesEnemigos[i].velocidad;

            // Si el coche enemigo llega al extremo izquierdo, reiniciar su posición
            if (cochesEnemigos[i].x < 0)
            {
                cochesEnemigos[i].x = 140;
                cochesEnemigos[i].velocidad = generarAleatorio(1, 3);
                int coloresPermitidos[] = {1, 4, 5, 6, 8, 12, 13, 14};
                int numColoresPermitidos = sizeof(coloresPermitidos) / sizeof(coloresPermitidos[0]);
                cochesEnemigos[i].color = coloresPermitidos[generarAleatorio(0, numColoresPermitidos - 1)];
            }

            // Verificar colisión con los coches enemigos
            for (int j = 0; j < numCochesEnemigos; ++j)
            {
                if (i != j &&
                    cochesEnemigos[i].x < cochesEnemigos[j].x + 10 &&
                    cochesEnemigos[i].x + 10 > cochesEnemigos[j].x &&
                    cochesEnemigos[i].y < cochesEnemigos[j].y + 5 &&
                    cochesEnemigos[i].y + 5 > cochesEnemigos[j].y)
                {
                    cochesEnemigos[i].x = cochesEnemigos[j].x + 20;
                }
            }

            // Verificar colisión con el coche principal
            if (!escudoActivo && cochePrincipal.x < cochesEnemigos[i].x + 10 &&
                cochePrincipal.x + 10 > cochesEnemigos[i].x &&
                cochePrincipal.y < cochesEnemigos[i].y + 5 &&
                cochePrincipal.y + 5 > cochesEnemigos[i].y)
            {
                borrarCoche(cochePrincipal);
                borrarCoche(cochesEnemigos[i]);
                dibujarX(cochePrincipal.x, cochePrincipal.y); // Dibujar una X en la posición del coche principal
                vidas--; // Decrementar las vidas
                gotoxy(160, 7);
                cout << "Colision! Vidas restantes: " << vidas; // Mostrar un mensaje de colisión
                Sleep(1000);

                // Limpiar el mensaje de colisión
                gotoxy(160, 7);
                cout << "                            ";

                // Verificar si el jugador ha perdido
                if (vidas == 0)
                {
                    juegoActivo = false;
                    mostrarMensajePerdio();
                    return;
                }
                else
                {
                    // Reiniciar la posición del coche principal y los coches enemigos
                    cochePrincipal.x = 0;
                    cochePrincipal.y = centroY;
                    cochesEnemigos[i].x = 150 - 10;
                    cochesEnemigos[i].y = (i == 0) ? 15 : (i == 1) ? 23 : 30;
                    cochesEnemigos[i].velocidad = generarAleatorio(1, 3);
                }
            }

            dibujarCoche(cochesEnemigos[i]); // Dibujar el coche enemigo en la nueva posición
        }

        dibujarCoche(cochePrincipal); // Dibujar el coche principal
        Sleep(20); // Pausa de 20 ms
    }
}

// Función para jugar el nivel 1
void nivel1(int& vidas)
{
    jugarNivel(1, 30, 2, vidas);
}

// Función para jugar el nivel 2
void nivel2(int& vidas)
{
    jugarNivel(2, 30, 3, vidas);
}

// Función para jugar el nivel 3
void nivel3(int& vidas)
{
    jugarNivel(3, 30, 0, vidas);
}

// Función principal que controla el flujo del juego según el nivel actual
void juego(int nivel, int& vidas)
{
    switch (nivel)
    {
    case 1:
        nivel1(vidas);
        break;
    case 2:
        nivel2(vidas);
        break;
    case 3:
        nivel3(vidas);
        break;
    default:
        break;
    }
}

// FUNCIONES DE LA INTERFAZ

// Muestra las instrucciones del juego
void instrucciones()
{
    system("cls");
    cout << "-------------------";
    cout << "Instrucciones";
    cout << "-------------------" << endl;
    cout << "DESCRIPCION" << endl;
    cout <<
        "Bienvenido a Between Lanes! Preparate para enfrentar el trafico de Lima y aprender a manejar de manera responsable"
        << endl;
    cout << endl << "CONTROLES BASICOS" << endl;
    cout << "Flecha Arriba: Mover hacia arriba" << endl;
    cout << "Flecha Abajo: Mover hacia abajo" << endl;
    cout << "Flecha Derecha: Mover a la derecha" << endl;
    cout << "Flecha Izquierda: Mover a la izquierda" << endl;
    cout << endl << "OBJETIVO DEL JUEGO" << endl;
    cout << "Esquivar obstaculos y llegar lo mas lejos posible sin chocar" << endl;
    cout << "Manten la calma y planea tus movimientos con anticipacion" << endl;
    cout << endl << "CONSEJOS" << endl;
    cout << "No te apresures, la paciencia es clave para sobrevivir en el trafico" << endl;
    cout << "Manten la vista en el camino y evita distracciones" << endl;
    cout << "Buena suerte!" << endl;
    esperarTecla();
}

// Muestra los créditos del juego
void creditos()
{
    system("cls");
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "  ______     ______     ______     _____     __     ______   ______     ______     " << endl;
    cout << " /\\  ___\\   /\\  == \\   /\\  ___\\   /\\  __-.  /\\ \\   /\\__  _\\ /\\  __ \\   /\\  ___\\    " <<
        endl;
    cout <<
        " \\ \\ \\____  \\ \\  __<   \\ \\  __\\   \\ \\ \\/\\ \\ \\ \\ \\  \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\___  \\   "
        << endl;
    cout <<
        "  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\____-  \\ \\_\\    \\ \\_\\  \\ \\_____\\  \\/\\_____\\  "
        << endl;
    cout << "   \\/_____/   \\/_/ /_/   \\/_____/   \\/____/   \\/_/     \\/_/   \\/_____/   \\/_____/  " << endl;
    cout << "                                                                                   " << endl;
    cout << "                          UPC CAMPUS SAN MIGUEL                                    " << endl;
    cout << "                     INTRODUCCION A LOS ALGORITMOS                                 " << endl;
    cout << "                                                                                   " << endl;
    cout << "                             PROGRAMADORES                                         " << endl;
    cout << "                       Ventosilla Chelge Nicolas                                   " << endl;
    cout << "                          Ponce Wong Jarumi                                        " << endl;
    cout << "                         Celis Salinas Alvaro                                      " << endl;
    cout << "                                                                                   " << endl;
    cout << "                               DOCENTE                                             " << endl;
    cout << "                         Rojas Sihuay Diego                                        " << endl;
    cout << "                                                                                   " << endl;
    cout << "                                                                                   " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    esperarTecla();
}

// Muestra un mensaje de despedida y sale del juego
void salir()
{
    system("cls");
    cout << "Gracias por jugar!" << endl;
}

void mostrarMensajeBienvenida()
{
    system("cls");
    cout <<
        "************************************************************************************************************************************"
        << endl;
    cout <<
        "************************************************************************************************************************************"
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "                           ____       __                                                                                            "
        << endl;
    cout <<
        "                          / __ )___  / /__      _____  ___  ____                                                                    "
        << endl;
    cout <<
        "                         / __  / _ \\/ __/ | /| / / _ \\/ _ \\/ __ \\                                                                   "
        << endl;
    cout <<
        "                        / /_/ /  __/ /_ | |/ |/ /  __/  __/ / / /                                                                   "
        << endl;
    cout <<
        "                       /_____/\\___/\\__/ |__/|__/\\___/\\___/_/ /_/                                                                    "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "                                                                             __                                                     "
        << endl;
    cout <<
        "                                                                            / /   ____ _____  ___  _____                            "
        << endl;
    cout <<
        "                                                                           / /   / __ `/ __ \\/ _ \\/ ___/                            "
        << endl;
    cout <<
        "                                                                          / /___/ /_/ / / / /  __(__  )                             "
        << endl;
    cout <<
        "                                                                         /_____/\\__,_/_/ /_/\\___/____/                              "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "   -------------------------------------------------------------------------------------------------------------------------------  "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "        --         --       --          --          --             --         --                   --                --             "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "   -------------------------------------------------------------------------------------------------------------------------------  "
        << endl;
    cout <<
        "                                                                                                                                    "
        << endl;
    cout <<
        "************************************************************************************************************************************"
        << endl;
    cout <<
        "************************************************************************************************************************************"
        << endl;
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch(); // Espera a que el usuario presione una tecla
}


// Función principal
int main()
{
    srand(time(0)); // Inicializar la semilla para generar números aleatorios
    mostrarMensajeBienvenida(); // Mostrar el mensaje de bienvenida
    ocultarCursor(); // Ocultar el cursor de la consola

    // Bucle principal del menú
    while (true)
    {
        system("cls");
        color(15); // Color blanco
        cout << "-------------------";
        cout << "Between Lines";
        cout << "-------------------" << endl;
        cout << "[1] Jugar" << endl;
        cout << "[2] Instrucciones" << endl;
        cout << "[3] Creditos" << endl;
        cout << "[4] Salir" << endl;
        char tecla = _getch(); // Leer la tecla presionada
        switch (tecla) // Verificar la opción seleccionada
        {
        case '1':
            vidas = 3; // Reinicializar vidas
            juego(1, vidas); // Jugar el nivel 1
            break;
        case '2':
            instrucciones();
            break;
        case '3':
            creditos();
            break;
        case '4':
            salir();
            return 0;
        }
    }
}
