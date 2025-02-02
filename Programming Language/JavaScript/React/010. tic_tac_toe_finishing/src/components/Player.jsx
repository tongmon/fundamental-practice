import { useState } from "react";

export function Player({ initialName, symbol, isActive, onChangeName }) {
  const [playerName, setPlayerName] = useState(initialName); // 플레이어 이름을 기억할 이벤트
  const [isEditing, setIsEditing] = useState(false);

  // input 태그의 onChange 이벤트에서는 event 객체를 인자로 받아올 수 있다.
  // 따라서 onChange 이벤트에 넘겨줄 함수 포인터는 이벤트 객체를 받아와 활용이 가능하다.
  function handleChange(event) {
    setPlayerName(event.target.value);
  }

  function handleEditClick() {
    setIsEditing((editing) => !editing);

    if (isEditing) {
      onChangeName(symbol, playerName);
    }
  }

  let editablePlayerName = <span className="player-name">{playerName}</span>;
  if (isEditing) {
    editablePlayerName = (
      // 밑은 양방향 바인딩의 예시로 input 필드에 데이터가 입력될 때마다 onChange 이벤트가 발생하고
      // 해당 이벤트 핸들러인 handleChange 함수가 호출되어 playerName이 변경되고 이렇게 변경된 playerName이 input 필드에 반영된다.
      // 즉 입력이 바뀔 때마다 playerName이 변경되고 playerName이 변경될 때마다 input 필드에 반영되는 양방향 바인딩이다.
      <input type="text" required value={playerName} onChange={handleChange} />
    );
  }

  return (
    <li className={isActive ? "active" : undefined}>
      <span className="player">
        {editablePlayerName}
        <span className="player-symbol">{symbol}</span>
      </span>
      <button onClick={handleEditClick}>{isEditing ? "Save" : "Edit"}</button>
    </li>
  );
}
