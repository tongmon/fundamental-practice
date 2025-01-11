/*
export function TabButton(props) {
  // 리액트에서 이벤트 핸들러 함수를 구축하는 법은 밑과 같다.
  // 구축한 함수 포인터를 <button> 요소의 onClick 속성에 할당하면 해당 버튼을 클릭했을 때 함수가 실행된다.
  // 모든 html 요소에는 on으로 시작하는 다양한 이벤트 핸들러 속성이 있으며 intelisense를 통해 확인할 수 있다.
  function handleClick() {
    console.log("Hello, world!");
  }

  return (
    <li>
      {
        // 밑과 같이 props.children이라는 builtin 속성을 사용하여 컴포넌트의 자식 요소를 렌더링할 수 있다.
        // 자식 요소는 예를 들어 <TabButtons>Children Props</TabButtons> 에서 Children Props라고 할 수 있다.
        // 'Children Props'와 같은 간단한 문자열일 수도 있고 복잡한 html 계층일 수도 있다.
      }
      <button onClick={handleClick}>{props.children}</button>
    </li>
  );
}
*/

// 밑과 같이 외부에서 onSelect 함수를 props로 받아서 사용할 수도 있다.
// onSelect 이름의 이벤트는 리액트에 이미 정의되어 있지만 여기에서는 사용자 정의 함수로 쓰인다.
export function TabButton({ children, onSelect }) {
  return (
    <li>
      <button onClick={onSelect}>{children}</button>
    </li>
  );
}
