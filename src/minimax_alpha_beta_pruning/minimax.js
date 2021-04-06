const MAXIMIZER_VALUE = 'X';
const MINIMIZER_VALUE = 'O';
const EMPTY_CELL = null;
const max = Math.max;
const min = Math.min;

const minimax = (position, depth, alpha, beta, maximizingPlayer) => {
    const result = calculateWinner(position);
    if (depth === 0 || result) {
        return evaluate(result, depth);
    }

    if (maximizingPlayer) {
        let maxEval = -Infinity;
        position.forEach((row, i) => row.forEach((sq, j) => {
            if (sq === EMPTY_CELL) {
                position[i][j] = MAXIMIZER_VALUE;;
                // Call minimax recursively and choose the maximum value
                maxEval = max(maxEval,
                    minimax(position, depth - 1, alpha, beta, false));
                alpha = max(alpha, maxEval);

                // Undo the move
                position[i][j] = EMPTY_CELL;

                if (beta <= alpha) // no need to continue if there is already better option for the minimizer
                {
                    return maxEval;
                }
            }
        }));
        return maxEval;
    }
    let minEval = +Infinity;
    position.forEach((row, i) => row.forEach((sq, j) => {
        if (sq === EMPTY_CELL) {
            position[i][j] = MINIMIZER_VALUE;;
            // Call minimax recursively and choose the maximum value
            minEval = min(minEval,
                minimax(position, depth - 1, alpha, beta, true));
            beta = min(beta, minEval);
            // Undo the move
            position[i][j] = EMPTY_CELL;
            if (beta <= alpha) // no need to continue if there is already better option for the minimizer
            {
                return minEval;
            }
        }
    }));

    return minEval;
}

const findBestMove = (board, maximizingPlayer) => {
    let bestVal = maximizingPlayer ? -Infinity : +Infinity;
    let bestMove = {};

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal value.
    board.forEach((row, i) => row.forEach((sq, j) => {
        if (sq === EMPTY_CELL) {
            // Make the move
            board[i][j] = maximizingPlayer ? MAXIMIZER_VALUE : MINIMIZER_VALUE;
            // Compute evaluation function for this move
            const moveVal = minimax(board, 10, -Infinity, +Infinity, !maximizingPlayer);

            // Undo the move
            board[i][j] = EMPTY_CELL;
            if ((maximizingPlayer && moveVal > bestVal) ||
                (!maximizingPlayer && moveVal < bestVal)) {
                bestMove.x = i;
                bestMove.y = j;
                bestVal = moveVal;
            }
        }
    }))
    return bestMove;
}

const evaluate = (result, depth) => {
    if (result.status === 'win') {
        if (result.win.player === MAXIMIZER_VALUE) {
            return depth;
        }
        if (result.win.player === MINIMIZER_VALUE) {
            return -depth;
        }
    }
    // else it's a draw
    return 0;
}

const winningMoves = [
    [{ x: 0, y: 0 }, { x: 0, y: 1 }, { x: 0, y: 2 }],
    [{ x: 1, y: 0 }, { x: 1, y: 1 }, { x: 1, y: 2 }],
    [{ x: 2, y: 0 }, { x: 2, y: 1 }, { x: 2, y: 2 }],
    [{ x: 0, y: 0 }, { x: 1, y: 1 }, { x: 2, y: 2 }],
    [{ x: 0, y: 1 }, { x: 1, y: 1 }, { x: 2, y: 1 }],
    [{ x: 0, y: 0 }, { x: 1, y: 0 }, { x: 2, y: 0 }],
    [{ x: 0, y: 2 }, { x: 1, y: 2 }, { x: 2, y: 2 }],
    [{ x: 0, y: 2 }, { x: 1, y: 1 }, { x: 2, y: 0 }]
];

const calculateWinner = (squares) => {
    let result = {
        status: "",
        win: {}
    };
    for (let i = 0; i < winningMoves.length; i++) {
        const [a, b, c] = winningMoves[i];
        if (
            squares[a.x][a.y] &&
            squares[a.x][a.y] === squares[b.x][b.y] &&
            squares[a.x][a.y] === squares[c.x][c.y]
        ) {
            result = {
                status: "win",
                win: { player: squares[a.x][a.y], squares: [a, b, c] }
            };
            return result;
        }
    }

    for (let i = 0; i < squares.length; i++) {
        for (let j = 0; j < squares[i].length; j++) {
            if (squares[i][j] === null) {
                return null;
            }
        }
    }
    result.status = "draw";
    return result;
}

export { findBestMove, calculateWinner };