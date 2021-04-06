import Board from "./components/Board";
import Statistics from "./components/Statistics";
import { useState, useEffect } from "react";
import {
  calculateWinner,
  findBestMove,
} from "./minimax_alpha_beta_pruning/minimax";
import "./App.css";

const App = () => {
  const initialize = () => {
    return {
      history: [
        {
          squares: Array(3)
            .fill()
            .map(() => Array(3).fill(null)),
          location: {
            col: 0,
            row: 0,
          },
          active: true,
          moveNumber: 0,
        },
      ],
      xIsNext: true,
      stepNumber: 0,
      result: null,
    };
  };

  const reset = () => {
    setState(initialize());
  };

  const jumpTo = (i) => {
    let history = state.history;
    history.forEach((item) => (item.active = false));
    history[i].active = true;
    setState({
      history,
      stepNumber: i,
      xIsNext: i % 2 === 0,
      result: calculateWinner(history[i].squares),
    });
  };

  // const generateComputerMove = (squares) => {
  //   let possibleMoves = [];
  //   squares.forEach((row, i) => row.forEach((sq, j) => {if(sq === null) possibleMoves.push({x: i, y: j})}));
  //   return possibleMoves[parseInt(possibleMoves.length * Math.random())] || null;
  // }

  const handleClick = (i, j) => {
    const history = state.history.slice(0, state.stepNumber + 1);
    const current = history[history.length - 1];
    // const squares = current.squares.slice(); // doesn't work!??

    // obv works
    const squares = Array(3)
      .fill()
      .map(() => Array(3).fill(null));
    for (let i = 0; i < 3; i++) {
      for (let j = 0; j < 3; j++) {
        squares[i][j] = current.squares[i][j];
      }
    }

    if (calculateWinner(squares) || squares[i][j]) {
      return;
    }

    squares[i][j] = state.xIsNext ? "X" : "O";
    history[state.stepNumber].active = false;
    setState((prevState) => ({
      history: history.concat([
        {
          squares,
          location: {
            row: i + 1,
            col: j + 1,
          },
          active: true,
          moveNumber: history.length,
        },
      ]),
      xIsNext: !prevState.xIsNext,
      stepNumber: history.length,
      result: calculateWinner(squares),
    }));
  };

  const [state, setState] = useState(initialize());
  useEffect(
    () => {
      if (
        !state.xIsNext &&
        !state.result &&
        state.history.length - 1 === state.stepNumber
      ) {
        // const computerMove = generateComputerMove(state.history[state.stepNumber].squares);
        const computerMove = findBestMove(
          state.history[state.stepNumber].squares,
          false
        );
        handleClick(computerMove.x, computerMove.y);
      }
    }, // eslint-disable-next-line
    [state.xIsNext, state.history, state.stepNumber]
  );

  const getCurrent = () => {
    return state.history[state.stepNumber];
  };

  return (
    <div className="App">
      <Board
        board={getCurrent()}
        reset={() => reset()}
        updateBoard={(i, j) => handleClick(i, j)}
        winningSquares={
          state.result && state.result.status === "win"
            ? state.result.win.squares
            : []
        }
      ></Board>
      <Statistics
        state={state}
        setState={setState}
        jumpTo={jumpTo}
        reset={() => reset()}
      ></Statistics>
    </div>
  );
};

export default App;
