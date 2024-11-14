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
const int COLOR_COCHE_PRINCIPAL = 10;
const int COLOR_COCHE_ENEMIGO = 12;
const int ANCHO = 100;
const int ALTO = 40;
const int NUM_ENEMY_CARS = 3;

// Estructura para los coches
struct Coche
{
    int x, y; // Posición del coche
    int dx, dy; // Dirección del movimiento
    int color; // Color del coche
    int velocidad; // Velocidad del coche
};

Coche cochesEnemigos[NUM_ENEMY_CARS];

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

    // Líneas blancas horizontales en las líneas
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
    if (_kbhit())
    {
        char tecla = _getch();
        if (tecla == 27) exit(0); // Si se presiona la tecla ESCAPE, salir del juego
        else if (tecla == 72) // Flecha arriba
        {
            coche.dx = 0;
            coche.dy = -1;
        }
        else if (tecla == 80) // Flecha abajo
        {
            coche.dx = 0;
            coche.dy = 1;
        }
        else if (tecla == 77) // Flecha derecha
        {
            coche.dx = 1;
            coche.dy = 0;
        }
        else if (tecla == 75) // Flecha izquierda
        {
            coche.dx = -1;
            coche.dy = 0;
        }
    }
    borrarCoche(coche);
    coche.x += coche.dx * coche.velocidad;
    coche.y += coche.dy * coche.velocidad;

    // Limitar el movimiento del coche dentro del rectángulo negro
    if (coche.x < 0) coche.x = 0;
    if (coche.x >= 150 - 10) coche.x = 150 - 10;
    if (coche.y < 15) coche.y = 15;
    if (coche.y >= 35 - 5) coche.y = 35 - 5;

    // Redibujar las líneas blancas
    redibujarLineas();

    dibujarCoche(coche);
}

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

// FUNCION PRINCIPAL DEL JUEGO

void juego(int nivel);

void inicializarCochesEnemigos()
{
    int posicionesY[NUM_ENEMY_CARS] = {15, 23, 30};
    for (int i = 0; i < NUM_ENEMY_CARS; ++i)
    {
        int centroX = 150 - 10;
        int velocidad = rand() % 3 + 1; // Random speed between 1 and 3
        cochesEnemigos[i] = {centroX, posicionesY[i], -1, 0, COLOR_COCHE_ENEMIGO, velocidad};
    }
}

// Juega un nivel del juego
void jugarNivel(int nivel, int tiempoNivel, int siguienteNivel)
{
    mostrarMensajeNivel(nivel);

    system("cls");

    // Initialize the main car
    int centroY = 15 + (35 - 15) / 2 - 2;
    Coche cochePrincipal = {0, centroY, 0, 0, COLOR_COCHE_PRINCIPAL, 1};

    // Initialize the enemy cars
    inicializarCochesEnemigos();

    int vidas = 3;

    ocultarCursor();

    // Call the appropriate level drawing function
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

    dibujarCoche(cochePrincipal);
    for (int i = 0; i < NUM_ENEMY_CARS; ++i)
    {
        dibujarCoche(cochesEnemigos[i]);
    }

    bool juegoActivo = true;

    time_t tiempoInicio = time(0);

    while (juegoActivo)
    {
        gotoxy(160, 5);
        color(15);
        cout << "Vidas: " << vidas;

        time_t tiempoActual = time(0);
        int segundosTranscurridos = difftime(tiempoActual, tiempoInicio);
        gotoxy(160, 3);
        cout << "Tiempo: " << segundosTranscurridos << "s";

        if (segundosTranscurridos >= tiempoNivel)
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
                    juego(siguienteNivel);
                }
            }
            return;
        }

        moverCoche(cochePrincipal);
        for (int i = 0; i < NUM_ENEMY_CARS; ++i)
        {
            borrarCoche(cochesEnemigos[i]);
            cochesEnemigos[i].x += cochesEnemigos[i].dx * cochesEnemigos[i].velocidad;
            if (cochesEnemigos[i].x < 0)
            {
                cochesEnemigos[i].x = 140;
                cochesEnemigos[i].velocidad = rand() % 3 + 1; // Reassign random speed
            }

            if (cochePrincipal.x < cochesEnemigos[i].x + 10 &&
                cochePrincipal.x + 10 > cochesEnemigos[i].x &&
                cochePrincipal.y < cochesEnemigos[i].y + 5 &&
                cochePrincipal.y + 5 > cochesEnemigos[i].y)
            {
                borrarCoche(cochePrincipal);
                borrarCoche(cochesEnemigos[i]);
                dibujarX(cochePrincipal.x, cochePrincipal.y);
                vidas--;
                gotoxy(160, 7);
                cout << "Colision! Vidas restantes: " << vidas;
                Sleep(2000);

                if (vidas == 0)
                {
                    juegoActivo = false;
                    mostrarMensajePerdio();
                    return;
                }
                else
                {
                    cochePrincipal.x = 0;
                    cochePrincipal.y = centroY;
                    cochesEnemigos[i].x = 150 - 10;
                    cochesEnemigos[i].y = (i == 0) ? 15 : (i == 1) ? 23 : 30;
                    cochesEnemigos[i].velocidad = rand() % 3 + 1; // Reassign random speed

                    // Redraw the lines and the black track to clear the "X"
                    color(0); // Black color for the track
                    for (int j = 15; j < 35; j++)
                    {
                        gotoxy(0, j);
                        for (int k = 0; k < 150; k++)
                        {
                            cout << " ";
                        }
                    }
                    redibujarLineas();
                }
            }

            dibujarCoche(cochesEnemigos[i]);
        }

        dibujarCoche(cochePrincipal);
        Sleep(20);
    }
}

void nivel1()
{
    jugarNivel(1, 30, 2);
}

void nivel2()
{
    jugarNivel(2, 30, 3);
}

void nivel3()
{
    jugarNivel(3, 30, 0);
}

void juego(int nivel)
{
    switch (nivel)
    {
    case 1:
        nivel1();
        break;
    case 2:
        nivel2();
        break;
    case 3:
        nivel3();
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
    srand(time(0)); // Inicializa la semilla de números aleatorios
    mostrarMensajeBienvenida();
    ocultarCursor();
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
        char tecla = _getch();
        switch (tecla)
        {
        case '1':
            juego(1);
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
