// 리액트는 밑과 같이 자바스크립트 코드 내부에 HTML 코드를 작성할 수 있게 해준다.
// 컴포넌트는 리액트 앱의 구성 요소로 함수 형태이다.
// 리액트는 프론트 엔드 라이브러리인 만큼 모든 컴포넌트는 사용자에게 보여지는 화면을 구성하는데 사용된다.
// 리액트에서 지켜야할 핵심적인 것 두 가지가 있다.
// 1. 컴포넌트의 이름은 반드시 대문자로 시작해야 한다.
// 2. 컴포넌트는 반드시 렌더링이 가능한 것(HTML 등)을 반환해야 한다.

function Header() {
  return (
    <header>
      <img src="src/assets/react-core-concepts.png" alt="Stylized atom" />
      <h1>React Essentials</h1>
      <p>
        Fundamental React concepts you will need for almost any app you are
        going to build!
      </p>
    </header>
  );
}

function App() {
  return (
    <div>
      {/* 위에서 정의한 Header 컴포넌트를 호출할 때는 밑과 같이 HTML 형태로 선언한다. */}
      <Header />
      <main>
        <h2>Time to get started!</h2>
      </main>
    </div>
  );
}

export default App;
