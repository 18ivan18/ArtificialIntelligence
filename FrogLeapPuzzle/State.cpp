#include "State.h"

// State *State::getPreviousState() const
// {
//     return prevState;
// }

State::State(Board *board /*, State *prev*/, MOVE move) : board(board) /*, prevState(prev)*/, moveFromPrevState(move)
{
}

State::~State()
{
    delete board;
    // delete prevState;
}

std::vector<State *> State::moves()
{
    std::vector<State *> moves;
    int indexOfEmpty = board->getIndexOfEmpty();
    if (indexOfEmpty > 0 && board->getBoard()[indexOfEmpty - 1] == TILE::BROWN_FROG)
    {
        // std::cout << "Jump right on empty space\n";
        TILE *temp = new TILE[board->getSize()];
        for (int i = 0; i < board->getSize(); i++)
        {
            temp[i] = board->getBoard()[i];
        }
        temp[indexOfEmpty] = TILE::BROWN_FROG;
        temp[indexOfEmpty - 1] = TILE::EMPTY;
        // moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty - 1), this, MOVE::JUMP_RIGHT));
        moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty - 1), MOVE::JUMP_RIGHT));
    }

    if (indexOfEmpty > 1 && board->getBoard()[indexOfEmpty - 1] != TILE::EMPTY && board->getBoard()[indexOfEmpty - 2] == TILE::BROWN_FROG)
    {
        // std::cout << "Jump right over a frog\n";
        TILE *temp = new TILE[board->getSize()];
        for (int i = 0; i < board->getSize(); i++)
        {
            temp[i] = board->getBoard()[i];
        }
        temp[indexOfEmpty] = TILE::BROWN_FROG;
        temp[indexOfEmpty - 2] = TILE::EMPTY;
        // moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty - 2), this, MOVE::DOUBL_JUMP_RIGHT));
        moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty - 2), MOVE::DOUBL_JUMP_RIGHT));
    }

    if (indexOfEmpty < board->getSize() - 1 && board->getBoard()[indexOfEmpty + 1] == TILE::GREEN_FROG)
    {
        // std::cout << "Jump left on empty space\n";
        TILE *temp = new TILE[board->getSize()];
        for (int i = 0; i < board->getSize(); i++)
        {
            temp[i] = board->getBoard()[i];
        }
        temp[indexOfEmpty] = TILE::GREEN_FROG;
        temp[indexOfEmpty + 1] = TILE::EMPTY;
        // moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty + 1), this, MOVE::JUMP_LEFT));
        moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty + 1), MOVE::JUMP_LEFT));
    }

    if (indexOfEmpty < board->getSize() - 2 && board->getBoard()[indexOfEmpty + 1] != TILE::EMPTY && board->getBoard()[indexOfEmpty + 2] == TILE::GREEN_FROG)
    {
        // std::cout << "Jump left over a frog\n";
        TILE *temp = new TILE[board->getSize()];
        for (int i = 0; i < board->getSize(); i++)
        {
            temp[i] = board->getBoard()[i];
        }
        temp[indexOfEmpty] = TILE::GREEN_FROG;
        temp[indexOfEmpty + 2] = TILE::EMPTY;
        // moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty + 2), this, MOVE::DOUBLE_JUMP_LEFT));
        moves.push_back(new State(new Board(temp, board->getSize(), indexOfEmpty + 2), MOVE::DOUBLE_JUMP_LEFT));
    }
    return moves;
}

Board *State::getBoard() const
{
    return board;
}
