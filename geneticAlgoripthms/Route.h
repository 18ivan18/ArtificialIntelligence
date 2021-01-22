#ifndef ROUTE
#define ROUTE
#include <vector>
#include <string>
#include "Cities.cpp"

class Route
{
private:
    std::vector<City *> route;
    int distance;

public:
    Route();
    Route(bool);
    Route(const std::vector<City *> &);
    int getDistance();
    int routeSize() const;
    void setCity(int, City *);
    City *getCity(int) const;
    std::string toString() const;
    bool containsCity(City *city) const;
    bool operator<(Route &);
    bool operator>(Route &);
    ~Route();
};

#endif
