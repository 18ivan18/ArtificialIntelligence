#ifndef BAYES_CLASSIFIER
#define BAYES_CLASSIFIER

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <random>

using InputEntries = std::vector<std::vector<int>>;
using Class = std::string;
using Count = int;
using ClassId = int;
using Probability = double;
using AttributeId = int;
using Count = int;
using AttributeValue = int;
using NumberOfAttributes = int;

class BayesClassifier
{
private:
    static int NUMBER_OF_ATTRIBUTES;
    static int NUMBER_OF_ATTRIBUTES_AND_CLASSES;
    static int NUMBER_OF_SUBSETS;
    static std::string YES;
    static std::string NO;
    static std::string Y;
    static std::string N;
    static std::unordered_map<ClassId, std::string> classIdToStringMap;
    static std::unordered_map<AttributeId, std::string> attributeIdToStringMap;
    static std::unordered_map<AttributeValue, std::string> attributeValueToStringMap;

    void readData(const std::string &);
    void splitIntoSubsets(InputEntries &, int);
    void calculcateProbabilityPerClassAndAttribute(const InputEntries &, int);
    void countAllClassesAndAttributes(const InputEntries &data, int numberOfAttributes,
                                      std::unordered_map<ClassId, Count> &classToCountMap,
                                      std::unordered_map<
                                          ClassId,
                                          std::unordered_map<AttributeId, std::unordered_map<AttributeValue, Count>>>
                                          &classToAttributeCountMap);
    std::string predict(const std::vector<int> &);

    std::vector<std::string> split(std::string &, const std::string &);
    InputEntries data;
    std::vector<InputEntries> subsets;
    std::vector<double> accuracies;
    // <class id, class probability>; <C,P(C)>
    std::unordered_map<ClassId, Probability> classToProbabilityMap;

    // <class id, <attribute id, <attribute value, probability>>> <-> <C,
    // <attribute x, <attribute x value, P(x=attributevalue|C)>>>
    std::unordered_map<
        ClassId,
        std::unordered_map<AttributeId, std::unordered_map<AttributeValue, Probability>>>
        classToAttributeProbabilityMap;

public:
    BayesClassifier(const std::string &);
    void trainAndPredict();
    ~BayesClassifier() = default;
};

#endif
