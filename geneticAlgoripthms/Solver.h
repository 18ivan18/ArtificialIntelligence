#ifndef SOLVER
#define SOLVER
class Cites;
#include "Population.cpp"

class Solver
{
private:
    static const int MAX_ITERATIONS = 100;
    static const int MAX_COORDNTE = 10000;
    static int N;
    int t;
    Population *population;
    bool isNotTerminated();

public:
    Solver(int);
    void solve();
    static int getN();
    ~Solver();
};

#endif
