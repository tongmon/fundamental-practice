import { useState } from "react";
import { Player } from "./components/Player";
import { GameBoard } from "./components/GameBoard";
import { Log } from "./components/Log";

function App() {
  const [gameTurns, setGameTurns] = useState([]);

  // Player와 GameBoard를 연결하는 상태를 만들기위해 상위 컴포넌트인 App 컴포넌트에서 상태를 만들어서 하위 컴포넌트에 전달한다.
  // 이를 상태 끌어올리기(lifting state up)라고 한다.
  const [activePlayer, setActivePlayer] = useState("X");

  // 게임 보드를 클릭할 때마다 플레이어를 교체하는 함수
  function handleSelectSquare(rowIndex, colIndex) {
    setActivePlayer((prevActivePlayer) => {
      return prevActivePlayer === "X" ? "O" : "X";
    });

    setGameTurns((prevGameTurns) => {
      // activePlayer 상태를 사용하지 않는 이유는 이 함수가 호출될 때 이미 activePlayer 상태가 변경되었을 수도 있기 때문이다.
      // setActivePlayer 함수로 인해 React 내부적으로 상태 변경이 이루어지는데 해당 변경이 정확히 언제 이루어지는지 알 수 없기 때문에
      // 밑과 같은 방식으로 현재 플레이 상태를 획득해야 한다.
      let currentPlayer = "X";
      if (prevGameTurns.length > 0 && prevGameTurns[0].player === "X") {
        currentPlayer = "O";
      }

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
