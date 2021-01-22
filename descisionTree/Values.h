#ifndef VALUES
#define VALUES
#include <vector>
#include <string>
using std::string;
using std::vector;

class Values
{
private:
    Values();
    static Values *instance;
    vector<vector<string>> attributesValues;

public:
    Values(const Values &) = delete;
    Values &operator=(const Values &) = delete;
    static Values *getInstance();
    vector<vector<string>> getValues();
};

Values *Values::instance = nullptr;

Values *Values::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Values();
    }
    return instance;
}

vector<vector<string>> Values::getValues()
{
    return attributesValues;
}

Values::Values()
{
    vector<string> age = {"10-19", "20-29", "30-39", "40-49", "50-59", "60-69", "70-79", "80-89", "90-99"};
    vector<string> menopause = {"lt40", "ge40", "premeno"};
    vector<string> tumor_size = {"0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39", "40-44",
                                 "45-49", "50-54", "55-59"};
    vector<string> inv_nodes = {"0-2", "3-5", "6-8", "9-11", "12-14", "15-17", "18-20", "21-23", "24-26",
                                "27-29", "30-32", "33-35", "36-39"};
    vector<string> node_caps = {"yes", "no"};
    vector<string> deg_malig = {"1", "2", "3"};
    vector<string> breast = {"left", "right"};
    vector<string> breast_quad = {"left_up", "left_low", "right_up", "right_low", "central"};
    vector<string> irradiat = {"yes", "no"};

    attributesValues.push_back(age);
    attributesValues.push_back(menopause);
    attributesValues.push_back(tumor_size);
    attributesValues.push_back(inv_nodes);
    attributesValues.push_back(node_caps);
    attributesValues.push_back(deg_malig);
    attributesValues.push_back(breast);
    attributesValues.push_back(breast_quad);
    attributesValues.push_back(irradiat);
}

#endif