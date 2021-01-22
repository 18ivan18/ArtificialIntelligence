#include <iostream>
#include "Solver.cpp"

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        std::cerr << "Usage ./main <filename.data>\n";
        return -1;
    }

    Solver slv(argc[1]);
    slv.solve();

    return 0;
}