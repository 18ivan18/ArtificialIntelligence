#ifndef BOARD
#define BOARD
#include "Enums.cpp"

class Board
{
private:
    int size, indexOfEmpty;
    TILE *board;

public:
    Board(TILE *, int, int);
    bool operator==(const Board &);
    int getIndexOfEmpty() const;
    int getSize() const;
    TILE *getBoard() const;
    ~Board();
};
#endif
