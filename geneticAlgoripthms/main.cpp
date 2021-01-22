#include <iostream>
#include "Solver.cpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./main <n>\n";
        return 1;
    }
    Solver slv(std::stoi(argv[1]));
    slv.solve();

    return 0;
}