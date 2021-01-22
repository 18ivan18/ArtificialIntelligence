#include "DecisionTree.h"
#include <numeric>
#include "EntropyCalculator.cpp"
#include "Values.h"

struct DecisionTree::Node
{
    vector<vector<string>> data;

    int attribute;

    vector<Node *> children;

    vector<string> values;

    string *finalValue;

    Node(vector<vector<string>> data);
    ~Node();

    Node(const Node &other);
};

DecisionTree::Node::Node(vector<vector<string>> data)
{
    this->data = data;
    finalValue = nullptr;
}

DecisionTree::Node::~Node()
{
    delete finalValue;
    for (auto &child : children)
    {
        delete child;
    }
}

DecisionTree::Node::Node(const Node &other)
{
    data = other.data;
    attribute = other.attribute;
    values = other.values;
    finalValue = other.finalValue;
}

vector<vector<string>> DecisionTree::extractData(const vector<vector<string>> &input, bool isTraining)
{
    vector<vector<string>> extractedData;
    if (isTraining)
    {
        for (int i = 0; i < (input.size() * TRAINING_PERCENTAGE) / 100; i++)
        {
            extractedData.push_back(input.at(i));
        }
    }
    else
    {
        for (int i = input.size() - 1; i >= (input.size() * TRAINING_PERCENTAGE) / 100; i--)
        {
            extractedData.push_back(input.at(i));
        }
    }
    return extractedData;
}

vector<vector<string>> DecisionTree::getData(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold)
{
    vector<vector<string>> data;
    int size = input.size();

    for (int i = (size * testFrom) / fold; i < (size * testTo) / fold; i++)
    {
        data.push_back(input.at(indices.at(i)));
    }

    return data;
}
vector<vector<string>> DecisionTree::getTrainingData(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold)
{
    vector<vector<string>> firstPart = getData(input, indices, 0, testFrom, fold);
    vector<vector<string>> secondPart = getData(input, indices, testTo, fold, fold);

    for (auto elem : secondPart)
    {
        firstPart.push_back(elem);
    }

    return firstPart;
}

DecisionTree::DecisionTree(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold)
{
    minNumExamples = MIN_NUM_EXAMPLES;
    vector<vector<string>> data = getTrainingData(input, indices, testFrom, testTo, fold);

    trainingData = extractData(data, true);
    validationData = extractData(data, false);
    testData = getData(input, indices, testFrom, testTo, fold);
}

DecisionTree::~DecisionTree()
{
    delete root;
}

void DecisionTree::setMinNumExamples(int minNumExamples)
{
    this->minNumExamples = minNumExamples;
}

string DecisionTree::getPrediction(const vector<string> &testRecord, Node *node)
{
outerLoop:
    while (node->finalValue == nullptr)
    {
        for (int i = 0; i < node->values.size(); i++)
        {
            string value = node->values.at(i);
            if (value.compare(testRecord.at(node->attribute)) == 0)
            {
                node = node->children.at(i);
                goto outerLoop;
            }
        }
        return *getFinalValue(node->data);
    }
    return *node->finalValue;
}

double DecisionTree::testWithData(const vector<vector<string>> &data, Node *node)
{
    int all = data.size();
    int correct = 0;

    string answer;
    for (const auto &testRecord : data)
    {
        answer = getPrediction(testRecord, node);

        if (answer.compare(testRecord.at(0)) == 0)
        {
            correct++;
        }
    }

    return (double)correct / (double)all;
}

// Result and best node pair
std::pair<double, DecisionTree::Node *> DecisionTree::getBestResult(Node *node, Node *root)
{
    if (node->finalValue != nullptr)
    {
        return {0.0, nullptr};
    }
    node->finalValue = getFinalValue(node->data);

    Node *bestNode = node;
    double currentBest = testWithData(validationData, root);

    node->finalValue = nullptr;

    for (const auto &child : node->children)
    {
        if (child->finalValue == nullptr)
        {
            auto [result, bestNodeResult] = getBestResult(child, root);

            if (result > currentBest)
            {
                currentBest = result;
                bestNode = bestNodeResult;
            }
        }
    }

    return {currentBest, bestNode};
}

void DecisionTree::applyReducedErrorPostPruning()
{
    double initialResult = testWithData(validationData, root);

    while (true)
    {
        auto [result, bestNode] = getBestResult(root, root); // start node and root node

        if (bestNode == nullptr || bestNode->finalValue != nullptr)
        {
            break;
        }

        // Prune
        bestNode->finalValue = getFinalValue(bestNode->data);

        double currentResult = testWithData(validationData, root);

        if (currentResult >= initialResult)
        {
            initialResult = currentResult;
        }
        else
        {
            bestNode->finalValue = nullptr;
            break;
        }
    }
}

void DecisionTree::train()
{
    root = new Node(trainingData);
    vector<bool> usedAttributes;
    usedAttributes.assign(trainingData.at(0).size(), false);

    buildTree(root, trainingData, usedAttributes);

    applyReducedErrorPostPruning();
}

bool DecisionTree::allAttributesUsed(const vector<bool> &used)
{
    using std::accumulate;
    return accumulate(used.begin(), used.end(), true);
}

string *DecisionTree::getFinalValue(const vector<vector<string>> &data)
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

    return (2 * numberOfRecurrenceEvents >= data.size() ? new string("recurrence-events") : new string("no-recurrence-events"));
}

vector<string> DecisionTree::getClasses(const vector<vector<string>> &data)
{
    vector<string> classes;
    classes.push_back(data.at(0).at(0));

    for (int i = 1; i < data.size(); i++)
    {
        if (data.at(i).at(0).at(0) != classes.at(0).at(0))
        {
            classes.push_back(data.at(i).at(0));
            return classes;
        }
    }
    return classes;
}

int DecisionTree::getBestAttribute(const vector<vector<string>> &data, const vector<bool> &used)
{
    int bestAttribute = 0;
    double bestGain = 0;

    for (int attribute = 1; attribute <= 9; attribute++)
    {
        if (!used[attribute])
        {
            double currentGain = getInformationGainForAttribute(data, attribute);

            if (currentGain > bestGain)
            {
                bestGain = currentGain;
                bestAttribute = attribute;
            }
        }
    }

    return bestAttribute;
}

double DecisionTree::getInformationGainForAttribute(vector<vector<string>> data, int attribute)
{
    return EntropyCalculator::getDataSetEntropy(data) -
           EntropyCalculator::getDataSetEntropyByAttribute(data, attribute);
}

vector<vector<string>> DecisionTree::getPartialTrainingData(const vector<vector<string>> &data, int attribute, const string &value)
{
    vector<vector<string>> partialData;

    for (const auto &record : data)
    {
        if (record.at(attribute).compare(value) == 0)
        {
            partialData.push_back(record);
        }
    }

    return partialData;
}

void DecisionTree::buildTree(Node *node, const vector<vector<string>> &input, vector<bool> usedAttributes)
{
    // Pre-pruning
    if (input.size() <= minNumExamples || allAttributesUsed(usedAttributes))
    {
        node->finalValue = getFinalValue(input);
        return;
    }

    vector<string> classes = getClasses(input);

    if (classes.size() == 1)
    {
        node->finalValue = new string(classes.at(0));
        return;
    }

    node->attribute = getBestAttribute(input, usedAttributes);

    usedAttributes[node->attribute] = true;

    vector<string> values = Values::getInstance()->getValues().at(node->attribute - 1);

    for (const auto &value : values)
    {
        vector<vector<string>> partialTrainingData = getPartialTrainingData(input, node->attribute, value);

        if (!partialTrainingData.empty())
        {
            Node *child = new Node(partialTrainingData);
            node->children.push_back(child);
            node->values.push_back(value);

            buildTree(child, partialTrainingData, usedAttributes);
        }
    }
}

double DecisionTree::test()
{
    return testWithData(testData, root);
}
