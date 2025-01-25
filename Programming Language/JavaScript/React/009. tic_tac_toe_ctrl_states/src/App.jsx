import { useState } from "react";
import { Player } from "./components/Player";
import { GameBoard } from "./components/GameBoard";

function App() {
  // Player와 GameBoard를 연결하는 상태를 만들기위해 상위 컴포넌트인 App 컴포넌트에서 상태를 만들어서 하위 컴포넌트에 전달한다.
  // 이를 상태 끌어올리기(lifting state up)라고 한다.
  const [activePlayer, setActivePlayer] = useState("X");

  // 게임 보드를 클릭할 때마다 플레이어를 교체하는 함수
  function handleSelectSquare() {
    setActivePlayer((prevActivePlayer) => {
      return prevActivePlayer === "X" ? "O" : "X";
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
        <GameBoard
          onSelectSquare={handleSelectSquare}
          activePlayerSymbol={activePlayer}
        />
      </div>
    </main>
  );
}

export default App;
