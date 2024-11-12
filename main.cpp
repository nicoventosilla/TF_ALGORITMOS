#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>

using namespace std;

// Constantes
const char CUBO = 219;
const int COLOR_FONDO = 10;
const int COLOR_COCHE_PRINCIPAL = 10;
const int COLOR_COCHE_ENEMIGO = 12;
const int ANCHO = 100;
const int ALTO = 40;

// Estructura para los coches
struct Coche
{
    int x, y; // Posición del coche
    int dx, dy; // Dirección del movimiento
    int color; // Color del coche
    int velocidad; // Velocidad del coche
};

// Funciones de utilidades

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

// Funciones de dibujo

// Dibuja el escenario del juego con tres rectángulos horizontales
void dibujarEscenario()
{
    ocultarCursor();

    // Primer rectángulo (verde claro)
    color(COLOR_FONDO);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 150; j++)
        {
            cout << CUBO;
        }
    }

    // Segundo rectángulo (negro) con líneas horizontales de pistas de 3 carriles
    color(0);
    for (int i = 15; i < 35; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 150; j++)
        {
            cout << CUBO;
        }
    }

    // Tercer rectángulo (verde claro)
    color(COLOR_FONDO);
    for (int i = 35; i < 50; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 150; j++)
        {
            cout << CUBO;
        }
    }
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


// Funciones de lógica del juego

// Mueve un coche según la entrada del usuario
void moverCoche(Coche& coche)
{
    if (_kbhit())
    {
        char tecla = _getch();
        if (tecla == 27) exit(0);
        else if (tecla == 72)
        {
            coche.dx = 0;
            coche.dy = -1;
        }
        else if (tecla == 80)
        {
            coche.dx = 0;
            coche.dy = 1;
        }
        else if (tecla == 77)
        {
            coche.dx = 1;
            coche.dy = 0;
        }
        else if (tecla == 75)
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

    dibujarCoche(coche);
}

// Función principal del juego
void juego()
{
    system("cls");

    // Inicializa los coches
    int centroY = 15 + (35 - 15) / 2 - 2; // Calcula el centro vertical del rectángulo negro
    Coche cochePrincipal = {0, centroY, 0, 0, COLOR_COCHE_PRINCIPAL, 1}; // Posición inicial en el centro vertical del rectángulo negro, alineado a la izquierda
    int centroX = 150 - 10; // Calcula la posición horizontal cerca del borde derecho del rectángulo negro
    Coche cocheEnemigo = {centroX, centroY, -1, 0, COLOR_COCHE_ENEMIGO, 1}; // Posición inicial en el centro vertical del rectángulo negro, alineado a la derecha

    ocultarCursor();
    dibujarEscenario();
    dibujarCoche(cochePrincipal);
    dibujarCoche(cocheEnemigo);

    // Bucle principal del juego
    while (true)
    {
        moverCoche(cochePrincipal);
        borrarCoche(cocheEnemigo);
        cocheEnemigo.x += cocheEnemigo.dx * cocheEnemigo.velocidad;
        if (cocheEnemigo.x < 0) cocheEnemigo.x = 140; // Reinicia la posición del coche enemigo cuando sale del rectángulo negro
        dibujarCoche(cochePrincipal);
        dibujarCoche(cocheEnemigo);
        Sleep(30);
    }
}

// Funciones de interfaz

// Muestra las instrucciones del juego
void instrucciones()
{
    system("cls");
    cout << "-------------------";
    cout << "Instrucciones";
    cout << "-------------------" << endl;
    cout << "\"Aqui van las instrucciones\"" << endl;
    esperarTecla();
}

// Muestra los créditos del juego
void creditos()
{
    system("cls");
    cout << "-------------------";
    cout << "Creditos";
    cout << "-------------------" << endl;
    cout << "\"Aqui van las instrucciones\"" << endl;
    esperarTecla();
}

// Muestra un mensaje de despedida y sale del juego
void salir()
{
    system("cls");
    cout << "Gracias por jugar!" << endl;
}

// Función principal
int main()
{
    ocultarCursor();
    while (true)
    {
        system("cls");
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
            juego();
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
