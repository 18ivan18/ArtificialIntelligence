#ifndef CITIES
#define CITIES
#include <vector>
#include "City.cpp"

class Cities
{
    static Cities *instance;
    std::vector<City *> *allCities;

    // Private constructor so that no objects can be created.
    Cities();

public:
    static Cities *getInstance();
    Cities(const Cities &) = delete;
    Cities &operator=(const Cities &) = delete;

    std::vector<City *> *getCities();

    int numberOfCities();

    City *getCity(int);

    void addCity(City *);
};

#endif
