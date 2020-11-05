#ifndef BOARD
#define BOARD
#include <string>
#include <vector>

class Board
{
private:
    static const int EMPTY_SPACE = 0;
    enum MOVE
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NO_MOVE
    };
    int n;
    int **board;
    std::vector<Board *> neighbours;
    int calculateDistance(int, int);
    std::pair<int, int> getIndexOfBlock(int, bool);
    int **copy();
    int **swap(int, int, int, int);
    MOVE moveFromLastState;

public:
    Board(int **tiles, int, MOVE mv = NO_MOVE); // create a board from an n-by-n array of tiles,
                                                // where tiles[row][col] = tile at (row, col)
    std::string toString();                     // string representation of this board
    int tileAt(int row, int col);               // tile at (row, col) or 0 if blank
    int size();                                 // board size n
    int manhattan();                            // sum of Manhattan distances between tiles and goal
    bool isGoal();                              // is this board the goal board?
    bool operator==(const Board &);             // does this board equal y?
    std::vector<Board *> getNeighbors();        // all neighboring boards
    Board *twin();
    static Board *goalBoard;
    std::string getMove();
    ~Board();
};

#endif
