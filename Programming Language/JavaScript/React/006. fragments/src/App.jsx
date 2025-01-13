// 부모 요소로 감싸지 않아도 되는 Fragment를 import 한다.
import { useState, Fragment } from "react";

import { CORE_CONCEPTS } from "./data.js";
import Header from "./components/Header/Header.jsx";
import CoreConcept from "./components/CoreConcept.jsx";
import TabButton from "./components/TabButton.jsx";
import { EXAMPLES } from "./data.js";

function App() {
  const [selectedTopic, setSelectedTopic] = useState();

  function handleSelect(selectedButton) {
    // selectedButton => 'components', 'jsx', 'props', 'state'
    setSelectedTopic(selectedButton);
    // console.log(selectedTopic);
  }

  console.log("APP COMPONENT EXECUTING");

  let tabContent = <p>Please select a topic.</p>;

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

  return (
    // JavaScript에서 함수는 단 하나의 값만 반환할 수 있다.
    // 따라서, 여러 개의 JSX 요소를 반환하려면 하나의 부모 요소(밑에선 '<div>')로 감싸야 한다.
    // 하지만 이는 불필요한 div 요소를 추가하는 것이고 Dom 구조를 복잡하게 만든다.
    // <div>
    //   <Header />
    //   <main></main>
    // </div>

    // 따라서 밑과 같이 Fragment를 사용하면 부모 요소로 감싸지 않아도 된다.
    // <Fragment>
    //   <Header />
    //   <main></main>
    // </Fragment>

    // 최신의 React 버전에서는 Fragment 대신 밑 처럼 빈 태그(<></>)를 사용할 수 있다.
    // 해당 방식은 Fragment를 따로 import 하지 않아도 되고 더 간결하기에 추천된다.
    <>
      <Header />
      <main>
        <section id="core-concepts">
          <h2>Core Concepts</h2>
          <ul>
            {CORE_CONCEPTS.map((conceptItem) => (
              <CoreConcept key={conceptItem.title} {...conceptItem} />
            ))}
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
          {tabContent}
        </section>
      </main>
    </>
  );
}

export default App;
