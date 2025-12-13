/* Inteligencia Artificial y Sistemas Inteligentes
   Escuela Politécnica. Universidad de Extremadura.

   Autores:
    - Abdel Wahed Mahfoud Mouhandizi
*/

#include <iostream>
#include "../include/board.hpp"
#include <time.h>
#include <limits>
#include <iomanip> // Para std::fixed y std::setprecision

using namespace std;

/*
    Selecciona un tablero de los ejemplos disponibles.

    Rutas a directorios
*/
void selectFile(FILE *&file)
{
    int file_number;
    cout << "¿Qué fichero quieres cargar?" << endl;
    cin >> file_number;

    string filename = "../layouts/MINIPAC" + to_string(file_number) + ".txt";
    file = fopen(filename.c_str(), "r");

    if (file == nullptr)
    {
        cerr << "Error al abrir el fichero " << filename << endl;
    }
}

void openMap(FILE *&file, int map_num)
{
    string filename = "layouts/MINIPAC" + to_string(map_num) + ".txt";
    file = fopen(filename.c_str(), "r");
    if (file == nullptr)
    {
        cerr << "Error al abrir el fichero " << filename << endl;
    }
}

void solveAllMaps(Board *board, FILE *&file, int solution)
{

    for (int i = 1; i <= 10; i++)
    {
        cout << "----------------------------------------------" << endl;
        cout << "MAPA " << i << endl;
        openMap(file, i);
        load(board, file);

        clock_t inicio, fin;
        double tiempo;

        switch (solution)
        {
        case 1:
            inicio = clock();
            hillClimbing(board);
            fin = clock();
            break;
        case 2:
            inicio = clock();
            maximumSlopeR(board);
            fin = clock();
            break;
        case 3:
            inicio = clock();
            solveRandom(board);
            fin = clock();
            break;
        case 4:
            inicio = clock();
            maximumSlopeI(board);
            fin = clock();
            break;
        case 5:
            inicio = clock();
            greedy(board);
            fin = clock();
        break;
        default:
            cerr << "Error en la selección" << endl;
            return;
        }

        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        showPacmanMovements(board);
        showGhostMovements(board);

        cout << "   Nodos generados: " << board->nodes << endl;
        cout << "   Tiempo de ejecución: " << fixed << setprecision(6) << tiempo << " segundos." << endl;

        fclose(file);
        delete(board);
        board = new Board;
    }
}

void showMenu(Board *board, FILE *&file)
{

    int selection;

    while (selection > 5 || selection < 1)
    {
        cin.clear();
        cout << "Selecciona una solución: " << endl;
        cout << "1 - Solución por escalada simple." << endl;
        cout << "2 - Solución por máxima pendiente (Recursivo)." << endl;
        cout << "3 - Solución con movimientos aleatorios. " << endl;
        cout << "4 - Solución por máxima pendiente (Iterativo)." << endl;
        cout << "5 - Solución en anchura modificada (Se mueve a otra casilla siempre que se pueda priorizando las cercanas)." << endl;
        
        cin >> selection;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    solveAllMaps(board, file, selection);
}

int main()
{
    Board *board = new Board;
    FILE *file;

    showMenu(board, file);
    delete board;

    return 0;
}
