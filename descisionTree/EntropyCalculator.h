#ifndef ENTROPY_CALCULATOR
#define ENTROPY_CALCULATOR
#include <vector>
#include <string>
using std::string;
using std::vector;

class EntropyCalculator
{
public:
    EntropyCalculator() = delete;
    static double getDataSetEntropy(const vector<vector<string>> &data);
    static double getEntropy(int firstValue, int secondValue);
    static double getDataSetEntropyByAttribute(const vector<vector<string>> &data, int attribute);
};

#endif
