#include "EntropyCalculator.h"
#include <cmath>
#include <map>

double EntropyCalculator::getDataSetEntropy(const vector<vector<string>> &data)
{
    int numberOfRecurrenceEvents = 0;
    for (const auto &record : data)
    {
        if (record.at(0).at(0) == 'r')
        {
            // Class recurrence-events
            numberOfRecurrenceEvents++;
        }
    }

    // E(S)
    return getEntropy(numberOfRecurrenceEvents, data.size() - numberOfRecurrenceEvents);
}

double EntropyCalculator::getEntropy(int firstValue, int secondValue)
{
    double p = double(firstValue) / double(firstValue + secondValue);
    double q = double(secondValue) / double(firstValue + secondValue);

    return -p * log2(p) - q * log2(q);
}

double EntropyCalculator::getDataSetEntropyByAttribute(const vector<vector<string>> &data, int attributeId)
{
    int size = data.size();
    std::map<string, int> attributeOccuranceRec;
    std::map<string, int> attributeOccuranceNoRec;

    string attributeValue;
    int count;
    for (const auto &record : data)
    {
        attributeValue = record.at(attributeId);

        if (attributeValue.compare("?") == 0)
        {
            size--;
            continue;
        }

        if (record.at(0).at(0) == 'r')
        {
            // Class recurrence-events
            count = 1;
            if (attributeOccuranceRec.find(attributeValue) != attributeOccuranceRec.end())
            {
                count += attributeOccuranceRec[attributeValue];
            }
            attributeOccuranceRec.insert({attributeValue, count});
        }
        else
        {
            count = 1;
            if (attributeOccuranceNoRec.find(attributeValue) != attributeOccuranceNoRec.end())
            {
                count += attributeOccuranceNoRec[attributeValue];
            }
            attributeOccuranceNoRec.insert({attributeValue, 1});
        }
    }

    double entropy = 0;
    string key;
    for (const auto &recurringValue : attributeOccuranceRec)
    {
        key = recurringValue.first;
        if (attributeOccuranceNoRec.find(key) != attributeOccuranceNoRec.end())
        {
            entropy = entropy +
                      (((double)(attributeOccuranceRec[key]) + attributeOccuranceNoRec[key]) / (double)size) *
                          getEntropy(attributeOccuranceRec[key], attributeOccuranceNoRec[key]);
        }
    }

    return entropy;
}