import { useState } from "react";

export function Player({ initialName, symbol }) {
  const [playerName, setPlayerName] = useState(initialName); // 플레이어 이름을 기억할 이벤트
  const [isEditing, setIsEditing] = useState(false);

  // input 태그의 onChange 이벤트에서는 event 객체를 인자로 받아올 수 있다.
  // 따라서 onChange 이벤트에 넘겨줄 함수 포인터는 이벤트 객체를 받아와 활용이 가능하다.
  function handleChange(event) {
    setPlayerName(event.target.value);
  }

  function handleEditClick() {
    // 밑 방식은 isEditing의 값을 실시간으로 변경 및 반영하지 않기에 React에서 권장하는 방식이 아니다.
    // 아무리 isEditing 값이 바뀌어도 항상 이전 값을 참조하게 되고 handleEditClick 함수를 벗어나야 다음 값을 참조할 수 있다.
    // setIsEditing(!isEditing);
    // 즉 setIsEditing(!isEditing);를 여러번 호출해도 setIsEditing(!isEditing);를 한 번 호출한 것과 같은 결과를 가져온다.

    // 따라서 아래와 같이 함수를 사용하여 이전 값을 참조하지만 실시간 반영이 되도록 한다.
    // 현재 값을 계속해서 변경할 수 있기에 개발자가 의도한 대로 동작한다.
    setIsEditing((editing) => !editing);
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
    <li>
      <span className="player">
        {editablePlayerName}
        <span className="player-symbol">{symbol}</span>
      </span>
      <button onClick={handleEditClick}>{isEditing ? "Save" : "Edit"}</button>
    </li>
  );
}
