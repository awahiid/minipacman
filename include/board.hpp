#ifndef BOARD_H
#define BOARD_H

#define TIME 300000

#include <unistd.h>
#include <algorithm> // ChatGPT para ordenar
#include <utility>   // ChatGPT para ordenar
#include "box.hpp"

#define SIZE 10

/**
 * @brief Estructura que representa el tablero del juego.
 */
struct board
{
    int height = SIZE; /**< Altura del tablero. */
    int width = SIZE;  /**< Ancho del tablero. */

    Box *pacman; /**< Puntero al objeto Pacman. */
    Box *ghost;  /**< Puntero al objeto Fantasma. */
    Box *exit;   /**< Puntero al objeto Salida. */

    Box *layout[SIZE][SIZE]; /**< Matriz que representa el diseño del tablero. */

    bool isLoaded; /**< Indica si el tablero ha sido cargado. */
    bool isEndGame; /**< Indica si el fantasma se ha comido al pacman. */
    bool isGameWin; /**< Indica si el pacman ha llegado a la salida*/

    vector<char> pacman_movement; /**< Vector que contiene los movimientos del pacman en el tablero. */
    vector<char> ghost_movement;  /**< Vector que contiene los movimientos del fantasma en el tablero. */
    int nodes;    /**< Cantidad de nodos generados al resolver el tablero. */
};

typedef struct board Board;

void load(Board *board, FILE *file);

/**
 * @brief Agrega una casilla a la solución del tablero.
 *
 * @param board Puntero al tablero al que se agrega la casilla.
 * @param box Puntero a la casilla que se agrega a la solución.
 */
void addBoxToPacmanMovements(Board *board, Box *box);

/**
 * @brief Agrega una casilla a la solución del tablero.
 *
 * @param board Puntero al tablero al que se agrega la casilla.
 * @param box Puntero a la casilla que se agrega a la solución.
 */
void addBoxToGhostMovements(Board *board, Box *box);

/**
 * @brief Muestra como ha finalizado el juego y el movimiento del Pacman.
 *
 * @param board Puntero al tablero que contiene el movimiento del pacman a mostrar.
 */
void showPacmanMovements(Board *board);

/**
 * @brief Muestra el movimiento del fantasma.
 *
 * @param board Puntero al tablero que contiene el movimiento del fantasma a mostrar.
 */
void showGhostMovements(Board *board);

/**
 * @brief Mueve el fantasma en el tablero.
 *
 * @param board Puntero al tablero en el que se mueve el fantasma.
 */
void moveGhost(Board *board);

/**
 * @brief Mueve el fantasma aleatoriamente en el tablero.
 *
 * @param board Puntero al tablero en el que se mueve el fantasma.
 */
void moveGhostRandom(Board *board);

/**
 * @brief Obtiene las casillas adyacentes a una casilla dada en el tablero.
 *
 * @param board Puntero al tablero en el que se busca.
 * @param box Puntero a la casilla para la que se obtienen las casillas adyacentes.
 * @return Un vector de punteros a las casillas adyacentes.
 */
vector<Box *> getAdjBoxes(Board *board, Box *box);

/**
 * @brief Calcula las distancias de todas las casillas al punto de salida en el tablero.
 *
 * @param board Puntero al tablero en el que se realizan los cálculos.
 */
void calculateDistancesToExit(Board *board);

/**
 * @brief Carga el contenido del archivo en el tablero proporcionado.
 *
 * @param board Puntero al tablero en el que se carga el contenido del archivo.
 * @param file Puntero al archivo que contiene el diseño del tablero.
 */
void load(Board *board, FILE *file);

/**
 * @brief Muestra información sobre las casillas importantes en el tablero, como la posición del Pacman, el Fantasma y la Salida.
 *
 * @param board Puntero al tablero del que se muestra la información.
 */
void showInfo(Board *board);

/**
 * @brief Compara dos casillas según su distancia al punto de salida.
 *
 * @param a Puntero a la primera casilla a comparar.
 * @param b Puntero a la segunda casilla a comparar.
 * @return Verdadero si la distancia de la primera casilla al punto de salida es menor que la de la segunda casilla, falso en caso contrario.
 */
bool compareByDistance(const Box *a, const Box *b);

/**
 * @brief Ordena un vector de casillas según sus distancias al punto de salida en el tablero.
 *
 * @param board Puntero al tablero en el que se encuentran las casillas.
 * @param boxes Vector de punteros a las casillas que se ordenarán.
 */
void sortByDistanceToExit(Board *board, vector<Box *> &boxes);

/**
 * @brief Resuelve el tablero moviendo al Pacman hacia la salida con un algoritmo de escalada simple.
 *
 * @param board Puntero al tablero que se va a resolver.
 */
void hillClimbing(Board *board);

/**
 * @brief Resuelve el tablero moviendo al Pacman hacia la salida con un algoritmo de máxima pendiente de forma recursiva.
 *
 * @param board Puntero al tablero que se va a resolver.
 */
void maximumSlopeR(Board *board);

/**
 * @brief Resuelve el tablero moviendo al Pacman hacia la salida con un algoritmo de máxima pendiente de forma iterativa.
 *
 * @param board Puntero al tablero que se va a resolver.
 */
void maximumSlopeI(Board *board);

/**
 * @brief Resuelve el tablero moviendo al Pacman hacia la salida con un algoritmo de seleccion en anchura que mueve el pacman siempre que se puede priorizando 
 * las casillas mas cercanas.
 *
 * @param board Puntero al tablero que se va a resolver.
 */
void greedy(Board * board);

/**
 * @brief Resuelve el tablero moviendo al Pacman hacia la salida con un algoritmo que mueve el pacman siempre que se pueda de forma aleatoria.
 *
 * @param board Puntero al tablero que se va a resolver.
 */
void solveRandom(Board *board);


#endif
