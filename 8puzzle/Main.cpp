#include <iostream>
#include <fstream>
#include "Solver.cpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./main <inputFileName>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cout << "Wrong file name.\n";
        return 1;
    }
    Solver slvr(input);
    std::cout << "Best solution in: " << slvr.moves() << std::endl;
    slvr.printSolution();
    input.close();

    return 0;
}