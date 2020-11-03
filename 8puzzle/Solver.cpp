#ifndef SOLVER_CPP
#define SOLVER_CPP

#include "Solver.h"
#include <iostream>

class Solver::State
{
private:
    Board *board;
    int numberOfMoves;
    State *prevState;
    int manhattan;

public:
    State(Board *board, int numberOfMoves, State *prevState)
    {
        this->board = board;
        this->numberOfMoves = numberOfMoves;
        this->prevState = prevState;
        this->manhattan = board->manhattan();
    }

    int getNumberOfMoves()
    {
        return numberOfMoves;
    }
    State *getPrevState()
    {
        return prevState;
    }

    Board *getBoard()
    {
        return board;
    }

    bool operator==(const State &other)
    {
        return (this->manhattan + this->numberOfMoves - other.manhattan - other.numberOfMoves) == 0;
    }
    bool operator>(const State &other)
    {
        return (this->manhattan + this->numberOfMoves - other.manhattan - other.numberOfMoves) > 0;
    }
    bool operator<(const State &other)
    {
        return !(*this > other);
    }
};

void Solver::initGoalBoard(int n, int positionOfZeroInGoal)
{
    int **goalBoard;
    goalBoard = new int *[n];
    for (int i = 0; i < n; i++)
    {
        goalBoard[i] = new int[n];
    }
    bool hasZero = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i * n + j == positionOfZeroInGoal)
            {
                goalBoard[i][j] = 0;
                hasZero = true;
            }
            else
            {
                goalBoard[i][j] = i * n + j + !hasZero;
            }
        }
    }
    if (!hasZero)
    {
        goalBoard[n - 1][n - 1] = 0;
    }
    Board::goalBoard = new Board(goalBoard, n);
}

Board *Solver::init(std::ifstream &input)
{
    int n, positionOfZeroInGoal;
    input >> n >> positionOfZeroInGoal;
    initGoalBoard(n, positionOfZeroInGoal);
    int **initialBoard;
    initialBoard = new int *[n];
    for (int i = 0; i < n; i++)
    {
        initialBoard[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> initialBoard[i][j];
        }
    }
    return new Board(initialBoard, n);
}

Solver::Solver(std::ifstream &input)
{
    Board *initial = init(input);
    // MinPQ<State *> pq;
    // pq.insert(lastState);
    lastState = new State(initial, 0, nullptr);
    int threshold = lastState->getBoard()->manhattan();
    int algorithm_result;

    do
    {
        algorithm_result = dfs(lastState, 0, threshold);

        if (algorithm_result == 0)
        {
            break;
        }

        // set new threshold
        threshold = algorithm_result;
    } while (threshold != INT32_MAX);
}

int Solver::dfs(State *state, int currentCost, int threshold)
{
    int estimatedCost = state->getBoard()->manhattan() + currentCost;

    if (estimatedCost > threshold)
    {
        return estimatedCost;
    }

    if (state->getBoard()->isGoal())
    {
        lastState = state;
        return 0;
    }

    int minimumCost = INT32_MAX;
    for (Board *successor : state->getBoard()->getNeighbors())
    {
        int successorIda = dfs(new State(successor, state->getNumberOfMoves() + 1, state), currentCost + 1, threshold);
        if (successorIda == 0)
        {
            return 0; // goal is found
        }
        if (successorIda < minimumCost)
        {
            minimumCost = successorIda;
        }
    }
    return minimumCost;
}

void Solver::printSolution()
{
    State *temp = lastState;
    std::stack<State *> sol;
    while (lastState->getPrevState())
    {
        sol.push(lastState);
        lastState = lastState->getPrevState();
    }
    while (!sol.empty())
    {
        std::cout << sol.top()->getBoard()->toString() << "\n";
        sol.pop();
    }
}

int Solver::moves()
{
    return lastState != nullptr ? lastState->getNumberOfMoves() : 0;
}

std::stack<Board *> Solver::solution()
{
    State *temp = lastState;
    std::stack<Board *> sol;
    while (lastState->getPrevState())
    {
        sol.push(lastState->getBoard());
        lastState = lastState->getPrevState();
    }
    return sol;
}

Solver::~Solver()
{
}

#endif