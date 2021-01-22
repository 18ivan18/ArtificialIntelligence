#ifndef SOLVER
#define SOLVER
#include <string>
#include <vector>
using std::string;
using std::vector;

class Solver
{
private:
    const int DEFAULT_FOLD = 5;
    std::vector<std::string> split(std::string &, const std::string &);
    vector<vector<string>> input;
    int fold;
    void readInput(const string &);
    vector<int> getShuffledIndexes(int);
    double fractionToPercentage(double);

public:
    Solver(const string &);
    void setFold(int);
    void solve();
    ~Solver();
};

#endif
