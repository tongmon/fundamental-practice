import componentsImg from "./assets/components.png";
import reactImg from "./assets/react-core-concepts.png";
import { CORE_CONCEPTS } from "./data";

const reactDescriptions = ["Fundamental", "Crucial", "Core"];

function getRandomInt(max) {
  return Math.floor(Math.random() * (max + 1));
}

function Header() {
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

// 밑과 같이 props를 사용하여 각 컴포넌트에 각기 다른 데이터를 전달할 수 있다.
// prop은 js의 객체 형태로 전달된다.
function CoreConcepts(prop) {
  return (
    <li>
      <img src={prop.image} alt={prop.title} />
      <h3>{prop.title}</h3>
      <p>{prop.description}</p>
    </li>
  );
}

/* 밑과 같이 자바스크립트의 구조 분해 할당을 이용하여 props를 사용할 수도 있다. 
해당 방식의 장점은 코드가 간결해지고 props에 default 값을 설정할 수 있다는 것이다.
function CoreConcepts({ title, description, image = null }) {
  return (
    <li>
      <img src={image} alt={title} />
      <h3>{title}</h3>
      <p>{description}</p>
    </li>
  );
}
*/

function App() {
  return (
    <div>
      <Header />
      <main>
        <section id="core-concepts">
          <h2>Core Concepts</h2>
          <ul>
            {/* 밑과 같이 여러 인자들을 prop 객체를 통해 전달할 수 있다. */}
            <CoreConcepts
              title="Components"
              description="The core UI building block."
              image={componentsImg}
            />

            {/* 위와 같이 하드 코팅으로 써줄 수도 있겠지만 밑과 같이 변수를 임포트하여 사용하는 것이 좋다. */}
            <CoreConcepts
              title={CORE_CONCEPTS[1].title}
              description={CORE_CONCEPTS[1].description}
              image={CORE_CONCEPTS[1].image}
            />

            {/* 더 간단하게 밑과 같이 Spread 연산자를 이용하여 전달할 수도 있다. */}
            <CoreConcepts {...CORE_CONCEPTS[2]} />
            <CoreConcepts {...CORE_CONCEPTS[3]} />
          </ul>
        </section>
      </main>
    </div>
  );
}

export default App;
