import { useState } from "react";

import { CoreConcepts } from "./components/CoreConcepts";
import { Header } from "./components/Header";
import { TabButton } from "./components/TabButton";
import { CORE_CONCEPTS, EXAMPLES } from "./data";

function App() {
  // 해당 훅의 default 값은 undefined이다.
  const [selectedTopic, setSelectedTopic] = useState();

  function handleSelect(selectedButton) {
    setSelectedTopic(selectedButton);
  }

  /*
  let tabContent = <p>Please select a topic</p>;
  if (selectedTopic) {
    tabContent = (
      <div id="tab-content">
        <h3>{EXAMPLES[selectedTopic].title}</h3>
        <p>{EXAMPLES[selectedTopic].description}</p>
        <pre>
          <code>{EXAMPLES[selectedTopic].code}</code>
        </pre>
      </div>
    );
  }
  
  // 위 코드에서 tabContent는 아래 코드를 축약한 것이다.
  // 따라서 {tabContent}를 사용한다면 같은 효과를 누릴 수 있다.
  {!selectedTopic ? (
    <p>Select a topic to a topic</p>
  ) : (
    <div id="tab-content">
      <h3>{EXAMPLES[selectedTopic].title}</h3>
      <p>{EXAMPLES[selectedTopic].description}</p>
      <pre>
        <code>{EXAMPLES[selectedTopic].code}</code>
      </pre>
    </div>
  )}
  */

  return (
    <div>
      <Header />
      <main>
        <section id="core-concepts">
          <h2>Core Concepts</h2>
          <ul>
            {
              // <CoreConcepts {...CORE_CONCEPTS[0]} />
              // <CoreConcepts {...CORE_CONCEPTS[1]} />
              // <CoreConcepts {...CORE_CONCEPTS[2]} />
              // <CoreConcepts {...CORE_CONCEPTS[3]} />
              // 위 코드를 배열 순회로 개선하면 밑과 같다.
              // key는 각각의 컴포넌트를 식별하기 위해 사용하게 되는 고유 값이다.
              // 해당 고유 값을 통해 리액트는 내부 상태를 최적화하기에 key를 적지 않으면 경고가 발생한다.
              CORE_CONCEPTS.map((concept) => (
                <CoreConcepts key={concept.title} {...concept} />
              ))
            }
          </ul>
        </section>
        <section id="examples">
          <h2>Examples</h2>
          <menu>
            <TabButton
              isSelected={selectedTopic === "components"}
              onSelect={() => handleSelect("components")}
            >
              Components
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "jsx"}
              onSelect={() => handleSelect("jsx")}
            >
              JSX
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "props"}
              onSelect={() => handleSelect("props")}
            >
              Props
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "state"}
              onSelect={() => handleSelect("state")}
            >
              State
            </TabButton>
          </menu>
          {
            // 밑 구문을 통해 selectedTopic의 초기값이 undefined인 경우 <p>Select a topic to a topic</p>을 출력하여 에러를 방지한다.
            // selectedTopic이 선택되면 EXAMPLES[selectedTopic]을 통해 선택된 토픽에 대한 정보를 출력한다.
          }
          {!selectedTopic ? (
            <p>Select a topic to a topic</p>
          ) : (
            <div id="tab-content">
              <h3>{EXAMPLES[selectedTopic].title}</h3>
              <p>{EXAMPLES[selectedTopic].description}</p>
              <pre>
                <code>{EXAMPLES[selectedTopic].code}</code>
              </pre>
            </div>
          )}
        </section>
      </main>
    </div>
  );
}

export default App;
