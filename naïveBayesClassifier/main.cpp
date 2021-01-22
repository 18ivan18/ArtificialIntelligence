#include <iostream>
#include "BayesClassifier.cpp"

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        std::cerr << "Input <dataset.data>\n";
        return 1;
    }
    try
    {
        BayesClassifier bc(argc[1]);
        bc.trainAndPredict();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}