#include "Solver.h"

Solver::Solver(int n)
{
    board = new Board(n);
}

void Solver::solve()
{
    auto start = std::chrono::steady_clock::now();
    board->solve();
    auto end = std::chrono::steady_clock::now();
    elapsedSeconds = end - start;
    // board->printSolution();
}

double Solver::elapsedTime()
{
    return elapsedSeconds.count();
}

Solver::~Solver()
{
    delete board;
}
