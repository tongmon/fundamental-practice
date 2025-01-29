export function Log({ turns }) {
  return (
    <ol id="log">
      {turns.map((turn) => (
        // li 태그에는 항상 key 값이 존재해야 한다는 것을 명심하자.
        <li key={turn.square.row * 10 + turn.square.col}>
          {turn.player} selected {turn.square.row}, {turn.square.col}
        </li>
      ))}
    </ol>
  );
}
