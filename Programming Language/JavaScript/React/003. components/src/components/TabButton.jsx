export function TabButton(props) {
  return (
    <li>
      {/* 밑과 같이 props.children이라는 builtin 속성을 사용하여 컴포넌트의 자식 요소를 렌더링할 수 있다. */
      /* 자식 요소는 예를 들어 <TabButtons>Children Props</TabButtons> 에서 Children Props라고 할 수 있다. */
      /* 위와 같은 간단한 문자열일 수도 있고 복잡한 html 계층일 수도 있다. */}
      <button>{props.children}</button>
    </li>
  );
}
