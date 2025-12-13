#include "../include/box.hpp"

void createBox(Box *box, int x, int y, char type)
{

    box->x = x;
    box->y = y;
    box->type = type;
    box->direction = 0;
}

char formatType(char type)
{
    if (type == 'P')
        return PACMAN;
    else if (type == 'F')
        return GHOST;
    else if (type == 'M')
        return WALL;
    else if (type == 'S')
        return EXIT;
    else
        return PATH;
}

void move(Box *box, int x, int y)
{
    box->x = x;
    box->y = y;
}

bool isInRange(Box *box)
{
    int x = box->x;
    int y = box->y;
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool canVisit(Box *box)
{
    return !box->isVisited && box->type != WALL && isInRange(box);
}

void visit(Box *box)
{
    box->isVisited = true;
}

double calculateDistance(int start_x, int start_y, int end_x, int end_y)
{
    return sqrt((pow((end_x - start_x), 2) + pow((end_y - start_y), 2)));
}

bool ghostCanVisit(Box *box)
{
    return box->type != WALL && box->type != EXIT && isInRange(box);
}

void interchangeBoxes(Box *box1, Box *box2)
{
    int x1 = box1->x;
    int y1 = box1->y;
    box1->x = box2->x;
    box1->y = box2->y;
    box2->x = x1;
    box2->y = y1;
    int distanceToExit1 = box1->distanceToExit;
    box1->distanceToExit = box2->distanceToExit;
    box2->distanceToExit = box1->distanceToExit;
}