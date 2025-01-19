// 밑과 같이 외부에서 onSelect 함수를 props로 받아서 사용할 수도 있다.
// onSelect 이름의 이벤트는 리액트에 이미 정의되어 있지만 여기에서는 사용자 정의 함수로 쓰인다.
export function TabButton({ children, onSelect, isSelected }) {
  return (
    <li>
      {
        // isSelected가 true일 때 버튼이 선택되었다는 효과를 주기위해 active 클래스를 추가한다.
        // active 클래스는 index.css의 button.active에 의해 색상이 변경된다.
        // 즉 className은 css 파일의 클래스 이름을 참조하는 것이다.
      }
      <button className={isSelected ? "active" : undefined} onClick={onSelect}>
        {children}
      </button>
    </li>
  );
}
