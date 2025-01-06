import reactImg from "../assets/react-core-concepts.png";

// CSS 파일도 컴포넌트와 같이 분리하여 밑과 같이 임포트해 사용하는 것이 리액트에서는 일반적이다.
// 하지만 이렇게 CSS 파일이 분리되었다고 해서 해당 CSS 파일이 임포트한 컴포넌트에만 적용되는 것은 아니다.
// 예를 들어 지금 이 파일에서 임포트한 Header CSS는 이 파일에서만 임포트되고 있지만 전체 애플리케이션에 적용된다.
import "./Header.css";

const reactDescriptions = ["Fundamental", "Crucial", "Core"];

function getRandomInt(max) {
  return Math.floor(Math.random() * (max + 1));
}

// 해당 컴포넌트를 다른 곳에서 사용하기 위해 export 키워드를 사용한다.
export function Header() {
  return (
    <header>
      <img src={reactImg} alt="Stylized atom" />
      <h1>React Essentials</h1>
      <p>
        {reactDescriptions[getRandomInt(2)]} Fundamental React concepts you will
        need for almost any app you are going to build!
      </p>
    </header>
  );
}
