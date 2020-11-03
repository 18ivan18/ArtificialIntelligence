#include <iostream>
#include "FrogLeapPuzzle.cpp"

int main()
{
    int n;
    std::cin >> n;
    FrogLeapPuzzle flp(n);
    std::cout << std::boolalpha << flp.hasSolution() << "\n";
    flp.printSolution();

    return 0;
}