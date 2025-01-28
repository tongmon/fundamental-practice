const initialGameBoard = [
  [null, null, null],
  [null, null, null],
  [null, null, null],
];

export function GameBoard({ onSelectSquare, turns }) {
  let gameBoard = initialGameBoard;

  for (const turn of turns) {
    const { square, player } = turn;
    const { row, col } = square;

    gameBoard[row][col] = player;
  }

  // const [gameBoard, setGameBoard] = useState(initialGameBoard);

  //function handleSelectSquare(rowIndex, colIndex) {
  //  setGameBoard((prevGameBoard) => {
  //    // prevGameBoard은 initialGameBoard를 참조하기에 해당 배열을 바로 변경하게 되면 prevGameBoard를 이미 내부적으로 상태 변경 시점에서 사용하고 있는 React와 충돌하여 문제가 발생할 수 있다.
  //    // 따라서 initialGameBoard의 복사본을 만들어서 변경해야 문제가 확실히 발생하지 않는다.
  //    // 밑은 이차원 배열을 깊은 복사하고 있다.
  //    // 깊은 복사이기에 그 속까지 '...' 연산자를 이용해 복사해주고 있다.
  //    const updatedBoard = [
  //      ...prevGameBoard.map((innerArray) => [...innerArray]),
  //    ];
  //    updatedBoard[rowIndex][colIndex] = activePlayerSymbol;
  //    return updatedBoard;
  //  });
  //
  //  onSelectSquare();
  //}

  return (
    <ol id="game-board">
      {gameBoard.map((row, rowIndex) => (
        <li key={rowIndex}>
          <ol>
            {row.map((playerSymbol, colIndex) => (
              <li key={colIndex}>
                <button onClick={() => onSelectSquare(rowIndex, colIndex)}>
                  {playerSymbol}
                </button>
              </li>
            ))}
          </ol>
        </li>
      ))}
    </ol>
  );
}
