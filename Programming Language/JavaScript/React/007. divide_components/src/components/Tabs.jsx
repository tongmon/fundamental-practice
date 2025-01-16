// Tabs 컴포넌트를 만들어 코드 관리를 더 쉽게 만들 수 있다.
export function Tabs({ children, buttons, buttonsContainer }) {
  // buttonsContainer에 넘겨진 값을 태그로 사용하기 위해서는 상수를 한 번 거치게 하는 방법이 있다.
  // 밑 상수는 첫 글자가 대문자인 것이 중요하다.
  // 그렇게 해야 리액트가 props를 태그로 인식한다.
  // 위 방식을 안쓰고 그냥 buttonsContainer 이름의 prop을 ButtonContainer로 바꾸면 상수를 따로 정의 안하고도 props를 태그로 사용할 수 있다.
  // 중요한 건 첫 글자가 대문자인 것이다.
  const ButtonContainer = buttonsContainer;

  return (
    <>
      <ButtonContainer>{buttons}</ButtonContainer>
      {children}
    </>
  );
}
