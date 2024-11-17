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
const int COLOR_COCHE_PRINCIPAL = 15;
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

void letraTiempo(int x, int y)
{
    gotoxy(x, y);
    cout << " _____ _                      _ " << endl;
    gotoxy(x, y + 1);
    cout << "|_   _|_|___ _____ ___ ___   |_|" << endl;
    gotoxy(x, y + 2);
    cout << "  | | | | -_|     | . | . |   _ " << endl;
    gotoxy(x, y + 3);
    cout << "  |_| |_|___|_|_|_|  _|___|  |_|" << endl;
    gotoxy(x, y + 4);
    cout << "                  |_|      " << endl;
}

void numero0(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|   |" << endl;
    gotoxy(x, y + 2);
    cout << "| | |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero1(int x, int y)
{
    gotoxy(x, y);
    cout << "   _ " << endl;
    gotoxy(x, y + 1);
    cout << "  | |" << endl;
    gotoxy(x, y + 2);
    cout << "  | |" << endl;
    gotoxy(x, y + 3);
    cout << "  |_|" << endl;
}

void numero2(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|_  |" << endl;
    gotoxy(x, y + 2);
    cout << "|  _|" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero3(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|_  |" << endl;
    gotoxy(x, y + 2);
    cout << "|_  |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero4(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "| | |" << endl;
    gotoxy(x, y + 2);
    cout << "|_  |" << endl;
    gotoxy(x, y + 3);
    cout << "  |_|" << endl;
}

void numero5(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|  _|" << endl;
    gotoxy(x, y + 2);
    cout << "|_  |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero6(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|  _|" << endl;
    gotoxy(x, y + 2);
    cout << "| . |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero7(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "|_  |" << endl;
    gotoxy(x, y + 2);
    cout << "  | |" << endl;
    gotoxy(x, y + 3);
    cout << "  |_|" << endl;
}

void numero8(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "| . |" << endl;
    gotoxy(x, y + 2);
    cout << "| . |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void numero9(int x, int y)
{
    gotoxy(x, y);
    cout << " ___ " << endl;
    gotoxy(x, y + 1);
    cout << "| . |" << endl;
    gotoxy(x, y + 2);
    cout << "|_  |" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void letraS(int x, int y)
{
    gotoxy(x, y + 1);
    cout << " ___ " << endl;
    gotoxy(x, y + 2);
    cout << "|_ -|" << endl;
    gotoxy(x, y + 3);
    cout << "|___|" << endl;
}

void mostrarTiempo(int tiempoRestante)
{
    int segundos = tiempoRestante % 60;
    int decenas = segundos / 10;
    int unidades = segundos % 10;

    // Mostrar la función tiempo
    letraTiempo(155, 0);

    // Mostrar decenas
    switch (decenas)
    {
    case 0: numero0(191, 0);
        break;
    case 1: numero1(191, 0);
        break;
    case 2: numero2(191, 0);
        break;
    case 3: numero3(191, 0);
        break;
    case 4: numero4(191, 0);
        break;
    case 5: numero5(191, 0);
        break;
    case 6: numero6(191, 0);
        break;
    case 7: numero7(191, 0);
        break;
    case 8: numero8(191, 0);
        break;
    case 9: numero9(191, 0);
        break;
    }

    // Mostrar unidades
    switch (unidades)
    {
    case 0: numero0(197, 0);
        break;
    case 1: numero1(197, 0);
        break;
    case 2: numero2(197, 0);
        break;
    case 3: numero3(197, 0);
        break;
    case 4: numero4(197, 0);
        break;
    case 5: numero5(197, 0);
        break;
    case 6: numero6(197, 0);
        break;
    case 7: numero7(197, 0);
        break;
    case 8: numero8(197, 0);
        break;
    case 9: numero9(197, 0);
        break;
    }

    // Mostrar letra S
    letraS(204, 0);
}

void letraVidas(int x, int y)
{
    gotoxy(x, y);
    cout << " _____ _   _            _ " << endl;
    gotoxy(x, y + 1);
    cout << "|  |  |_|_| |___ ___   |_|" << endl;
    gotoxy(x, y + 2);
    cout << "|  |  | | . | .'|_ -|   _ " << endl;
    gotoxy(x, y + 3);
    cout << " \\___/|_|___|__,|___|  |_|" << endl;
}

void mostrarVidas(int vidas)
{
    // Mostrar la palabra "VIDAS"
    letraVidas(155, 5);

    // Descomponer el número de vidas en decenas y unidades
    int unidades = vidas % 10;

    // Mostrar unidades
    switch (unidades)
    {
    case 0: numero0(185, 5);
        break;
    case 1: numero1(185, 5);
        break;
    case 2: numero2(185, 5);
        break;
    case 3: numero3(185, 5);
        break;
    case 4: numero4(185, 5);
        break;
    case 5: numero5(185, 5);
        break;
    case 6: numero6(185, 5);
        break;
    case 7: numero7(185, 5);
        break;
    case 8: numero8(185, 5);
        break;
    case 9: numero9(185, 5);
        break;
    }
}

void dibujarSemaforo(int x, int y)
{
    color(8);
    gotoxy(x + 1, y);
    cout << CUBO;
    gotoxy(x + 2, y);
    cout << CUBO;
    gotoxy(x + 1, y + 2);
    cout << CUBO;
    gotoxy(x + 2, y + 2);
    cout << CUBO;
    gotoxy(x + 1, y + 4);
    cout << CUBO;
    gotoxy(x + 2, y + 4);
    cout << CUBO;
    gotoxy(x + 1, y + 6);
    cout << CUBO;
    gotoxy(x + 2, y + 6);
    cout << CUBO;
    gotoxy(x + 1, y + 7);
    cout << CUBO;
    gotoxy(x + 2, y + 7);
    cout << CUBO;
    gotoxy(x + 1, y + 8);
    cout << CUBO;
    gotoxy(x + 2, y + 8);
    cout << CUBO;
    for (int i = 0; i < 7; i++)
    {
        gotoxy(x, y + i);
        cout << CUBO;
    }
    for (int i = 0; i < 7; i++)
    {
        gotoxy(x + 3, y + i);
        cout << CUBO;
    }
    color(4);
    gotoxy(x + 1, y + 1);
    cout << CUBO;
    gotoxy(x + 2, y + 1);
    cout << CUBO;
    color(6);
    gotoxy(x + 1, y + 3);
    cout << CUBO;
    gotoxy(x + 2, y + 3);
    cout << CUBO;
    color(10);
    gotoxy(x + 1, y + 5);
    cout << CUBO;
    gotoxy(x + 2, y + 5);
    cout << CUBO;
}

int FONDO_NIVEL_1[15][150] = {
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3,
        0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0,
        0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0,
        0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0,
        0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0,
        0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0,
        3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3,
        0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0,
        3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3,
        0, 0
    },
    {
        0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
        0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3,
        0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0,
        0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0,
        0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0,
        0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0,
        0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0,
        3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3,
        0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0,
        3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0, 3,
        0, 0
    },
    {
        0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
        0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0
    }
};

// Dibuja el escenario del nivel 1
void dibujarEscenarioNivel1()
{
    ocultarCursor();

    // Rectángulo superior
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            if (FONDO_NIVEL_1[i][j] == 0) // Si es 0, dibuja un cubo verde claro
            {
                color(10); // Color verde claro
                cout << CUBO;
            }
            else if (FONDO_NIVEL_1[i][j] == 3) // Si es 3, dibuja un cubo verde oscuro
            {
                color(2); // Color verde oscuro
                cout << CUBO;
            }
        }
        cout << endl; // Salto de línea
    }

    dibujarSemaforo(143, 5); // Dibuja el semáforo en la posición (143, 5)

    // Rectángulo inferior
    gotoxy(0, 35);
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            if (FONDO_NIVEL_1[i][j] == 0)
            {
                color(10);
                cout << CUBO;
            }
            else if (FONDO_NIVEL_1[i][j] == 3)
            {
                color(2);
                cout << CUBO;
            }
        }
        cout << endl;
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
    dibujarSemaforo(143, 5);
}

// Dibuja el escenario del nivel 3
void dibujarEscenarioNivel3()
{
    // Código para dibujar el escenario del nivel 3
    dibujarSemaforo(143, 5);
}

// Dibuja el coche principal en la posición especificada
void dibujarCochePrincipal(const Coche& coche)
{
    color(COLOR_COCHE_PRINCIPAL);
    for (int i = 0; i < 8; i++)
    {
        gotoxy(coche.x + i, coche.y);
        cout << CUBO;
    }
    for (int i = 0; i < 5; i++)
    {
        gotoxy(coche.x + i, coche.y + 1);
        cout << CUBO;
    }
    gotoxy(coche.x + 7, coche.y + 1);
    cout << CUBO;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 2);
        cout << CUBO;
    }
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 3);
        cout << CUBO;
    }
    color(3);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 4 + i, coche.y + 1);
        cout << CUBO;
    }
    color(8);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + i, coche.y + 4);
        cout << CUBO;
    }
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 5 + i, coche.y + 4);
        cout << CUBO;
    }
}

// Dibuja el coche enemigo en la posición especificada
void dibujarCocheEnemigo(const Coche& coche)
{
    color(coche.color);
    for (int i = 0; i < 8; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y);
        cout << CUBO;
    }
    for (int i = 1; i <= 5; i++)
    {
        gotoxy(coche.x + 4 + i, coche.y + 1);
        cout << CUBO;
    }
    gotoxy(coche.x + 2, coche.y + 1);
    cout << CUBO;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 2);
        cout << CUBO;
    }
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 3);
        cout << CUBO;
    }
    color(3);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y + 1);
        cout << CUBO;
    }
    color(8);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 1 + i, coche.y + 4);
        cout << CUBO;
    }
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 6 + i, coche.y + 4);
        cout << CUBO;
    }
}

// Borra un coche de la pantalla
void borrarCoche(const Coche& coche)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gotoxy(coche.x + j, coche.y + i);
            cout << ' ';
        }
    }
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

    dibujarCochePrincipal(coche); // Dibujar el coche en la nueva posición
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

void borrarX(int x, int y)
{
    color(0); // Color negro
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
    int coloresPermitidos[] = {1, 4, 5, 12, 13}; // Colores permitidos
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

// Función para dibujar un coche de reparación en la posición especificada
void dibujarCocheReparacion(const CocheAliado& coche)
{
    color(coche.color);
    for (int i = 1; i <= 9; i++)
    {
        gotoxy(coche.x + i, coche.y);
        cout << CUBO;
    }
    for (int i = 1; i <= 6; i++)
    {
        gotoxy(coche.x + 3 + i, coche.y + 1);
        cout << CUBO;
    }
    gotoxy(coche.x + 1, coche.y + 1);
    cout << CUBO;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 3);
        cout << CUBO;
    }
    color(4);
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 2);
        cout << CUBO;
    }
    color(3);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 1 + i, coche.y + 1);
        cout << CUBO;
    }
    color(8);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 1 + i, coche.y + 4);
        cout << CUBO;
    }
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 6 + i, coche.y + 4);
        cout << CUBO;
    }
}

// Dibuja un coche con escudo en la posición especificada
void dibujarCocheEscudo(const CocheAliado& coche)
{
    color(coche.color);
    for (int i = 1; i <= 4; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y);
        cout << CUBO;
    }
    for (int i = 1; i <= 3; i++)
    {
        gotoxy(coche.x + 4 + i, coche.y + 1);
        cout << CUBO;
    }
    gotoxy(coche.x + 2, coche.y + 1);
    cout << CUBO;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 2);
        cout << CUBO;
    }
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 3);
        cout << CUBO;
    }
    color(3);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y + 1);
        cout << CUBO;
    }
    color(8);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 1 + i, coche.y + 4);
        cout << CUBO;
    }
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 6 + i, coche.y + 4);
        cout << CUBO;
    }
}

// Dibuja un coche de velocidad en la posición especificada
void dibujarCocheVelocidad(const CocheAliado& coche)
{
    color(coche.color);
    for (int i = 1; i <= 4; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y);
        cout << CUBO;
    }
    for (int i = 1; i <= 3; i++)
    {
        gotoxy(coche.x + 4 + i, coche.y + 1);
        cout << CUBO;
    }
    gotoxy(coche.x + 2, coche.y + 1);
    cout << CUBO;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 2);
        cout << CUBO;
    }
    for (int i = 0; i < 10; i++)
    {
        gotoxy(coche.x + i, coche.y + 3);
        cout << CUBO;
    }
    color(3);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 2 + i, coche.y + 1);
        cout << CUBO;
    }
    color(8);
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 1 + i, coche.y + 4);
        cout << CUBO;
    }
    for (int i = 1; i <= 2; i++)
    {
        gotoxy(coche.x + 6 + i, coche.y + 4);
        cout << CUBO;
    }
}

// Función para borrar un coche aliado
void borrarCocheAliado(const CocheAliado& coche)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gotoxy(coche.x + j, coche.y + i);
            cout << ' ';
        }
    }
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

    // Desactivar el coche aliado si se sale de la pantalla
    if (cocheAliado.x < 0)
    {
        cocheAliado.activo = false;
    }

    // Verificar colisiones con el coche principal
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

    // Verificar colisiones con los coches enemigos
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        if (cochesEnemigos[i].x < cocheAliado.x + 11 &&
            cochesEnemigos[i].x + 11 > cocheAliado.x &&
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
        if (cocheAliado.tipo == 1)
        {
            dibujarCocheReparacion(cocheAliado);
        }
        else if (cocheAliado.tipo == 2)
        {
            dibujarCocheEscudo(cocheAliado);
        }
        else if (cocheAliado.tipo == 3)
        {
            dibujarCocheVelocidad(cocheAliado);
        }
    }
}

// Estructura para los conos
struct Cono
{
    int x, y; // Posición del cono
    int color; // Color del cono
    bool activo; // Indica si el cono está activo
};

void dibujarCono(const Cono& cono)
{
    if (!cono.activo) return;
    color(cono.color);
    gotoxy(cono.x, cono.y);
    cout << "    " << CUBO << "    ";

    color(15); // Color blanco
    gotoxy(cono.x, cono.y + 1);
    cout << "   " << CUBO << CUBO << CUBO << "   ";

    color(cono.color);
    gotoxy(cono.x, cono.y + 2);
    cout << "  " << CUBO << CUBO << CUBO << CUBO << CUBO << "  ";

    color(15); // Color blanco
    gotoxy(cono.x, cono.y + 3);
    cout << " " << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO << " ";

    color(cono.color);
    gotoxy(cono.x, cono.y + 4);
    cout << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO << CUBO;
}

void borrarCono(const Cono& cono)
{
    if (!cono.activo) return;
    color(0); // Color negro (fondo)
    gotoxy(cono.x, cono.y);
    cout << "         ";
    gotoxy(cono.x, cono.y + 1);
    cout << "         ";
    gotoxy(cono.x, cono.y + 2);
    cout << "         ";
    gotoxy(cono.x, cono.y + 3);
    cout << "         ";
    gotoxy(cono.x, cono.y + 4);
    cout << "         ";
}

void inicializarCono(Cono& cono, int carrilOcupado = -1, int llantaX = -1, int llantaY = -1)
{
    int carriles[] = {16, 22, 29}; // Posiciones Y de los carriles
    int carril;
    do
    {
        carril = generarAleatorio(0, 2);
    }
    while (carril == carrilOcupado); // Asegurarse de que no sea el mismo carril que la llanta

    do
    {
        cono.x = generarAleatorio(80, 110); // Posición X aleatoria
    }
    while (cono.x == llantaX && carriles[carril] == llantaY); // Asegurarse de que no coincidan las coordenadas

    cono.y = carriles[carril]; // Aparece en uno de los carriles disponibles
    cono.color = 14; // Color del cono
    cono.activo = true; // Activar el cono
}

struct Llanta
{
    int x, y; // Posición de la llanta
    int color; // Color de la llanta
    bool activo; // Indica si la llanta está activa
};

void dibujarLlanta(const Llanta& llanta)
{
    if (!llanta.activo) return;
    color(llanta.color);
    gotoxy(llanta.x, llanta.y);
    cout << "  " << CUBO << CUBO << "  ";

    gotoxy(llanta.x, llanta.y + 1);
    cout << " " << CUBO << CUBO << CUBO << CUBO << " ";

    gotoxy(llanta.x, llanta.y + 2);
    cout << CUBO << CUBO;
    color(0); // Color negro
    cout << CUBO << CUBO;
    color(llanta.color);
    cout << CUBO << CUBO;

    gotoxy(llanta.x, llanta.y + 3);
    cout << " " << CUBO << CUBO << CUBO << CUBO << " ";

    gotoxy(llanta.x, llanta.y + 4);
    cout << "  " << CUBO << CUBO << "  ";
}

void borrarLlanta(const Llanta& llanta)
{
    if (!llanta.activo) return;
    color(0); // Color negro (fondo)
    gotoxy(llanta.x, llanta.y);
    cout << "      ";
    gotoxy(llanta.x, llanta.y + 1);
    cout << "      ";
    gotoxy(llanta.x, llanta.y + 2);
    cout << "      ";
    gotoxy(llanta.x, llanta.y + 3);
    cout << "      ";
    gotoxy(llanta.x, llanta.y + 4);
    cout << "      ";
}

void inicializarLlanta(Llanta& llanta, int carrilOcupado = -1, int conoX = -1, int conoY = -1)
{
    int carriles[] = {16, 22, 29}; // Posiciones Y de los carriles
    int carril;
    do
    {
        carril = generarAleatorio(0, 2);
    }
    while (carril == carrilOcupado); // Asegurarse de que no sea el mismo carril que el cono

    do
    {
        llanta.x = generarAleatorio(80, 110); // Posición X aleatoria
    }
    while (llanta.x == conoX && carriles[carril] == conoY); // Asegurarse de que no coincidan las coordenadas

    llanta.y = carriles[carril]; // Aparece en uno de los carriles disponibles
    llanta.color = 8; // Color de la llanta
    llanta.activo = true; // Activar la llanta
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
    int numCochesEnemigos = 3 + (nivel - 1) * 2; // De 3 a 7 coches enemigos
    // int numCochesEnemigos = nivel * 3; // 3 coches en el nivel 1, 6 en el nivel 2, 9 en el nivel 3
    inicializarCochesEnemigos(numCochesEnemigos, nivel); // Inicializar los coches enemigos

    // Inicializar los coches aliados
    CocheAliado cocheReparacion;
    inicializarCocheAliado(cocheReparacion, 1);

    CocheAliado cocheEscudo;
    inicializarCocheAliado(cocheEscudo, 2);

    CocheAliado cocheVelocidad;
    inicializarCocheAliado(cocheVelocidad, 3);

    // Inicializar el cono
    Cono cono = {0, 0, 0, false}; // Inicializar la variable cono
    int tiempoAparicionCono = generarAleatorio(15, 20); // Tiempo de aparición del cono
    int duracionCono = 5; // Duración del cono en segundos

    // Inicializar la llanta
    Llanta llanta = {0, 0, 0, false}; // Inicializar la variable llanta
    int tiempoAparicionLlanta = generarAleatorio(17, 22); // Tiempo de aparición de la llanta
    int duracionLlanta = 6; // Duración de la llanta en segundos

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

    dibujarCochePrincipal(cochePrincipal); // Dibujar el coche principal

    // Dibujar los coches enemigos
    for (int i = 0; i < numCochesEnemigos; ++i)
    {
        dibujarCocheEnemigo(cochesEnemigos[i]);
    }

    // Variables para controlar el flujo del juego
    bool juegoActivo = true; // Indica si el juego está activo
    time_t tiempoInicio = time(0); // Tiempo de inicio del juego
    int tiempoAparicionReparacion = generarAleatorio(5, 9); // Tiempo de aparición del coche de reparación
    int tiempoAparicionEscudo = generarAleatorio(0, 4); // Tiempo de aparición del coche de escudo
    int tiempoAparicionVelocidad = generarAleatorio(9, 13); // Tiempo de aparición del coche de velocidad

    // Bucle principal del juego
    while (juegoActivo)
    {
        // Mostrar información del juego
        gotoxy(160, 5);
        color(15);
        mostrarVidas(vidas);

        // Mostrar el tiempo transcurrido
        time_t tiempoActual = time(0);
        int tiempoRestante = tiempoNivel - difftime(tiempoActual, tiempoInicio);
        mostrarTiempo(tiempoRestante);

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

        // Verificar si es el momento de activar el cono
        if (!cono.activo && tiempoRestante == tiempoNivel - tiempoAparicionCono)
        {
            inicializarCono(cono, llanta.activo ? llanta.y : -1, llanta.x, llanta.y);
            dibujarCono(cono);
        }

        // Verificar si es el momento de desactivar el cono
        if (cono.activo && tiempoRestante == tiempoNivel - tiempoAparicionCono - duracionCono)
        {
            borrarCono(cono);
            cono.activo = false;
        }

        // Verificar colisión con el coche principal
        if (cono.activo && cochePrincipal.x < cono.x + 9 &&
            cochePrincipal.x + 10 > cono.x &&
            cochePrincipal.y < cono.y + 4 &&
            cochePrincipal.y + 5 > cono.y)
        {
            borrarCoche(cochePrincipal); // Borrar el coche principal de su posición actual
            dibujarX(cochePrincipal.x, cochePrincipal.y); // Dibujar una X en la posición del coche principal
            vidas--; // Decrementar las vidas
            Sleep(1000);
            borrarX(cochePrincipal.x, cochePrincipal.y); // Borrar la X de la posición del coche principal
            dibujarCono(cono); // Redibujar el cono para asegurarse de que no se borre

            // Verificar si el jugador ha perdido
            if (vidas == 0)
            {
                juegoActivo = false;
                mostrarMensajePerdio();
                return;
            }
            else
            {
                // Reiniciar la posición del coche principal
                cochePrincipal.x = 0;
                cochePrincipal.y = centroY;
            }
        }

        // Verificar si es el momento de activar la llanta
        if (!llanta.activo && tiempoRestante == tiempoNivel - tiempoAparicionLlanta)
        {
            inicializarLlanta(llanta, cono.activo ? cono.y : -1, cono.x, cono.y);
            dibujarLlanta(llanta);
        }

        // Verificar si es el momento de desactivar la llanta
        if (llanta.activo && tiempoRestante == tiempoNivel - tiempoAparicionLlanta - duracionLlanta)
        {
            borrarLlanta(llanta);
            llanta.activo = false;
        }

        // Verificar colisión con el coche principal
        if (llanta.activo && cochePrincipal.x < llanta.x + 6 &&
            cochePrincipal.x + 10 > llanta.x &&
            cochePrincipal.y < llanta.y + 4 &&
            cochePrincipal.y + 5 > llanta.y)
        {
            borrarCoche(cochePrincipal); // Borrar el coche principal de su posición actual
            dibujarX(cochePrincipal.x, cochePrincipal.y); // Dibujar una X en la posición del coche principal
            vidas--; // Decrementar las vidas
            gotoxy(160, 7);
            cout << "Colision! Vidas restantes: " << vidas; // Mostrar un mensaje de colisión
            Sleep(1000);
            borrarX(cochePrincipal.x, cochePrincipal.y); // Borrar la X de la posición del coche principal
            dibujarLlanta(llanta); // Redibujar la llanta para asegurarse de que no se borre

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
                // Reiniciar la posición del coche principal
                cochePrincipal.x = 0;
                cochePrincipal.y = centroY;
            }
        }

        // Verificar colisión de la llanta con los coches enemigos
        for (int i = 0; i < numCochesEnemigos; ++i)
        {
            if (llanta.activo && cochesEnemigos[i].x < llanta.x + 6 &&
                cochesEnemigos[i].x + 10 > llanta.x &&
                cochesEnemigos[i].y < llanta.y + 4 &&
                cochesEnemigos[i].y + 5 > llanta.y)
            {
                borrarCoche(cochesEnemigos[i]); // Borrar el coche enemigo de su posición actual
                cochesEnemigos[i].x += 10; // Retroceder 10 espacios a la derecha
                dibujarLlanta(llanta); // Redibujar la llanta para asegurarse de que no se borre
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
            if (cono.activo && cochesEnemigos[i].x < cono.x + 10 &&
                cochesEnemigos[i].x + 10 > cono.x &&
                cochesEnemigos[i].y < cono.y + 5 &&
                cochesEnemigos[i].y + 5 > cono.y)
            {
                borrarCoche(cochesEnemigos[i]); // Borrar el coche enemigo de su posición actual
                cochesEnemigos[i].x += 10; // Retroceder 10 espacios a la derecha
                dibujarCono(cono); // Redibujar el cono para asegurarse de que no se borre
            }

            if (llanta.activo && cochesEnemigos[i].x < llanta.x + 6 &&
                cochesEnemigos[i].x + 10 > llanta.x &&
                cochesEnemigos[i].y < llanta.y + 4 &&
                cochesEnemigos[i].y + 5 > llanta.y)
            {
                borrarCoche(cochesEnemigos[i]); // Borrar el coche enemigo de su posición actual
                cochesEnemigos[i].x += 10; // Retroceder 10 espacios a la derecha
                dibujarLlanta(llanta); // Redibujar la llanta para asegurarse de que no se borre
            }

            borrarCoche(cochesEnemigos[i]); // Borrar el coche enemigo de su posición actual
            cochesEnemigos[i].x += cochesEnemigos[i].dx * cochesEnemigos[i].velocidad; // Mover el coche enemigo

            // Si el coche enemigo llega al extremo izquierdo, reiniciar su posición
            if (cochesEnemigos[i].x < 0)
            {
                cochesEnemigos[i].x = 140;
                cochesEnemigos[i].velocidad = generarAleatorio(1, 3);
                int coloresPermitidos[] = {1, 4, 5, 12, 13}; // Colores permitidos
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
                    cochesEnemigos[i].x = cochesEnemigos[j].x + 10;
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
                Sleep(1000);
                borrarX(cochePrincipal.x, cochePrincipal.y); // Borrar la X de la posición del coche principal

                // Verificar si el jugador ha perdido
                if (vidas == 0)
                {
                    juegoActivo = false;
                    system("cls"); // Clear the screen
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

            dibujarCocheEnemigo(cochesEnemigos[i]); // Dibujar el coche enemigo en la nueva posición
        }

        dibujarCochePrincipal(cochePrincipal); // Dibujar el coche principal
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
