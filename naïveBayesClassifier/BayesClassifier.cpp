#include "BayesClassifier.h"

int BayesClassifier::NUMBER_OF_ATTRIBUTES = 16;
int BayesClassifier::NUMBER_OF_ATTRIBUTES_AND_CLASSES = 17;
int BayesClassifier::NUMBER_OF_SUBSETS = 10;
std::string BayesClassifier::Y = "y";
std::string BayesClassifier::N = "n";
std::string BayesClassifier::YES = "YES";
std::string BayesClassifier::NO = "NO";

std::unordered_map<ClassId, std::string> BayesClassifier::classIdToStringMap = {
    {0, "democrat"},
    {1, "republican"},
};

std::unordered_map<AttributeId, std::string> BayesClassifier::attributeIdToStringMap = {
    {0, "HANDICAPPED_INFANTS"},
    {1, "WATER_PROJECT_COST_SHARING"},
    {2, "ADOPTION_OF_THE_BUDGET_RESOLUTION"},
    {3, "PHYSICIAN_FEE_FREEZE"},
    {4, "EL_SALVADOR_AID"},
    {5, "RELIGIOUS_GROUPS_IN_SCHOOLS"},
    {6, "ANTI_SATELLITE_TEST_BAN"},
    {7, "AID_TO_NICARAGUAN_CONTRAS"},
    {8, "MX_MISSILE"},
    {9, "IMMIGRATION"},
    {10, "SYNFUELS_CORPORATION_CUTBACK"},
    {11, "EDUCATION_SPENDING"},
    {12, "SUPERFUND_RIGHT_TO_SUE"},
    {13, "CRIME"},
    {14, "DUTY_FREE_EXPORTS"},
    {15, "EXPORT_ADMINISTRATION_ACT_SOUTH_AFRICA"},
};

std::unordered_map<AttributeValue, std::string> BayesClassifier::attributeValueToStringMap = {
    {0, YES},
    {1, NO},
    {2, "INDETERMINATE"},
};

BayesClassifier::BayesClassifier(const std::string &str)
{
    readData(str);
    splitIntoSubsets(data, NUMBER_OF_SUBSETS);
}

void BayesClassifier::readData(const std::string &str)
{
    std::ifstream is(str);
    if (!is)
    {
        throw new std::invalid_argument("Invalid file...\n");
    }

    std::string line;
    while (std::getline(is, line))
    {
        std::vector<std::string> strs = split(line, ",");
        std::vector<int> dataEntry;

        if (strs.size() != BayesClassifier::NUMBER_OF_ATTRIBUTES_AND_CLASSES)
        {
            throw new std::invalid_argument("Something is wrong with the input data...\n");
        }

        if (strs[0] == "republican")
        {
            dataEntry.push_back(1);
        }
        else if (strs[0] == "democrat")
        {
            dataEntry.push_back(0);
        }
        else
        {
            throw new std::invalid_argument("Invalid class...\n");
        }

        for (int i = 1; i < strs.size(); i++)
        {
            if (strs[i] == BayesClassifier::Y)
            {
                dataEntry.push_back(0);
            }
            else if (strs[i] == BayesClassifier::N)
            {
                dataEntry.push_back(1);
            }
            else if (strs[i] == "?")
            {
                dataEntry.push_back(2);
            }
            else
            {
                throw new std::invalid_argument("Invalid value for attribute...\n");
            }
        }

        data.push_back(dataEntry);
    }
}

void BayesClassifier::splitIntoSubsets(InputEntries &data, int numberOfSubsets)
{
    std::cout << "Input data size: [" << data.size() << "]\n";
    std::cout << "Number of subsets: [" << numberOfSubsets << "]\n";
    std::random_shuffle(data.begin(), data.end());
    // auto rng = std::default_random_engine{};
    // std::shuffle(std::begin(data), std::end(data), rng);

    int numberOfElementsInSubset = ceil(static_cast<double>(data.size()) / numberOfSubsets);
    std::cout << "Number of elements in subset = [" << numberOfElementsInSubset << "]\n";

    int numberOfElementsInLastSubset = data.size() - (numberOfElementsInSubset * (numberOfSubsets - 1));
    std::cout << "Number of elements in last subset should be equal to [" << numberOfElementsInLastSubset << "]\n";

    // Fill all but the last subset
    for (int chunk = 0; chunk < numberOfSubsets - 1; chunk++)
    {
        std::cout << "Filling subset number " << (chunk + 1) << std::endl;
        int startIndex = chunk * numberOfElementsInSubset;
        int endIndex = startIndex + numberOfElementsInSubset - 1;
        InputEntries inputEntries;
        for (int i = startIndex; i <= endIndex; i++)
        {
            inputEntries.push_back(data[i]);
        }
        subsets.push_back(inputEntries);
    }

    // Fill last subset
    std::cout << "Filling subset number " << numberOfSubsets << std::endl;
    const int startIndex = (numberOfSubsets - 1) * numberOfElementsInSubset;
    const int endIndex = data.size() - 1;
    InputEntries inputEntries;
    for (int i = startIndex; i <= endIndex; i++)
    {
        inputEntries.push_back(data[i]);
    }
    subsets.push_back(inputEntries);
    std::cout << "Number of elements in last subset is equal to: [" << inputEntries.size() << "]\n";
}

std::vector<std::string> BayesClassifier::split(std::string &s, const std::string &delimiter)
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

void BayesClassifier::trainAndPredict()
{
    for (int testSubset = 0; testSubset < NUMBER_OF_SUBSETS; testSubset++)
    {
        // testSubset will be used for testing, all the other subsets will be used for training
        std::cout << "\n--------------------- TEST SUBSET WILL BE " << testSubset
                  << " ---------------------\n\n";

        // start constructing training set
        InputEntries trainingSet;
        for (int subset = 0; subset < NUMBER_OF_SUBSETS; subset++)
        {
            if (subset == testSubset)
            {
                // Do not add testSubset to trainingSet
                continue;
            }
            trainingSet.insert(trainingSet.end(), subsets[subset].begin(),
                               subsets[subset].end());
        }

        // ok, now we have a training set, let's train our model!
        calculcateProbabilityPerClassAndAttribute(trainingSet, NUMBER_OF_ATTRIBUTES);

        // now that we've trained our model, let's use the testSubset for some
        // predictions...
        std::cout << "\n ------------ PREDICTIONS START ------------\n";
        int successfulPredictions = 0, totalPredictions = 0;
        for (const auto &entry : subsets[testSubset])
        {
            std::string actualClass = classIdToStringMap.at(entry[0]);

            std::vector<int> attributes{entry.begin() + 1, entry.end()};
            std::string predictedClass = predict(attributes);

            std::cout << "Attributes: [";
            for (auto attributeValue : attributes)
            {
                std::cout << attributeValue << ",";
            }
            std::cout << "]; actual class: " << actualClass
                      << "; predicted class: " << predictedClass << std::endl;

            totalPredictions++;
            if (actualClass == predictedClass)
            {
                successfulPredictions++;
            }
        }

        std::cout << "Results:\n";
        std::cout << "Successful predictions: " << successfulPredictions << std::endl;
        std::cout << "Total predictions: " << totalPredictions << std::endl;
        double accuracy =
            (static_cast<double>(successfulPredictions) / totalPredictions);
        accuracies.push_back(accuracy);
        std::cout << "Accuracy: " << accuracy << std::endl;
        std::cout << "--------------------- TEST FINISH FOR SUBSET " << testSubset
                  << " ---------------------\n\n";
    }
    auto accuraciesSum = accumulate(accuracies.begin(), accuracies.end(), 0.0);

    std::cout << "Mean of all accuracies: " << (accuraciesSum / accuracies.size())
              << std::endl;
}

void BayesClassifier::calculcateProbabilityPerClassAndAttribute(const InputEntries &data, int numberOfAttributes)
{

    // count classes <C, total number of instances with class C>
    std::unordered_map<ClassId, Count> classToCountMap;

    // count attributes per class <C, <AttributeId, <AttributeValue, Count>>>
    // for example:
    // <class Democrat -> <HANDICAPPED_INFANTS -> {"yes" -> 69, "no" -> 23,
    // "indeterminate" -> 15},
    //                    <PHYSICIAN_FEE_FREEZE -> {"yes" -> 123, "no" -> 4,
    //                    "indeterminate" -> 67}>>
    std::unordered_map<ClassId, std::unordered_map<AttributeId,
                                                   std::unordered_map<AttributeValue, Count>>>
        classToAttributeCountMap;

    countAllClassesAndAttributes(data, numberOfAttributes, classToCountMap,
                                 classToAttributeCountMap);

    //[ currentClassId, attributeIdToCountMap ]
    for (auto &pair :
         classToAttributeCountMap)
    {
        ClassId currentClassId = pair.first;
        std::unordered_map<AttributeId,
                           std::unordered_map<AttributeValue, Count>>
            attributeIdToCountMap = pair.second;
        std::cout << "\n--- Class " << classIdToStringMap[currentClassId] << " ---"
                  << std::endl;
        // [attributeId, attributeCountMap]
        for (auto &pair : attributeIdToCountMap)
        {
            AttributeId attributeId = pair.first;
            std::unordered_map<AttributeValue, Count> attributeCountMap = pair.second;
            for (int attributeValue = 0; attributeValue <= 2; attributeValue++)
            {
                auto &probability =
                    classToAttributeProbabilityMap[currentClassId][attributeId]
                                                  [attributeValue];
                probability = static_cast<double>(attributeCountMap[attributeValue]) /
                              classToCountMap[currentClassId];

                std::cout << "Attribute " << attributeIdToStringMap[attributeId]
                          << " P(x=" << attributeValueToStringMap[attributeValue]
                          << "|C=" << classIdToStringMap[currentClassId]
                          << ") = " << probability << std::endl;
            }
        }

        classToProbabilityMap[currentClassId] =
            static_cast<double>(classToCountMap[currentClassId]) / data.size();

        std::cout << "Class P(C=" << classIdToStringMap.at(currentClassId)
                  << ") = " << classToProbabilityMap[currentClassId] << std::endl;
    }
}

void BayesClassifier::countAllClassesAndAttributes(
    const InputEntries &data, int numberOfAttributes,
    std::unordered_map<ClassId, Count> &classToCountMap,
    std::unordered_map<
        ClassId,
        std::unordered_map<AttributeId, std::unordered_map<AttributeValue, Count>>>
        &classToAttributeCountMap)
{
    // Entry is vector of the class and all 16 attributes
    for (const auto &entry : data)
    {
        const int currentClass = entry[0];
        if (classToCountMap.find(currentClass) == classToCountMap.end())
        {
            classToCountMap[currentClass] = 1;
            classToAttributeCountMap[currentClass] = {};
        }
        else
        {
            classToCountMap[currentClass] += 1;
        }

        for (int attributeId = 0; attributeId < numberOfAttributes; attributeId++)
        {
            const int attributeValue = entry[attributeId];
            // Value - count map
            auto &currentClassAttributeToCountMap =
                classToAttributeCountMap[currentClass][attributeId];
            if (currentClassAttributeToCountMap.find(attributeValue) ==
                currentClassAttributeToCountMap.end())
            {
                currentClassAttributeToCountMap[attributeValue] = 1;
            }
            else
            {
                currentClassAttributeToCountMap[attributeValue] += 1;
            }
        }
    }
}

std::string BayesClassifier::predict(const std::vector<int> &attributes)
{
    int maxProbabilityClassId = -1;
    double maxProbability = 0;
    // [currentClassId, currentClassProbability]
    for (const auto &pair : classToProbabilityMap)
    {
        const ClassId currentClassId = pair.first;
        const Probability currentClassProbability = pair.second;
        // p(C|x) = p(C)*p(x1|C)*p(x2|C)*…
        double pCx = currentClassProbability;
        for (int attributeId = 0; attributeId < attributes.size(); attributeId++)
        {
            pCx *= classToAttributeProbabilityMap[currentClassId][attributeId]
                                                 [attributes[attributeId]] +
                   1; // laplace smoothing
        }

        if (pCx > maxProbability)
        {
            maxProbability = pCx;
            maxProbabilityClassId = currentClassId;
        }
    }

    std::cout << "maxProbabilityClassId = [" << maxProbabilityClassId << "]\n";
    std::cout << "maxProbability = [" << maxProbability << "]\n";
    std::cout << "Predict Class : " << classIdToStringMap.at(maxProbabilityClassId)
              << " P(C|x1,x2,...,xN) = " << maxProbability << std::endl;

    return classIdToStringMap.at(maxProbabilityClassId);
}