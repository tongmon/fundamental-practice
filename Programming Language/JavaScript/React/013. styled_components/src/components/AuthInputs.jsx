import { useState } from "react";

// styled-components는 CSS-in-JS 라이브러리로, JavaScript 파일 내에서 CSS를 작성할 수 있게 해준다.
import { styled } from 'styled-components';

import { Button } from "./Button";
import { CustomInput } from "./CustomInput";

// 밑과 같이 특정 스타일을 변수에 저장해둘 수 있다.
const ControlContainer = styled.div`
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  margin-bottom: 1.5rem;
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
        <CustomInput
          invalid={emailNotValid}
          type="email"
          onChange={(event) => handleInputChange("email", event.target.value)}>
          Email
        </CustomInput>
        <CustomInput
          invalid={passwordNotValid}
          type="password"
          onChange={(event) => handleInputChange("password", event.target.value)}>
          Password
        </CustomInput>
      </ControlContainer>
      <div className="actions">
        <button type="button" className="text-button">
          Create a new account
        </button>
        <Button onClick={handleLogin}>
          Sign In
        </Button>
      </div>
    </div >
  );
}

