import React from 'react'

const Square = ({highlightWinSquares, value, updateStateOnClick}) => {
    return (
        <div className={highlightWinSquares} onClick={updateStateOnClick}>
            {value}
        </div>
    )
}

export default Square
