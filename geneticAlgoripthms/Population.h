#ifndef POPULATION
#define POPULATION
#include "Route.cpp"

class Population
{
private:
    static constexpr double MUTATUION_RATE = 0.2;
    static constexpr double PARENTS_PERCENTAGE = 0.2;
    std::vector<Route *> routes;
    void crossover(std::vector<Route *> &);
    Route *breedNewIndivid(const Route *, const Route *);
    void mutate();

public:
    Population(int);
    int populationSize();
    Route *getFittest();
    void buildNextGeneration();
    ~Population();
};

#endif
