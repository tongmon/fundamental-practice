import { Player } from "./components/Player";

function App() {
  return (
    <main>
      <div id="game-container">
        <ol id="players">
          {
            // 당연하게도 밑의 두 Player 컴포넌트는 서로 공유되는 값이 없이 독립적으로 동작한다.
            // 따라서 두 컴포넌트는 서로 영향을 주지 않고 코드가 꼬일 일이 없다.
          }
          <Player name="Player 1" symbol="X" />
          <Player name="Player 2" symbol="O" />
        </ol>
      </div>
    </main>
  );
}

export default App;
