export function GameOver({ winner, onRestart }) {
  return (
    <div id="game-over">
      <h2>Game Over!</h2>
      {winner && <p>{winner} won!</p>}
      {
        // '를 출력하기 위해 &apos;를 사용하였다.
        !winner && <p>It&apos;s a draw!</p>
      }
      <p>
        <button onClick={onRestart}>Rematch!</button>
      </p>
    </div>
  );
}
