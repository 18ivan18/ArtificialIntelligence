#include "FrogLeapPuzzle.h"

FrogLeapPuzzle::~FrogLeapPuzzle()
{
    delete goalBoard;
}

void FrogLeapPuzzle::printSolution()
{
    if (!hasSolution())
    {
        return;
    }
    std::stack<State *> solution = this->solution;
    while (!solution.empty())
    {
        State *temp = solution.top();
        solution.pop();
        for (int i = 0; i < temp->getBoard()->getSize(); i++)
        {
            std::cout << (char)temp->getBoard()->getBoard()[i] << " ";
        }
        std::cout << std::endl;
    }
}

bool FrogLeapPuzzle::hasSolution()
{
    return solutionFound;
}

bool FrogLeapPuzzle::isGoalState(State *state) const
{
    return *state->getBoard() == *goalBoard;
}

bool FrogLeapPuzzle::dfs(State *state)
{
    if (isGoalState(state))
    {
        return true;
    }
    for (State *move : state->moves())
    {
        if (dfs(move))
        {
            solution.push(move);
            return true;
        }
    }
    return false;
}

TILE *FrogLeapPuzzle::reverse(TILE *&arr, int size)
{
    TILE *reverse = new TILE[size];
    for (int i = 0; i < size; i++)
    {
        reverse[i] = arr[size - i - 1];
    }
    return reverse;
}

State *FrogLeapPuzzle::initializeStates()
{
    TILE *arr = new TILE[size];
    arr[size / 2] = EMPTY;
    for (int i = 0; i < n; i++)
    {
        arr[i] = BROWN_FROG;
        arr[size - i - 1] = GREEN_FROG;
    }
    goalBoard = new Board(reverse(arr, size), size, size / 2);

    return new State(new Board(arr, size, size / 2), NO_MOVE);
}

FrogLeapPuzzle::FrogLeapPuzzle(int n)
{
    this->n = n;
    this->size = (2 * n) + 1;
    State *zeroState = initializeStates();
    this->solutionFound = dfs(zeroState);
}
