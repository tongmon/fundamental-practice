import Header from "./components/Header/Header.jsx";
import { CoreConcepts } from "./components/CoreConcepts.jsx";
import { Examples } from "./components/Examples.jsx";

function App() {
  return (
    <>
      {
        // 밑과 같이 여러개의 컴포넌트로 나누어 가독성을 높여 유지보수와 확장을 쉽게 할 수 있다.
      }
      <Header />
      <main>
        <CoreConcepts />
        <Examples />
      </main>
    </>
  );
}

export default App;
