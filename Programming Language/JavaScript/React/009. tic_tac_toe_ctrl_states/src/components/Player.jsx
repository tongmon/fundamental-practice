import { useState } from "react";

export function Player({ name, symbol }) {
  const [isEditing, setIsEditing] = useState(false);

  function handleEditClick() {
    // 밑 방식은 isEditing의 값을 실시간으로 변경 및 반영하지 않기에 React에서 권장하는 방식이 아니다.
    // 아무리 isEditing 값이 바뀌어도 항상 이전 값을 참조하게 되고 handleEditClick 함수를 벗어나야 다음 값을 참조할 수 있다.
    // setIsEditing(!isEditing);
    // 즉 setIsEditing(!isEditing);를 여러번 호출해도 setIsEditing(!isEditing);를 한 번 호출한 것과 같은 결과를 가져온다.

    // 따라서 아래와 같이 함수를 사용하여 이전 값을 참조하지만 실시간 반영이 되도록 한다.
    // 현재 값을 계속해서 변경할 수 있기에 개발자가 의도한 대로 동작한다.
    setIsEditing((editing) => !editing);
  }

  let playerName = <span className="player-name">{name}</span>;
  if (isEditing) {
    playerName = <input type="text" required value={name} />;
  }

  return (
    <li>
      <span className="player">
        {playerName}
        <span className="player-symbol">{symbol}</span>
      </span>
      <button onClick={handleEditClick}>{isEditing ? "Save" : "Edit"}</button>
    </li>
  );
}
