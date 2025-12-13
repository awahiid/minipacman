#ifndef BOX_H
#define BOX_H

#define PACMAN 'C'
#define GHOST 'O'
#define EXIT ' '
#define WALL 'H'
#define PATH '.'

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define SIZE 10

/**
 * @brief Estructura que representa una casilla en el tablero.
 */
struct box
{
    char type;     /**< Tipo de la casilla (Pacman, Fantasma, Pared, Salida, etc.). */
    int x;         /**< Coordenada X de la casilla en el tablero. */
    int y;         /**< Coordenada Y de la casilla en el tablero. */
    int direction; // las direciones son 0=Derecha, 1=Abajo, 2=Izquierda, 3=Arriba

    double distanceToExit; /**< Distancia de la casilla al punto de salida en el tablero. */
    bool isVisited;        /**< Indica si la casilla ha sido visitada durante un recorrido en el tablero. */
};

typedef struct box Box;

/**
 * @brief Crea una casilla con las coordenadas especificadas y el tipo dado.
 *
 * @param box Puntero a la casilla que se va a crear.
 * @param x Coordenada X de la casilla.
 * @param y Coordenada Y de la casilla.
 * @param type Tipo de la casilla ('P' para Pacman, 'F' para Fantasma, 'M' para Muro, 'S' para Salida, cualquier otro para Camino).
 */
void createBox(Box *box, int x, int y, char type);

/**
 * @brief Formatea el tipo de casilla según el tipo de entrada.
 *
 * @param type Tipo de casilla a formatear.
 * @return Carácter que representa el tipo formateado ('P' para Pacman, 'F' para Fantasma, 'M' para Muro, 'S' para Salida, ' ' para Camino).
 */
char formatType(char type);

/**
 * @brief Mueve una casilla a las coordenadas especificadas.
 *
 * @param box Puntero a la casilla que se va a mover.
 * @param x Nueva coordenada X de la casilla.
 * @param y Nueva coordenada Y de la casilla.
 */
void move(Box *box, int x, int y);

/**
 * @brief Verifica si una casilla está dentro de los límites del tablero.
 *
 * @param box Puntero a la casilla que se verifica.
 * @return Verdadero si la casilla está dentro de los límites del tablero, falso en caso contrario.
 */
bool isInRange(Box *box);

/**
 * @brief Verifica si se puede visitar una casilla (no visitada, no es un muro y está dentro de los límites del tablero).
 *
 * @param box Puntero a la casilla que se verifica.
 * @return Verdadero si se puede visitar la casilla, falso en caso contrario.
 */
bool canVisit(Box *box);

/**
 * @brief Marca una casilla como visitada y cambia su color a verde.
 *
 * @param box Puntero a la casilla que se va a marcar como visitada.
 */
void visit(Box *box);

/**
 * @brief Calcula la distancia euclidiana entre dos puntos en el tablero.
 *
 * @param start_x Coordenada X del punto de inicio.
 * @param start_y Coordenada Y del punto de inicio.
 * @param end_x Coordenada X del punto de llegada.
 * @param end_y Coordenada Y del punto de llegada.
 * @return La distancia euclidiana entre los dos puntos.
 */
double calculateDistance(int start_x, int start_y, int end_x, int end_y);

/**
 * @brief Verifica si un fantasma puede visitar la casilla (no es un muro, no es una salida y está dentro de los límites del tablero).
 *
 * @param box Puntero a la casilla que se verifica.
 * @return Verdadero si el fantasma puede visitar la casilla, falso en caso contrario.
 */
bool ghostCanVisit(Box *box);

void interchangeBoxes(Box *box1, Box *box2);

#endif