#ifndef BOARD
#define BOARD
#include <vector>
#include <string>

class Board
{
private:
    const int FIX = 3;
    const int NO_FIX = 0;
    const int K = 2;
    std::vector<int> candidates;
    int n;
    int *q, *queensInRow, *queensInMainDiags, *queensInSecondaryDiags;
    void shuffle();
    void addToMainDiagonal(int, int, int);
    void addToSecondaryDiagonal(int, int, int);
    bool isPositionOccupiedByQueen(int, int);
    int numberOfConflicts(int, int);
    int getColWithQueenWithMaxConf();
    int getRowWithMinConf(int);
    void updateStats(int, int);
    bool isSolved();
    void randomShuffle(int *, int, int (*f)(int));
    template <typename T>
    void swap(T &, T &);

public:
    Board(int);
    void solve();
    void printSolution();
    std::string toString();
    ~Board();
};

#endif
