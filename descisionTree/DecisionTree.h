#ifndef DECISION_TREE
#define DECISION_TREE
#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;

class DecisionTree
{
private:
    const int MIN_NUM_EXAMPLES = 5;
    const int TRAINING_PERCENTAGE = 75;
    struct Node;
    Node *root;

    int minNumExamples;

    void buildTree(Node *node, const vector<vector<string>> &input, vector<bool> usedAttributes);
    vector<string> getClasses(const vector<vector<string>> &data);
    int getBestAttribute(const vector<vector<string>> &data, const vector<bool> &used);
    double getInformationGainForAttribute(vector<vector<string>> data, int attribute);
    vector<vector<string>> getPartialTrainingData(const vector<vector<string>> &data, int attribute, const string &value);
    void applyReducedErrorPostPruning();
    double testWithData(const vector<vector<string>> &data, Node *node);
    string getPrediction(const vector<string> &testRecord, Node *node);

    vector<vector<string>> trainingData;

    vector<vector<string>> validationData;

    vector<vector<string>> testData;

    vector<vector<string>> getTrainingData(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold);
    vector<vector<string>> extractData(const vector<vector<string>> &input, bool isTraining);
    vector<vector<string>> getData(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold);
    bool allAttributesUsed(const vector<bool> &used);
    std::string *getFinalValue(const vector<vector<string>> &input);
    std::pair<double, Node *> getBestResult(Node *node, Node *root);

public:
    DecisionTree(const vector<vector<string>> &input, const vector<int> &indices, int testFrom, int testTo, int fold);
    void train();
    double test();
    void setMinNumExamples(int);
    ~DecisionTree();
};

#endif
