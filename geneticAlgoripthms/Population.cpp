#include "Population.h"
#include <iostream>

Population::Population(int size)
{
    routes.assign(size, nullptr);
    for (int i = 0; i < populationSize(); i++)
    {
        routes[i] = new Route();
    }
}

int Population::populationSize()
{
    return routes.size();
}

void Population::buildNextGeneration()
{
    std::sort(routes.begin(), routes.end(), [](Route *a, Route *b) -> bool { return *a < *b; });
    std::vector<Route *> parents;
    int parentsSize = int(routes.size() * PARENTS_PERCENTAGE);
    parentsSize = parentsSize % 2 == 0 ? parentsSize : parentsSize + 1;
    for (int i = 0; i < parentsSize; i++)
    {
        parents.push_back(routes[i]);
    }
    std::random_shuffle(parents.begin(), parents.end());
    crossover(parents);
    mutate();
}

Route *Population::getFittest()
{
    Route *fittest = routes[0];
    for (int i = 1; i < populationSize(); i++)
    {
        if (fittest->getDistance() < routes[i]->getDistance())
        {
            fittest = routes[i];
        }
    }
    return fittest;
}

void Population::mutate()
{
    for (int i = 0; i < routes.size(); i++)
    {
        for (int routeIndex = 0; routeIndex < routes[i]->routeSize(); routeIndex++)
        {
            if (((double)std::rand() / (RAND_MAX)) < MUTATUION_RATE)
            {
                int tourPos2 = (int)(routes[i]->routeSize() * ((double)std::rand() / (RAND_MAX)));

                City *city1 = routes[i]->getCity(routeIndex);
                City *city2 = routes[i]->getCity(tourPos2);

                routes[i]->setCity(tourPos2, city1);
                routes[i]->setCity(routeIndex, city2);
            }
        }
    }
}

void Population::crossover(std::vector<Route *> &parents)
{
    for (int i = 0; i < parents.size(); i += 2)
    {
        routes.push_back(breedNewIndivid(parents[i], parents[i + 1]));
    }
    std::sort(routes.begin(), routes.end(), [](Route *a, Route *b) -> bool { return *a < *b; });
    routes.erase(routes.begin() + routes.size() - parents.size() / 2 - 1, routes.end());
    // const int MAX_NUMBER_OF_PAIRS = 80;
    // for (int i = 0; i < MAX_NUMBER_OF_PAIRS; i++)
    // {
    //     int firstParent = std::rand() % parents.size();
    //     int secondParent = std::rand() % parents.size();
    //     while (firstParent == secondParent)
    //     {
    //         secondParent = std::rand() % parents.size();
    //     }

    //     routes.push_back(breedNewIndivid(parents[firstParent], parents[secondParent]));
    //     routes.push_back(breedNewIndivid(parents[secondParent], parents[firstParent]));
    // }

    // std::sort(routes.begin(), routes.end(), [](Route *a, Route *b) -> bool { return *a < *b; });
    // routes.erase(routes.begin() + Cities::getInstance()->numberOfCities(), routes.end());
}

Route *Population::breedNewIndivid(const Route *parent1, const Route *parent2)
{
    Route *child = new Route(false);

    int startPos = (int)(((double)std::rand() / (RAND_MAX)) * parent1->routeSize());
    int endPos = (int)(((double)std::rand() / (RAND_MAX)) * parent1->routeSize());
    for (int i = 0; i < child->routeSize(); i++)
    {
        if (startPos < endPos && i > startPos && i < endPos)
        {
            child->setCity(i, parent1->getCity(i));
        }
        else if (startPos > endPos)
        {
            if (!(i < startPos && i > endPos))
            {
                child->setCity(i, parent1->getCity(i));
            }
        }
    }

    for (int i = 0; i < parent2->routeSize(); i++)
    {
        if (!child->containsCity(parent2->getCity(i)))
        {
            for (int j = 0; j < child->routeSize(); j++)
            {
                if (child->getCity(j) == nullptr)
                {
                    child->setCity(j, parent2->getCity(i));
                    break;
                }
            }
        }
    }
    return child;
}

Population::~Population() {}