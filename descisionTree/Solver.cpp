#include "Solver.h"
#include <fstream>
#include "DecisionTree.cpp"
#include <iostream>
#include <algorithm>

Solver::Solver(const string &filename)
{
    readInput(filename);
    fold = DEFAULT_FOLD;
}

Solver::~Solver()
{
}

void Solver::setFold(int fold)
{
    this->fold = fold;
}

std::vector<std::string> Solver::split(std::string &s, const std::string &delimiter)
{
    std::vector<std::string> list;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

void Solver::readInput(const string &filename)
{
    std::ifstream is(filename);
    if (!is)
    {
        throw new std::invalid_argument("Invalid file...\n");
    }

    string line;
    while (std::getline(is, line))
    {
        std::vector<std::string> record = split(line, ",");
        input.push_back(record);
    }
}

void Solver::solve()
{
    vector<int> shuffledIndexes = getShuffledIndexes(input.size());

    double accuracy, averageAccuracy = 0;

    for (int i = 0; i < fold; i++)
    {
        DecisionTree decisionTree(input, shuffledIndexes, i, i + 1, fold);

        decisionTree.train();

        accuracy = decisionTree.test();
        std::cout << "Test " << (i + 1) << " accuracy: " << fractionToPercentage(accuracy) << "%" << std::endl;

        averageAccuracy += accuracy;
    }

    std::cout << "\nAverage accuracy: " << fractionToPercentage(averageAccuracy / fold) << "%" << std::endl;
}

vector<int> Solver::getShuffledIndexes(int size)
{
    vector<int> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(i);
    }
    std::random_shuffle(result.begin(), result.end());
    return result;
}

double Solver::fractionToPercentage(double fraction)
{
    return fraction * 100.0;
}