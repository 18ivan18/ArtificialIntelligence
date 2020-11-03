#ifndef FROG_LEAP_PUZZLE
#define FROG_LEAP_PUZZLE
#include "State.cpp"
#include <stack>
#include <vector>

class FrogLeapPuzzle
{
private:
    bool solutionFound;
    bool dfs(State *);
    std::stack<State *> solution;
    int n, size;
    State *initializeStates();
    bool isGoalState(State *) const;
    Board *goalBoard;
    TILE *reverse(TILE *&, int size);

public:
    FrogLeapPuzzle(int);
    void printSolution();
    bool hasSolution();
    ~FrogLeapPuzzle();
};
#endif