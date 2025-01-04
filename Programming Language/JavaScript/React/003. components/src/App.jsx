// 리액트 프로젝트에서는 하나의 파일에 여러 컴포넌트를 정의하는 일은 거의 없다.
// 보통 components 폴더를 만들어 그 안에 컴포넌트를 정의하고, App.jsx에서 해당 컴포넌트를 임포트하여 사용한다.

import { CoreConcepts } from "./components/CoreConcepts";
import { Header } from "./components/Header";
import { TabButton } from "./components/TabButton";
import { CORE_CONCEPTS } from "./data";

function App() {
  return (
    <div>
      <Header />
      <main>
        <section id="core-concepts">
          <h2>Core Concepts</h2>
          <ul>
            <CoreConcepts {...CORE_CONCEPTS[0]} />
            <CoreConcepts {...CORE_CONCEPTS[1]} />
            <CoreConcepts {...CORE_CONCEPTS[2]} />
            <CoreConcepts {...CORE_CONCEPTS[3]} />
          </ul>
        </section>
        <section id="examples">
          <h2>Examples</h2>
          <menu>
            {/* 밑과 같이 리액트의 builtin property인 children을 이용한 방식을 사용하여 TabButton 컴포넌트를 사용할 수 있다. */
            /* 밑 방식과 CoreConcepts 컴포넌트에 쓰인 방식 모두 알아야 유연하게 리액트를 사용할 수 있다. */}
            <TabButton>Components</TabButton>
            <TabButton>JSX</TabButton>
            <TabButton>Props</TabButton>
            <TabButton>State</TabButton>
          </menu>
        </section>
      </main>
    </div>
  );
}

export default App;
