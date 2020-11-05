#ifndef BOARD_CPP
#define BOARD_CPP
#include "Board.h"

Board *Board::goalBoard = nullptr;

Board::Board(int **board, int n, MOVE mv) : board(board), n(n), moveFromLastState(mv)
{
}

std::string Board::toString()
{
    std::string result("");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result.append(std::to_string(board[i][j])).append(" ");
        }
        result.append("\n");
    }

    return result;
}
int Board::tileAt(int row, int col)
{
    return board[row][col];
}
int Board::size()
{
    return n;
}
int Board::manhattan()
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum += calculateDistance(i, j);
        }
    }

    return sum;
}

int Board::calculateDistance(int i, int j)
{
    int block = board[i][j];
    std::pair<int, int> indexOfBlockInGoal = getIndexOfBlock(block, true);

    return (block == EMPTY_SPACE) ? 0 : abs(i - indexOfBlockInGoal.first) + abs(j - indexOfBlockInGoal.second);
}

std::pair<int, int> Board::getIndexOfBlock(int block, bool inGoal)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inGoal ? goalBoard->board[i][j] == block : board[i][j] == block)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool Board::isGoal()
{
    return *this == *goalBoard;
}

bool Board::operator==(const Board &other)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (other.board[i][j] != board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<Board *> Board::getNeighbors()
{
    if (neighbours.size() == 0)
    {
        std::pair<int, int> spaceLocation = getIndexOfBlock(EMPTY_SPACE, false);
        int spaceRow = spaceLocation.first, spaceCol = spaceLocation.second;

        if (spaceRow > 0)
            neighbours.push_back(new Board(swap(spaceRow, spaceCol, spaceRow - 1, spaceCol), n, MOVE::UP));
        if (spaceRow < size() - 1)
            neighbours.push_back(new Board(swap(spaceRow, spaceCol, spaceRow + 1, spaceCol), n, MOVE::DOWN));
        if (spaceCol > 0)
            neighbours.push_back(new Board(swap(spaceRow, spaceCol, spaceRow, spaceCol - 1), n, MOVE::LEFT));
        if (spaceCol < size() - 1)
            neighbours.push_back(new Board(swap(spaceRow, spaceCol, spaceRow, spaceCol + 1), n, MOVE::RIGHT));
    }

    return neighbours;
}

int **Board::swap(int row1, int col1, int row2, int col2)
{
    int **copy = this->copy();
    int tmp = copy[row1][col1];
    copy[row1][col1] = copy[row2][col2];
    copy[row2][col2] = tmp;

    return copy;
}

std::string Board::getMove()
{
    std::string result;
    switch (moveFromLastState)
    {
    case UP:
        return "UP";

    case DOWN:
        return "DOWN";

    case RIGHT:
        return "RIGHT";

    case LEFT:
        return "LEFT";

    default:
        break;
    }
    return "";
}

int **Board::copy()
{
    int **copy = new int *[n];
    for (int i = 0; i < n; i++)
    {
        copy[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            copy[i][j] = board[i][j];
        }
    }
    return copy;
}

Board *Board::twin()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
            if (board[i][j] != EMPTY_SPACE && board[i][j + 1] != EMPTY_SPACE)
            {
                return new Board(swap(i, j, i, j + 1), n);
            }
    }
    return nullptr;
}

// Board();
Board::~Board()
{
    for (int i = 0; i < n; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

#endif