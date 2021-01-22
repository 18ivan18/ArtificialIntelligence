import React from 'react'
import Circle from './Circle'

const Board = ({ graph }) => {
    return (
        <div className="rect">
            {graph.V().map(vertex => <Circle></Circle>)}
        </div>
    )
}

export default Board
