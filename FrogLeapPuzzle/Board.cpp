#include "Board.h"

int Board::getIndexOfEmpty() const
{
    return indexOfEmpty;
}

int Board::getSize() const
{
    return size;
}

TILE *Board::getBoard() const
{
    return board;
}

Board::Board(TILE *arr, int size, int indexOfEmpty) : size(size), board(arr), indexOfEmpty(indexOfEmpty)
{
}

Board::~Board()
{
    delete[] board;
}

bool Board::operator==(const Board &other)
{
    if (size != other.size)
    {
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (board[i] != other.board[i])
        {
            return false;
        }
    }
    return true;
}