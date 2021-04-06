import React from "react";
import Square from "./Square";
import "./Board.css";

const Board = ({ board, updateBoard, reset, winningSquares }) => {
  const highlightSquare = (i, j) => {
    let result = "square";
    if (winningSquares.length > 0) {
      winningSquares.forEach((element) => {
        if (element.x === i && element.y === j) {
          result = "square winningSquare";
        }
      });
    }
    return result;
  };

  const generateRow = (col, row) => {
    return col.map((sq, i) => (
      <Square
        key={i}
        highlightWinSquares={highlightSquare(row, i)}
        value={sq}
        updateStateOnClick={() => updateBoard(row, i)}
      ></Square>
    ));
  };

  const generateBoard = (board) => {
    return board.squares.map((row, i) => (
      <div className="row" key={i}>
        {" "}
        {generateRow(row, i)}
      </div>
    ));
  };

  return (
    <div>
      <div className="board">
        {generateBoard(board)}
        <div className="btnCountainer">
          <button className="btn" onClick={reset}>
            Reset
          </button>
        </div>
      </div>
    </div>
  );
};

export default Board;
