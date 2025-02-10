import logo from "../assets/logo.png";
// import "../components/Header.css";

// 밑과 같이 module.css를 사용하면 css 파일을 import할 때 클래스 이름을 지정해줘야 한다.
// 이렇게 css 클래스 이름 변수를 사용하게 되어 특정 jsx 파일에서만 사용되도록 css를 컴포넌트 단위로 지정할 수 있다.
import classes from "../components/Header.module.css";

export default function Header() {
  return (
    <header>
      <img src={logo} alt="A canvas" />
      <h1>ReactArt</h1>
      {
        // module.css를 사용하면 className="paragraph" 대신에 className={classes.paragraph}로 사용할 수 있다.
        // 이것의 장점은 클래스 이름이 겹치지 않는다는 것이다.
        // react는 내부적으로 paragraph 클래스 이름을 paragraph_vstq_1 이런 식으로 바꿔서 사용하기에 className="paragraph"을 사용한 다른 곳과 겹칠 일이 없다.
      }
      <p className={classes.paragraph}>
        A community of artists and art-lovers.
      </p>
    </header>
  );
}
