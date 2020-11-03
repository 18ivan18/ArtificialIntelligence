#ifndef STATE
#define STATE
#include "Board.cpp"
#include <vector>

class State
{
private:
    Board *board;
    // State *prevState;
    MOVE moveFromPrevState;

public:
    State(Board * /*, State **/, MOVE);
    std::vector<State *> moves();
    Board *getBoard() const;
    State *getPreviousState() const;

    ~State();
};
#endif
