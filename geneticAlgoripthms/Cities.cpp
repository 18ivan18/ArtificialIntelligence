#include "Cities.h"

Cities *Cities::instance = nullptr;

std::vector<City *> *Cities::getCities()
{
    return this->allCities;
}

Cities *Cities::getInstance()
{
    if (!instance)
        instance = new Cities();
    return instance;
}

Cities::Cities()
{
    allCities = new std::vector<City *>;
}

int Cities::numberOfCities()
{
    return allCities->size();
}

City *Cities::getCity(int index)
{
    return allCities->at(index);
}

void Cities::addCity(City *city)
{
    allCities->push_back(city);
}