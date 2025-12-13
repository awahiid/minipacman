#include "../include/board.hpp"
#include <random>

void addBoxToPacmanMovements(Board *board, Box *box) {
    char movement = (box->x < board->pacman->x) ? 'R' :
                    (box->y < board->pacman->y) ? 'D' :
                    (box->y > board->pacman->y) ? 'U' :
                    'L';
    board->pacman_movement.push_back(movement);
}


void addBoxToGhostMovements(Board *board, Box *box)
{

    char movement;
    Box *ghost = board->ghost;
    if (box->x < ghost->x)
    {
        movement = 'R';
    }
    else if (box->y < ghost->y)
    {
        movement = 'D';
    }
    else if (box->y > ghost->y)
    {
        movement = 'U';
    }
    else if (box->x > ghost->x)
    {
        movement = 'L';
    }

    board->ghost_movement.push_back(movement);
}

void showPacmanMovements(Board *board)
{
    if (board->isLoaded /*&& board->pacman_movement.size() > 0*/)
    {

        if (board->isGameWin)
        {
            cout << "   El pacman ha llegado a la salida" << endl;
        }
        else if (board->isEndGame)
        {
            cout << "   El fantasma se ha comido al pacman" << endl;
        }
        else
        {
            cout << "   El pacman se ha quedado atascado" << endl;
        }

        cout << "   PACMAN: ";

        for (size_t i = 0; i < board->pacman_movement.size(); ++i)
        {
            cout << board->pacman_movement[i];
            if (i != board->pacman_movement.size() - 1)
            {
                cout << "-";
            }
        }

        cout << endl;
    }
}

void showGhostMovements(Board *board)
{
    if (board->isLoaded /*&& board->pacman_movement.size() > 0*/)
    {

        cout << "   FANTASMA: ";

        for (size_t i = 0; i < board->ghost_movement.size(); ++i)
        {
            cout << board->ghost_movement[i];
            if (i != board->ghost_movement.size() - 1)
            {
                cout << "-";
            }
        }

        cout << endl;
    }
}

void moveGhost(Board *board)
{
    Box *ghost = board->ghost;
    int gx = ghost->x;
    int gy = ghost->y;
    int dir = ghost->direction;
    // Direcciones en orden: Derecha, Abajo, Izquierda, Arriba
    const pair<int, int> directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    const char movements[4] = {'R', 'D', 'L', 'U'};
    // las direciones son 0=Derecha, 1=Abajo, 2=Izquierda, 3=Arriba
    int i = 0;
    while (i < 4)
    {
        int new_x = gx + directions[dir].second;
        int new_y = gy + directions[dir].first;

        // Verificar si la nueva posición es válida y visitable
        if (ghostCanVisit(board->layout[new_y][new_x]))
        {

            interchangeBoxes(ghost, board->layout[new_y][new_x]);
            board->layout[gy][gx] = board->layout[new_y][new_x];
            board->layout[new_y][new_x] = ghost;

            if (board->layout[gy][gx] == board->pacman)
            {
                board->layout[gy][gx]->type = PATH;
                board->isEndGame = true;
            }

            board->ghost_movement.push_back(movements[ghost->direction]);

            return;
        }

        // Cambiar de dirección si no se puede mover en la dirección actual
        dir = (ghost->direction + 1) % 4;
        ghost->direction = dir;
        i++;
    }
}

vector<Box *> getAdjBoxes(Board *board, Box *box)
{
    vector<Box *> adjBoxes;
    if (box->type != WALL)
    {
        int x, y;
        x = box->x;
        y = box->y;
        adjBoxes.push_back(board->layout[y - 1][x]);
        adjBoxes.push_back(board->layout[y][x + 1]);
        adjBoxes.push_back(board->layout[y + 1][x]);
        adjBoxes.push_back(board->layout[y][x - 1]);
    }
    return adjBoxes;
}

void calculateDistancesToExit(Board *board)
{
    Box *box, *exit;
    exit = board->exit;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            box = board->layout[i][j];
            box->distanceToExit = calculateDistance(box->x, box->y, exit->x, exit->y);
        }
    }
}

void load(Board *board, FILE *file)
{
    if (file != NULL)
    {
        char type;
        int i = 0;
        int j = 0;
        while ((type = fgetc(file)) != EOF)
        {
            if (type == '\n')
            {
                i++;
                j = 0;
            }
            else if (type != ',')
            {

                board->layout[i][j] = new Box;
                createBox(board->layout[i][j], j, i, formatType(type));

                if (type == 'P')
                {
                    board->pacman = board->layout[i][j];
                }
                else if (type == 'F')
                {
                    board->ghost = board->layout[i][j];
                }
                else if (type == 'S')
                {
                    board->exit = board->layout[i][j];
                }

                j++;
            }
        }
        board->isLoaded = true;
        board->isGameWin = false;
        board->isEndGame = false;
        board->nodes = 0;
    }
    else
    {
        printf("Error al cargar tablero: Parece que el fichero no se ha abierto correctamente.\n");
    }
}

void showInfo(Board *board)
{
    if (board->isLoaded)
    {

        printf("Pacman (x,y): %i,%i\n", board->pacman->x, board->pacman->y);
        printf("Fantasma (x,y): %i, %i\n", board->ghost->x, board->ghost->y);
        printf("Salida (x,y): %i, %i\n", board->exit->x, board->exit->y);
    }
    else
    {
        printf("Error al obtener la información del tablero: Parece que el tablero no está cargado\n");
    }
}

//Inicio ChatGPT
bool compareByDistance(const Box *a, const Box *b)
{
    return a->distanceToExit < b->distanceToExit;
}

void sortByDistanceToExit(Board *board, vector<Box *> &boxes)
{
    for(Box * box : boxes){
        box->distanceToExit = calculateDistance(board->exit->x, board->exit->y, box->x, box->y);
    }
    sort(boxes.begin(), boxes.end(), compareByDistance);
}
//Fin ChatGPT

bool movePacman(Board *board, int x, int y)
{

    Box *pacman = board->pacman;
    Box *newPos = board->layout[y][x];

    if (newPos->type != GHOST && canVisit(newPos))
    {

        board->isGameWin = newPos == board->exit;

        board->layout[pacman->y][pacman->x] = newPos;
        visit(newPos);
        board->layout[y][x] = pacman;
        interchangeBoxes(pacman, newPos);
        return true;
    }

    return false;
}

void hillClimbing(Board *board)
{

    moveGhost(board); // Mueve al fantasma con inercia

    // Si el fantasma se ha comido al pacman ha terminado el juego
    if (board->isEndGame)
        return;

    Box *pacman = board->pacman;
    Box *exit = board->exit;

    // Definir las direcciones posibles: derecha (0), abajo (1), izquierda (2), arriba (3)
    const pair<int, int> directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    Box *adjBox;
    bool isNear;
    int direction = 0;
    int newX;
    int newY;

    // Mover el pacman a la primera casilla que se pueda del conjunto de adyacentes y añadir ese paso a la solucion
    while (direction < 4)
    {   
        newX = pacman->x + directions[direction].second;
        newY = pacman->y + directions[direction].first;

        adjBox = board->layout[newY][newX];
        isNear = calculateDistance(exit->x, exit->y, adjBox->x, adjBox->y) <= calculateDistance(exit->x, exit->y, pacman->x, pacman->y);
        board->nodes++;
        if (isNear && movePacman(board, adjBox->x, adjBox->y))
        {
            addBoxToPacmanMovements(board, adjBox);
            // Si el pacman está en la salida termina
            if (board->isGameWin)
                return;
            hillClimbing(board);
            return;
        }

        direction++;
    }
}

void maximumSlopeR(Board *board)
{

    moveGhost(board); // Mueve al fantasma con inercia

    // Si el fantasma se ha comido al pacman ha terminado el juego
    if (board->isEndGame)
        return;

    Box *pacman = board->pacman;
    Box *exit = board->exit;

    // Obtener las casillas adyacentes
    vector<Box *> adjBoxes = getAdjBoxes(board, pacman);
    sortByDistanceToExit(board, adjBoxes);
    board->nodes+=4;

    Box *adjBox;
    bool isNear;

    // Mover el pacman a la primera casilla que se pueda del conjunto de adyacentes y añadir ese paso a la solucion
    while (adjBoxes.size() > 0)
    {   
        adjBox = adjBoxes.front();
        adjBoxes.erase(adjBoxes.begin());
        isNear = calculateDistance(exit->x, exit->y, adjBox->x, adjBox->y) < calculateDistance(exit->x, exit->y, pacman->x, pacman->y);

        if (isNear && movePacman(board, adjBox->x, adjBox->y))
        {
            addBoxToPacmanMovements(board, adjBox);
            // Si el pacman está en la salida termina
            if (board->isGameWin)
                return;
            maximumSlopeR(board);
            return;
        }
    }
}

void greedy(Board *board)
{

    moveGhost(board); // Mueve al fantasma con inercia

    // Si el fantasma se ha comido al pacman ha terminado el juego
    if (board->isEndGame){
        return;
    }

    Box *pacman = board->pacman;

    // Obtener las casillas adyacentes
    vector<Box *> adjBoxes = getAdjBoxes(board, pacman);
    sortByDistanceToExit(board, adjBoxes);
    board->nodes+=4;
    Box *adjBox;

    // Mover el pacman a la primera casilla que se pueda del conjunto de adyacentes y añadir ese paso a la solucion
    while (adjBoxes.size() > 0)
    {   
        adjBox = adjBoxes.front();
        adjBoxes.erase(adjBoxes.begin());

        if (movePacman(board, adjBox->x, adjBox->y))
        {
            addBoxToPacmanMovements(board, adjBox);
            // Si el pacman está en la salida termina
            if (board->isGameWin){
                return;
            }
            greedy(board);
            return;
        }
    }
}

void ordenarAleatoriamente(vector<Box *> &boxes)
{
    // Crear un motor de números aleatorios utilizando una semilla aleatoria
    random_device rd;
    default_random_engine rng(rd());

    // Usar shuffle para ordenar el vector de forma aleatoria
    shuffle(boxes.begin(), boxes.end(), rng);
}

bool isEndGame(Board *board)
{
    int gx = board->ghost->x;
    int gy = board->ghost->y;
    int px = board->pacman->x;
    int py = board->pacman->y;

    return gx == px && gy == py;
}

void solveRandom(Board *board)
{

    moveGhost(board); // Mueve al fantasma aleatoriamente

    // Si el fantasma se ha comido al pacman ha terminado el juego
    if (board->isEndGame)
        return;

    Box *pacman = board->pacman;
    Box *exit = board->exit;

    // Obtener las casillas adyacentes
    vector<Box *> adjBoxes = getAdjBoxes(board, pacman);
    board->nodes+=4;
    ordenarAleatoriamente(adjBoxes);
    Box *adjBox;

    // Mover el pacman a la primera casilla que se pueda del conjunto de adyacentes y añadir ese paso a la solucion
    while (adjBoxes.size() > 0)
    {
        adjBox = adjBoxes.front();        // Obtenemos la primera casilla del conjunto
        adjBoxes.erase(adjBoxes.begin()); // La eliminamos del conjunto

        if (movePacman(board, adjBox->x, adjBox->y))
        {
            addBoxToPacmanMovements(board, adjBox);
            if (board->isGameWin)
                return;
            solveRandom(board);
            return;
        }
    }
}

// Esta solucion implementa escalada Maxima Pendiente
void maximumSlopeI(Board *board)
{
    Box *pacman = board->pacman;
    Box *exit = board->exit;
    bool movido, puedeMover = true;
    double distancia, distanciaMenor = calculateDistance(pacman->x, pacman->y, exit->x, exit->y);
    int i = 100;
    while (i > 0 && puedeMover)
    {
        movido = false;
        moveGhost(board); // Mueve al fantasma con inercia

        // Si el fantasma se ha comido al pacman ha terminado el juego
        if (board->isEndGame)
            return;

        // Obtener las casillas adyacentes y ordenarlas por distancia a la salida
        vector<Box *> adjBoxes = getAdjBoxes(board, pacman);
        vector<Box *> adjBoxesNodos = getAdjBoxes(board, pacman);
        sortByDistanceToExit(board, adjBoxes);
        Box *adjBox;
        while (adjBoxesNodos.size() > 0)
        {
            adjBox = adjBoxesNodos.front();             // Obtenemos la primera casilla del conjunto
            adjBoxesNodos.erase(adjBoxesNodos.begin()); // La eliminamos del conjunto
            if (!adjBox->isVisited && adjBox->type != WALL)
            {
                board->nodes++;
            }
        }

        // Mover el pacman a la primera casilla que se pueda del conjunto de adyacentes y añadir ese paso a la solucion
        while (adjBoxes.size() > 0 && !movido)
        {
            adjBox = adjBoxes.front();        // Obtenemos la primera casilla del conjunto
            adjBoxes.erase(adjBoxes.begin()); // La eliminamos del conjunto
            distancia = adjBox->distanceToExit;
            if (distancia < distanciaMenor)
            {
                if (movePacman(board, adjBox->x, adjBox->y))
                {
                    movido = true;
                    addBoxToPacmanMovements(board, adjBox);

                    if (board->isGameWin)
                    {
                        return;
                    }
                }
            }
        }
        if (!movido)
        {
            puedeMover = false;
        }

        i--;
    }
}
