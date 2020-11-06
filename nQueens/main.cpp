#include <iostream>
#include "Solver.cpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./main <n>\n";
        return 1;
    }

    Solver s(std::stoi(argv[1]));
    s.solve();
    std::cout << s.elapsedTime() << "\n";

    return 0;
}