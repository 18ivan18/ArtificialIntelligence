#include "Route.h"
#include <algorithm> // std::random_shuffle

// creates a random route
Route::Route()
{
    for (int i = 0; i < Cities::getInstance()->numberOfCities(); i++)
    {
        route.push_back(Cities::getInstance()->getCity(i));
    }

    // Create a random shuffle
    std::random_shuffle(route.begin(), route.end());
    distance = 0;
}

Route::Route(bool empty)
{
    route.assign(Cities::getInstance()->numberOfCities(), nullptr);
    distance = 0;
}

std::string Route::toString() const
{
    std::string result("");
    for (City *city : route)
    {
        result.append(city->toString());
    }
    return result;
}

Route::Route(const std::vector<City *> &) {}

bool Route::operator<(Route &other)
{
    return this->getDistance() < other.getDistance();
}

bool Route::operator>(Route &other)
{
    return this->getDistance() > other.getDistance();
}

int Route::routeSize() const
{
    return route.size();
}

int Route::getDistance()
{
    if (this->distance == 0)
    {
        int distance = 0;
        // Loop through our tour's cities
        for (int i = 0; i < routeSize(); i++)
        {
            // Get city we're travelling from
            City *fromCity = route[i];
            // City we're travelling to
            City *destinationCity;
            // Check we're not on our tour's last city, if we are set our
            // tour's final destination city to our starting city
            if (i + 1 < routeSize())
            {
                destinationCity = route[i + 1];
            }
            else
            {
                destinationCity = route[0];
            }
            // Get the distance between the two cities
            distance += fromCity->distanceTo(destinationCity);
        }
        this->distance = distance;
    }
    return distance;
}

void Route::setCity(int index, City *c)
{
    route[index] = c;
}

City *Route::getCity(int index) const
{
    return route[index];
}

bool Route::containsCity(City *city) const
{
    if (std::find(route.begin(), route.end(), city) != route.end())
        return true;

    return false;
}

Route::~Route() {}