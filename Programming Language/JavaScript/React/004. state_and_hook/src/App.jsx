// 리액트에서 use로 시작하는 파일은 훅(Hook)을 정의한 파일이다.
import { useState } from "react";

import { CoreConcepts } from "./components/CoreConcepts";
import { Header } from "./components/Header";
import { TabButton } from "./components/TabButton";
import { CORE_CONCEPTS, EXAMPLES } from "./data";

// index.jsx를 보면 알겠지만 밑 App() 컴포넌트는 단 한 번만 렌더링된다.
// 하지만 특정 상황에서는 App() 렌더링을 여러 번 수행해야 하는데 이때 상태(state)와 훅(Hook)을 사용한다.
function App() {
  // 밑과 같이 Hook은 컴포넌트 최상위에서만 호출해야 한다.
  // 컴포넌트 밖에서나 handleSelect과 같은 컴포넌트 내부 함수에서 호출하면 안된다.
  // useState 함수는 배열을 반환하며 첫 번째 요소는 상태 값이고 두 번째 요소는 상태 값을 변경하는 리액트 함수이다.
  // selectedTopic의 초기값은 "components"이다.
  const [selectedTopic, setSelectedTopic] = useState("components");

  function handleSelect(selectedButton) {
    // 상태 값을 변경하는 리액트 함수를 호출하여 상태 값을 변경한다.
    // 그러면 변경된 상태 값이 selectedTopic에 저장된다.
    setSelectedTopic(selectedButton);

    // 주의할 점은 해당 함수 내부에서 selectedTopic 값을 변경하더라도 selectedTopic 값이 바로 변경되지 않는다는 것이다.
    // 이러한 이유는 호출 순서가 밑과 같기 때문이다.
    // handleSelect() 시작 -> setSelectedTopic() 수행 -> handleSelect() 종료 -> selectedTopic 값 변경 -> App() 재렌더링
    // 따라서 `setSelectedTopic(selectedButton);` 이후에 selectedTopic 값을 사용해도 과거 호출 시점의 값이 사용된다.
  }

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
            <TabButton onSelect={() => handleSelect("components")}>
              Components
            </TabButton>
            <TabButton onSelect={() => handleSelect("jsx")}>JSX</TabButton>
            <TabButton onSelect={() => handleSelect("props")}>Props</TabButton>
            <TabButton onSelect={() => handleSelect("state")}>State</TabButton>
          </menu>
          {
            // 밑과 같이 selectedTopic 값이 변경되면 useState 훅에 의해 App() 함수가 재호출되어 렌더링이 다시 수행된다.
            // 따라서 특정 버튼 클릭 시 handleSelect() 함수 내부에서 selectedTopic 값이 변경되어 해당 내용이 실시간 반영된다.
          }
          <div id="tab-content">
            <h3>{EXAMPLES[selectedTopic].title}</h3>
            <p>{EXAMPLES[selectedTopic].description}</p>
            <pre>
              <code>{EXAMPLES[selectedTopic].code}</code>
            </pre>
          </div>
        </section>
      </main>
    </div>
  );
}

export default App;
