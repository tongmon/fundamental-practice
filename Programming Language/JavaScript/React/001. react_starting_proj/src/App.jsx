// 리액트는 밑과 같이 자바스크립트 코드 내부에 HTML 코드를 작성할 수 있게 해준다.
// 컴포넌트는 리액트 앱의 구성 요소로 함수 형태이다.
// 리액트는 프론트 엔드 라이브러리인 만큼 모든 컴포넌트는 사용자에게 보여지는 화면을 구성하는데 사용된다.
// 리액트에서 지켜야할 핵심적인 것 두 가지가 있다.
// 1. 컴포넌트의 이름은 반드시 대문자로 시작해야 한다.
// 2. 컴포넌트는 반드시 렌더링이 가능한 것(HTML 등)을 반환해야 한다.

// 리액트에서 이미지를 사용할 때는 이미지를 import하여 사용하는 것이 좋다.
import reactImg from "./assets/react-core-concepts.png";

const reactDescriptions = ["Fundamental", "Crucial", "Core"];

function getRandomInt(max) {
  return Math.floor(Math.random() * (max + 1));
}

function Header() {
  return (
    <header>
      {/* 이미지를 밑과 같이 임포트할 수도 있지만 비효율적이다. */
      /*<img src="src/assets/react-core-concepts.png" alt="Stylized atom" />*/
      /* 이미지를 밑과 같이 임포트하여 사용하면 리액트에서 이미지 최적화를 사용할 수 있다. */}
      <img src={reactImg} alt="Stylized atom" />
      <h1>React Essentials</h1>
      <p>
        {/* 밑과 같이 jsx에서 '{}'로 감싼 부분을 사용하여 자바스크립트 코드를 동적으로 html에 넣을 수 있다. */
        /* 함수 정의나 if문, for문과 같은 복잡한 로직은 넣지 못하나 호출이나 산술 연산 정도는 가능하다. */
        /* 밑의 코드는 reactDescriptions 배열의 요소 중 하나를 랜덤으로 선택하여 반환하여 페이지 새로 고침을 할 때마다 글자가 달라진다. */}
        {reactDescriptions[getRandomInt(2)]} Fundamental React concepts you will
        need for almost any app you are going to build!
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
