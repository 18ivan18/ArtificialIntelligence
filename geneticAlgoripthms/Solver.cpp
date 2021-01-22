#include "Solver.h"
#include <random>
#include <ctime>

int Solver::N = 20;

int Solver::getN()
{
    return N;
}

Solver::Solver(int n)
{
    this->N = n;
    std::srand(std::time(nullptr));
    int x, y;
    for (int i = 0; i < N; i++)
    {
        x = (int)std::rand() % MAX_COORDNTE;
        y = (int)std::rand() % MAX_COORDNTE;
        Cities::getInstance()->addCity(new City(x, y));
    }
}
void Solver::solve()
{
    t = 0;
    population = new Population(N);
    int initialBestDistance = population->getFittest()->getDistance();
    while (isNotTerminated())
    {
        population->buildNextGeneration();
        t++;
        if (t == 10 || t == 40 || t == 70 || t == 90)
        {
            std::cout << t << "th path: " << population->getFittest()->getDistance() << '\n';
        }
    }
    std::cout << "Initial distance: " << initialBestDistance << "\n";
    std::cout << "Solution distance: " << population->getFittest()->getDistance() << '\n';
}

bool Solver::isNotTerminated()
{
    return t < MAX_ITERATIONS;
}

Solver::~Solver()
{
}