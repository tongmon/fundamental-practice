import { useState } from "react";
import { Player } from "./components/Player";
import { GameBoard } from "./components/GameBoard";
import { Log } from "./components/Log";

// gameTurns을 받아 현재 플레이어를 반환하는 함수
function deriveActivePlayer(gameTurns) {
  let currentPlayer = "X";
  if (gameTurns.length > 0 && gameTurns[0].player === "X") {
    currentPlayer = "O";
  }
  return currentPlayer;
}

function App() {
  const [gameTurns, setGameTurns] = useState([]);

  // 기존의 activePlayer 상태를 제거하고 deriveActivePlayer 함수를 통해 현재 플레이어를 도출한다.
  // React 개발에서 상태를 최소화해야 최적화가 이루어진다.
  // 따라서 기존 상태에서 어떻게 다른 상태 변수를 파생시킬 수 있을지를 고민하면서 개발하는 것이 좋다.
  const activePlayer = deriveActivePlayer(gameTurns);

  // 게임 보드를 클릭할 때마다 플레이어를 교체하는 함수
  function handleSelectSquare(rowIndex, colIndex) {
    setGameTurns((prevGameTurns) => {
      let currentPlayer = deriveActivePlayer(prevGameTurns);

      const updatedTurns = [
        { square: { row: rowIndex, col: colIndex }, player: currentPlayer },
        ...prevGameTurns,
      ];

      return updatedTurns;
    });
  }

  return (
    <main>
      <div id="game-container">
        <ol id="players" className="highlight-player">
          {
            // 당연하게도 밑의 두 Player 컴포넌트는 서로 공유되는 값이 없이 독립적으로 동작한다.
            // 따라서 두 컴포넌트는 서로 영향을 주지 않고 코드가 꼬일 일이 없다.
          }
          <Player
            initialName="Player 1"
            symbol="X"
            isActive={activePlayer === "X"}
          />
          <Player
            initialName="Player 2"
            symbol="O"
            isActive={activePlayer === "O"}
          />
        </ol>
        <GameBoard onSelectSquare={handleSelectSquare} turns={gameTurns} />
      </div>
      <Log turns={gameTurns} />
    </main>
  );
}

export default App;
