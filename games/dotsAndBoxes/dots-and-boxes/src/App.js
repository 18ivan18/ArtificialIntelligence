import React, { useState } from 'react'
import Board from './components/Board'
import Menu from './components/Menu'
import { Graph } from './logic/Graph'

const App = () => {
  const [board, setBoard] = useState(new Graph());
  return (
    <div>
      <Menu></Menu>
      <Board graph={board}></Board>
    </div>
  )
}

export default App

