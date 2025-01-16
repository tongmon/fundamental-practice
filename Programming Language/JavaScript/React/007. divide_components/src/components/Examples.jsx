import { useState } from "react";
import { TabButton } from "./TabButton";
import { Section } from "./Section";
import { Tabs } from "./Tabs";
import { EXAMPLES } from "../data";

export function Examples() {
  const [selectedTopic, setSelectedTopic] = useState();

  function handleSelect(selectedButton) {
    setSelectedTopic(selectedButton);
  }

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
    <Section title="Examples" id="examples">
      <Tabs
        // 태그를 인자로 받고 싶어서 buttonsContainer라는 props를 만들었다.
        // buttonsContainer를 사용하는 경우 기존 html 태그를 넣어줄 때는 "menu"와 같이 문자열로 넣어줘야 하고
        // 사용자 지정 컴포넌트를 넣어주거나 변수를 넣어줄 때는 {}로 감싸줘야 한다.
        buttonsContainer="menu"
        buttons={
          // 해당 버튼에 html 코드를 넘길 때는 항상 하나의 부모가 존재해야 하기에 <></>로 감싸줘야 한다.
          <>
            {
              // TabButton 컴포넌트는 이제 ...props를 이용하기에 직접 onClick을 지정해야 한다.
            }
            <TabButton
              isSelected={selectedTopic === "components"}
              onClick={() => handleSelect("components")}
            >
              Components
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "jsx"}
              onClick={() => handleSelect("jsx")}
            >
              JSX
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "props"}
              onClick={() => handleSelect("props")}
            >
              Props
            </TabButton>
            <TabButton
              isSelected={selectedTopic === "state"}
              onClick={() => handleSelect("state")}
            >
              State
            </TabButton>
          </>
        }
      >
        {tabContent}
      </Tabs>
    </Section>
  );
}
