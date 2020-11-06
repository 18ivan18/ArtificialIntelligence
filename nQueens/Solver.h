#ifndef SOLVER
#define SOLVER
#include <chrono>
#include "Board.cpp"

class Solver
{
private:
    Board *board;
    std::chrono::duration<double> elapsedSeconds;

public:
    Solver(int);
    void solve();
    double elapsedTime();
    ~Solver();
};

#endif
