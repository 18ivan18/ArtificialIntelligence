#include "City.h"
#include <cmath>

City::City(int x, int y)
{
    this->x = x;
    this->y = y;
}

int City::getX() { return this->x; }

int City::getY() { return this->y; }

double City::distanceTo(City *city)
{
    int xDist = abs(getX() - city->getX());
    int yDist = abs(getY() - city->getY());
    return sqrt((xDist * xDist) + (yDist * yDist));
}

std::string City::toString() const
{
    std::string result("");
    result.append(std::to_string(this->x)).append(", ").append(std::to_string(this->y)).append(" ");
    return result;
}

City::~City() {}