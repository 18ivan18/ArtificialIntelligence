#ifndef CITY
#define CITY
#include <string>

class City
{
private:
    int x, y;

public:
    City(int, int);
    int getX();
    int getY();
    double distanceTo(City *);
    std::string toString() const;
    ~City();
};

#endif
