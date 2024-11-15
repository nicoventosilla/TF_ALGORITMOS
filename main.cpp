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

int generarAleatorio(int min, int max) // Generar un numero aleatorio entre min y max
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
            coche.dx = 1; // Mover 2 unidades a la derecha
            coche.dy = 0;
        }
        else if (tecla == 75) // Flecha izquierda
        {
            coche.dx = -1; // Mover 2 unidades a la izquierda
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

void inicializarCochesEnemigos(int numCoches, int nivel)
{
    int posicionesY[9] = {15, 23, 30, 15, 23, 30, 15, 23, 30};
    int coloresPermitidos[] = {1, 2, 4, 5, 6, 8, 12, 13, 14}; // Colores permitidos
    int numColoresPermitidos = sizeof(coloresPermitidos) / sizeof(coloresPermitidos[0]);

    for (int i = 0; i < numCoches; ++i)
    {
        int centroX = generarAleatorio(60, 150);
        int velocidad = generarAleatorio(1, 3);
        if (nivel >= 2 && centroX < 75) // Incrementar la velocidad para coches en la izquierda a partir del nivel 2
        {
            velocidad += 1; // Incrementar la velocidad en 1
        }

        int colorAleatorio = coloresPermitidos[generarAleatorio(0, numColoresPermitidos - 1)];

        cochesEnemigos[i] = {centroX, posicionesY[i], -1, 0, colorAleatorio, velocidad};
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

// Función para borrar un coche aliado
void borrarCocheAliado(const CocheAliado& coche)
{
    CocheAliado cocheBorrado = coche;
    cocheBorrado.color = 0;
    dibujarCocheAliado(cocheBorrado);
}

// Función para inicializar los coches aliados
void inicializarCocheAliado(CocheAliado& cocheAliado, int tipo)
{
    cocheAliado.x = 140; // Aparece en el extremo derecho
    int carriles[] = {16, 22, 29};
    cocheAliado.y = carriles[generarAleatorio(0, 2)]; // Aparece en una de las tres líneas específicas
    cocheAliado.dx = -1; // Moverse de derecha a izquierda
    cocheAliado.dy = 0;
    cocheAliado.color = (tipo == 1) ? 15 : 11; // Color blanco para reparación, azul para escudo
    cocheAliado.tipo = tipo;
    cocheAliado.activo = false; // Inicialmente inactivo
}


// Función para mover y verificar colisiones con el coche principal y coches enemigos
void moverCocheAliado(CocheAliado& cocheAliado, Coche& cochePrincipal, int& vidas, Coche cochesEnemigos[],
                      int numCochesEnemigos, bool& escudoActivo, time_t& tiempoEscudo)
{
    if (!cocheAliado.activo) return;

    borrarCocheAliado(cocheAliado);
    cocheAliado.x += cocheAliado.dx;

    if (cocheAliado.x < 0)
    {
        cocheAliado.activo = false; // Desactivar el coche aliado si sale de la pantalla
    }

    // Verificar colisión con el coche principal
    if (cochePrincipal.x < cocheAliado.x + 10 &&
        cochePrincipal.x + 10 > cocheAliado.x &&
        cochePrincipal.y < cocheAliado.y + 5 &&
        cochePrincipal.y + 5 > cocheAliado.y)
    {
        if (cocheAliado.tipo == 1) // Coche de Reparación
        {
            vidas++;
            cocheAliado.activo = false; // Desactivar el coche aliado después de la colisión
        }
        else if (cocheAliado.tipo == 2) // Coche de Escudo
        {
            escudoActivo = true;
            tiempoEscudo = time(0); // Registrar el tiempo de activación del escudo
            cocheAliado.activo = false; // Desactivar el coche aliado después de la colisión
        }
    }

    // Verificar colisión con coches enemigos
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        if (cochesEnemigos[i].x < cocheAliado.x + 12 &&
            cochesEnemigos[i].x + 12 > cocheAliado.x &&
            cochesEnemigos[i].y < cocheAliado.y + 5 &&
            cochesEnemigos[i].y + 5 > cocheAliado.y)
        {
            // Borrar el coche enemigo antes de moverlo
            borrarCoche(cochesEnemigos[i]);
            // Retroceder el coche enemigo unos espacios a la derecha para evitar la colisión
            cochesEnemigos[i].x += 20;
        }
    }

    if (cocheAliado.activo)
    {
        dibujarCocheAliado(cocheAliado);
    }
}

// FUNCION PRINCIPAL DEL JUEGO

void juego(int nivel, int& vidas);

// Juega un nivel del juego
void jugarNivel(int nivel, int tiempoNivel, int siguienteNivel, int& vidas)
{
    mostrarMensajeNivel(nivel);

    system("cls");

    ocultarCursor();

    int centroY = 15 + (35 - 15) / 2 - 2;
    Coche cochePrincipal = {0, centroY, 0, 0, COLOR_COCHE_PRINCIPAL, 1};

    int numCochesEnemigos = nivel * 3;
    inicializarCochesEnemigos(numCochesEnemigos, nivel);

    CocheAliado cocheReparacion;
    inicializarCocheAliado(cocheReparacion, 1);

    CocheAliado cocheEscudo;
    inicializarCocheAliado(cocheEscudo, 2);

    bool escudoActivo = false;
    time_t tiempoEscudo = 0;
    int tiempoRestanteEscudo = 0;

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
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        dibujarCoche(cochesEnemigos[i]);
    }

    bool juegoActivo = true;
    time_t tiempoInicio = time(0);
    int tiempoAparicionReparacion = generarAleatorio(0, 20);
    // Momento aleatorio para la aparición del coche de reparación en los primeros 20 segundos
    int tiempoAparicionEscudo = generarAleatorio(0, 15);
    // Momento aleatorio para la aparición del coche de escudo en los primeros 15 segundos

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
                    juego(siguienteNivel, vidas);
                }
            }
            return;
        }

        if (segundosTranscurridos == tiempoAparicionReparacion)
        {
            cocheReparacion.activo = true; // Activar el coche de reparación en el momento aleatorio
        }

        if (segundosTranscurridos == tiempoAparicionEscudo)
        {
            cocheEscudo.activo = true; // Activar el coche de escudo en el momento aleatorio
        }

        if (escudoActivo)
        {
            tiempoRestanteEscudo = 10 - difftime(tiempoActual, tiempoEscudo);
            if (tiempoRestanteEscudo <= 0)
            {
                escudoActivo = false;
                tiempoRestanteEscudo = 0;
                gotoxy(160, 9);
                cout << "                "; // Borrar el contador del escudo
            }
            else
            {
                gotoxy(160, 9);
                cout << "Escudo: " << tiempoRestanteEscudo << " s   ";
            }
        }

        moverCoche(cochePrincipal);
        moverCocheAliado(cocheReparacion, cochePrincipal, vidas, cochesEnemigos, numCochesEnemigos, escudoActivo,
                         tiempoEscudo);
        moverCocheAliado(cocheEscudo, cochePrincipal, vidas, cochesEnemigos, numCochesEnemigos, escudoActivo,
                         tiempoEscudo);

        for (int i = 0; i < numCochesEnemigos; ++i)
        {
            borrarCoche(cochesEnemigos[i]);
            cochesEnemigos[i].x += cochesEnemigos[i].dx * cochesEnemigos[i].velocidad;
            if (cochesEnemigos[i].x < 0)
            {
                cochesEnemigos[i].x = 140;
                cochesEnemigos[i].velocidad = generarAleatorio(1, 3); // Asignar una nueva velocidad aleatoria
                int coloresPermitidos[] = {1, 2, 4, 5, 6, 8, 12, 13, 14}; // Colores permitidos
                int numColoresPermitidos = sizeof(coloresPermitidos) / sizeof(coloresPermitidos[0]);
                cochesEnemigos[i].color = coloresPermitidos[generarAleatorio(0, numColoresPermitidos - 1)];
                // Asignar un nuevo color permitido
            }

            // Verificar colisión con otros coches enemigos
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

            if (!escudoActivo && cochePrincipal.x < cochesEnemigos[i].x + 10 &&
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
                Sleep(1000);

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
                    cochesEnemigos[i].velocidad = generarAleatorio(1, 3); // Asignar una nueva velocidad aleatoria
                }
            }

            dibujarCoche(cochesEnemigos[i]);
        }

        dibujarCoche(cochePrincipal);
        Sleep(20);
    }
}


void nivel1(int& vidas)
{
    jugarNivel(1, 30, 2, vidas);
}

void nivel2(int& vidas)
{
    jugarNivel(2, 30, 3, vidas);
}

void nivel3(int& vidas)
{
    jugarNivel(3, 30, 0, vidas);
}

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
    srand(time(0)); // Initialize random seed
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
            vidas = 3; // Reinicializar vidas
            juego(1, vidas);
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
