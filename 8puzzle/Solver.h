#ifndef SOLVER
#define SOLVER
#include "Board.cpp"
#include <fstream>
#include "minPQ/MinPQ.cpp"
#include <stack>

class Solver
{
private:
    class State;
    Board *init(std::ifstream &);
    State *lastState;
    int dfs(State *, int, int);
    void initGoalBoard(int, int);

public:
    // Solver(const Board &initial);
    Solver(std::ifstream &); // find a solution to the initial board (using the IDA* algorithm)
    int moves();             // min number of moves to solve initial board
    std::stack<Board *> solution();
    void printSolution();
    ~Solver();
};

#endif
