import React from 'react'
import "./Statistics.css"

const Statistics = ({ state, reset, jumpTo }) => {
    const moves = state.history.map((move, i) => {
        
    const desc = i ? "Go to move #" + i : "Go to game start";

      let active = "";
      if (move.active) {
        active = "active";
      } else {
        active = "normal";
      }
      return (
        <li key={i}>
          <button
            className={active}
            key={`${move.location.col}_${move.location.row}`}
            onClick={() => jumpTo(i)}
          >
            {`${desc} (${move.location.row}, ${move.location.col})`}
          </button>
        </li>
      );
    })
    
    return (
        <div className="statistics">
        {state.result && <div className="stats">{state.result.status === "win" ? "WIN" : "Draw"}<br></br><button onClick={reset} className="stats">Play again</button></div>}
        {state.result && state.result.status === "win" && <div className="stats">Winner: {state.result.win.player}</div>}
        {!state.result && <div className="stats">Turn player: {state.xIsNext ? "X" : "O"}</div>}
        <ol>{moves}</ol>
        
        </div>
    )
}

export default Statistics
