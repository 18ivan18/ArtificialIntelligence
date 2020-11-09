#include "Board.h"
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <cmath>
#include <iostream>
#include <algorithm>

Board::Board(int n)
{
    this->n = n;
    q = new int[n];
    queensInRow = new int[n];
    queensInSecondaryDiags = new int[2 * n - 1];
    queensInMainDiags = new int[2 * n - 1];
    srand(time(NULL));
    shuffle();
}

template <typename T>
void Board::swap(T &first, T &second)
{
    T temp = first;
    first = second;
    second = temp;
}

void Board::randomShuffle(int *arr, int n, int (*gen)(int))
{
    for (int i = n - 1; i > 0; --i)
    {
        swap(arr[i], arr[gen(i + 1)]);
    }
}

// Randomly fills the board with one queen in each column. Optimizes on the first iteration
void Board::shuffle()
{
    for (int i = 0; i < 2 * n - 1; i++)
    {
        queensInMainDiags[i] = 0;
        queensInSecondaryDiags[i] = 0;

        if (i < n)
        {
            // q[i] = i;
            queensInRow[i] = 0;
        }
    }
    // randomShuffle(q, n, [](int i) -> int { return std::rand() % i; });

    for (int i = 0; i < n; i++)
    {
        q[i] = rand() % n; // rand int between 0 and n
        // q[i] = getRowWithMinConf(i);
        queensInRow[q[i]] += 1;
        addToMainDiagonal(q[i], i, 1);
        addToSecondaryDiagonal(q[i], i, 1);
    }
}

void Board::addToMainDiagonal(int col, int row, int value)
{
    if (row <= col)
    {
        queensInMainDiags[(n - 1) - abs(row - col)] += value;
        return;
    }
    queensInMainDiags[(n - 1) + abs(row - col)] += value;
}

void Board::addToSecondaryDiagonal(int row, int col, int value)
{
    // Overengineered it a bit
    // if (row >= n - col - 1)
    // {
    //     queensInSecondaryDiags[(n - 1) - abs(n - col - 1 - row)] += value;
    //     return;
    // }
    // queensInSecondaryDiags[(n - 1) + abs(n - col - 1 - row)] += value;
    queensInSecondaryDiags[row + col] += value;
}

// Returns the number of queens that conflict with (row, col), not
// counting the queen in column col.
int Board::numberOfConflicts(int row, int col)
{
    int fix = NO_FIX; // we will count 3 additional conflicts if we are on a queen - those should be subtracted
    if (isPositionOccupiedByQueen(row, col))
    {
        fix = FIX;
    }

    int mainDiagonalIndex;
    if (row <= col)
    {
        mainDiagonalIndex = (n - 1) - abs(row - col);
    }
    else
    {
        mainDiagonalIndex = (n - 1) + abs(row - col);
    }

    int secondaryDiagonalIndex = row + col;

    return queensInRow[row] + queensInMainDiags[mainDiagonalIndex] + queensInSecondaryDiags[secondaryDiagonalIndex] - fix;
}

void Board::solve()
{
    int moves = 0;
    int col, row;
    // std::cout << toString() << "\n";
    while (true)
    {
        col = getColWithQueenWithMaxConf();
        if (col == -1)
        {
            return;
        }
        row = getRowWithMinConf(col);
        // Move queen
        updateStats(col, row);
        if (isSolved())
        {
            return;
        }
        moves++;
        if (n * K == moves)
        {
            // restart
            shuffle();
            moves = 0;
        }
    }
}

// rowWithMinConfl is old row
// q[col] = row;
void Board::updateStats(int worstQueenColumn, int rowWithMinConfl)
{

    int oldRow = q[worstQueenColumn];
    if (rowWithMinConfl != oldRow)
    {
        q[worstQueenColumn] = rowWithMinConfl;
        queensInRow[oldRow] -= 1;
        queensInRow[rowWithMinConfl] += 1;
        addToMainDiagonal(oldRow, worstQueenColumn, -1);
        addToMainDiagonal(rowWithMinConfl, worstQueenColumn, 1);
        addToSecondaryDiagonal(oldRow, worstQueenColumn, -1);
        addToSecondaryDiagonal(rowWithMinConfl, worstQueenColumn, 1);
    }
}

int Board::getRowWithMinConf(int col)
{
    candidates.clear();
    int minNumberOfConflicts = n;
    for (int i = 0; i < n; i++)
    {
        int numberOfConflicts = this->numberOfConflicts(i, col);
        if (numberOfConflicts == minNumberOfConflicts)
        {
            candidates.push_back(i);
        }
        else if (numberOfConflicts < minNumberOfConflicts)
        {
            minNumberOfConflicts = numberOfConflicts;
            candidates.clear();
            candidates.push_back(i);
        }
    }

    // if (!candidates.empty())
    // {
    return candidates.at(rand() % candidates.size());

    // }
}

int Board::getColWithQueenWithMaxConf()
{
    int maxConflicts = 0;
    candidates.clear();
    for (int i = 0; i < n; i++)
    {
        int numberOfConflicts = this->numberOfConflicts(q[i], i);
        if (numberOfConflicts == maxConflicts)
        {
            candidates.push_back(i);
        }
        else if (numberOfConflicts > maxConflicts)
        {
            maxConflicts = numberOfConflicts;
            candidates.clear();
            candidates.push_back(i);
        }
    }

    if (maxConflicts == 0)
    {
        // Checked every queen and found no conflicts
        return -1;
    }

    // Pick a random queen from those that had the most conflicts
    return candidates.at(rand() % candidates.size());
}

bool Board::isPositionOccupiedByQueen(int row, int col)
{
    return q[col] == row;
}

bool Board::isSolved()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int numOfConflicts = numberOfConflicts(i, j);
            if (isPositionOccupiedByQueen(i, j) && numOfConflicts > 0)
            {
                return false;
            }
        }
    }
    return true;
}

std::string Board::toString()
{
    std::string str("");
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            str.append(isPositionOccupiedByQueen(row, col) ? "Q\t" : ".\t");
        }
        str.append("\n");
    }
    return str;
}

void Board::printSolution()
{
    std::cout << toString();
}

Board::~Board()
{
    delete[] q;
    delete[] queensInRow;
    delete[] queensInSecondaryDiags;
    delete[] queensInMainDiags;
}