import { useState } from "react";
import { Player } from "./components/Player";
import { GameBoard } from "./components/GameBoard";
import { Log } from "./components/Log";
import { WINNING_COMBINATIONS } from "./winning-combination";
import { GameOver } from "./components/GameOver";

const initialGameBoard = [
  [null, null, null],
  [null, null, null],
  [null, null, null],
];

// gameTurns을 받아 현재 플레이어를 반환하는 함수
function deriveActivePlayer(gameTurns) {
  let currentPlayer = "X";
  if (gameTurns.length > 0 && gameTurns[0].player === "X") {
    currentPlayer = "O";
  }
  return currentPlayer;
}

function App() {
  // Player.jsx에서 사용하는 player 상태를 끌어올리면 여러 개의 문제가 발생할 수 있다.
  // 그 중 제일 큰 문제는 Player의 이름을 바꿀 때마다 App 컴포넌트 전체가 리렌더링되는 문제가 있고 이는 코드 관리의 복잡성을 초래하며 성능을 저하시킨다.
  // 따라서 이런 경우에는 state 하나를 더 추가하여 Player 컴포넌트의 상태를 관리하는 것이 좋다.
  const [players, setPlayers] = useState({
    X: "Player 1",
    O: "Player 2",
  });
  const [gameTurns, setGameTurns] = useState([]);

  // 기존의 activePlayer 상태를 제거하고 deriveActivePlayer 함수를 통해 현재 플레이어를 도출한다.
  // React 개발에서 상태를 최소화해야 최적화가 이루어진다.
  // 따라서 기존 상태에서 어떻게 다른 상태 변수를 파생시킬 수 있을지를 고민하면서 개발하는 것이 좋다.
  const activePlayer = deriveActivePlayer(gameTurns);

  // 그냥 gameBoard = initialGameBoard를 해버리면 gameBoard와 initialGameBoard는 참조 상태가 된다.
  // 이를 방지하기 위해 gameBoard = [...initialGameBoard]를 해주어 gameBoard를 복사해준다.
  let gameBoard = [...initialGameBoard.map((row) => [...row])];

  for (const turn of gameTurns) {
    const { square, player } = turn;
    const { row, col } = square;

    gameBoard[row][col] = player;
  }

  let winner;

  for (const combination of WINNING_COMBINATIONS) {
    winner = gameBoard[combination[0].row][combination[0].col];
    for (const square of combination) {
      const { row, col } = square;
      if (!winner || winner !== gameBoard[row][col]) {
        winner = null;
        break;
      }
    }
    if (winner) {
      break;
    }
  }

  const hasDraw = gameTurns.length === 9 && !winner;

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

  function handleRestart() {
    setGameTurns([]);
  }

  function handlePlayerNameChange(symbol, newName) {
    setPlayers((prevPlayers) => {
      return {
        ...prevPlayers,
        // 밑 방식은 js의 내장 기능으로 동적 키를 사용하는 방식이다.
        // 예를 들어 symbol이 X인 값이 이미 존재하는 경우 X 키의 값을 newName으로 변경하는 것이다.
        [symbol]: newName,
      };
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
        {(winner || hasDraw) && (
          <GameOver winner={winner} onRestart={handleRestart} />
        )}
        <GameBoard onSelectSquare={handleSelectSquare} board={gameBoard} />
      </div>
      <Log turns={gameTurns} />
    </main>
  );
}

export default App;
