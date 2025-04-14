import { useState } from "react";

// styled-components는 CSS-in-JS 라이브러리로, JavaScript 파일 내에서 CSS를 작성할 수 있게 해준다.
import { styled } from 'styled-components';

// 밑과 같이 특정 스타일을 변수에 저장해둘 수 있다.
const ControlContainer = styled.div`
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  margin-bottom: 1.5rem;
`;

// styled-components는 color 속성을 보면 알겠지만 함수를 사용하여 props를 전달받을 수 있다.
// 함수를 전달할 때 ({ $invalid }) => ($invalid ? '#f87171' : '#6b7280') 이런 형식을 사용한 다는 것을 기억하자.
// 위 형식에서 (), {}가 생략되면 제대로 동작하지 않는다.
const Label = styled.label`
  display: block;
  margin-bottom: 0.5rem;
  font-size: 0.75rem;
  font-weight: 700;
  letter-spacing: 0.1em;
  text-transform: uppercase;
  color: ${({ $invalid }) => ($invalid ? '#f87171' : '#6b7280')};
`;

const Input = styled.input`
  width: 100%;
  padding: 0.75rem 1rem;
  line-height: 1.5;
  background-color: ${({ $invalid }) => ($invalid ? '#fed2d2' : '#d1d5db')};
  color: ${({ $invalid }) => ($invalid ? '#ef4444' : '#374151')};
  border: 1px solid transparent;
  border-radius: 0.25rem;
  border - color: ${({ $invalid }) => ($invalid ? '#f73f3f' : 'transparent')};
  box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.1), 0 1px 2px 0 rgba(0, 0, 0, 0.06);
`;

export default function AuthInputs() {
  const [enteredEmail, setEnteredEmail] = useState("");
  const [enteredPassword, setEnteredPassword] = useState("");
  const [submitted, setSubmitted] = useState(false);

  function handleInputChange(identifier, value) {
    if (identifier === "email") {
      setEnteredEmail(value);
    } else {
      setEnteredPassword(value);
    }
  }

  function handleLogin() {
    setSubmitted(true);
  }

  const emailNotValid = submitted && !enteredEmail.includes("@");
  const passwordNotValid = submitted && enteredPassword.trim().length < 6;

  return (
    <div id="auth-inputs">
      {
        // styled-components를 적용하려면 원래 <div> 태그를 styled.div인 <ControlContainer>로 바꿔야 한다.
      }
      <ControlContainer>
        <p className="paragraph">
          {
            // label 태그도 마찬가지로 위에서 정의한 styled.label로 바꿔주면 된다.
            // styled-components에서 invalid와 같이 props로 값을 전달하여 동적 스타일링을 구현 할 수 있다.
            // styled-components의 props는 내장 프로퍼티의 이름과 충돌을 피하기 위해 $로 시작하는 것이 좋다.
          }
          <Label $invalid={emailNotValid}>
            Email
          </Label>
          <Input
            type="email"
            $invalid={emailNotValid}
            onChange={(event) => handleInputChange("email", event.target.value)}
          />
        </p>
        <p>
          <Label $invalid={passwordNotValid}>
            Password
          </Label>
          <Input
            type="password"
            $invalid={passwordNotValid}
            onChange={(event) =>
              handleInputChange("password", event.target.value)
            }
          />
        </p>
      </ControlContainer>
      <div className="actions">
        <button type="button" className="text-button">
          Create a new account
        </button>
        <button className="button" onClick={handleLogin}>
          Sign In
        </button>
      </div>
    </div>
  );
}
