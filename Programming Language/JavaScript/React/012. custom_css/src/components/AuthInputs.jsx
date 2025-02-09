import { useState } from "react";

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
      <div className="controls">
        <p>
          <label className={`label ${emailNotValid ? "invalid" : ""}`}>
            Email
          </label>
          <input
            type="email"
            className={emailNotValid ? "invalid" : undefined}
            // style={{ backgroundColor: emailNotValid ? "#fed2d2" : "#d1d5db" }}
            onChange={(event) => handleInputChange("email", event.target.value)}
          />
        </p>
        <p>
          <label className={`label ${passwordNotValid ? "invalid" : ""}`}>
            Password
          </label>
          <input
            type="password"
            // {emailNotValid && 'invalid'} 이런 식으로는 emailNotValid가 false인 경우 boolean 값이 반환되어 오류가 발생한다.
            className={passwordNotValid ? "invalid" : undefined} // 그래서 옆의 방식을 사용한다.
            onChange={(event) =>
              handleInputChange("password", event.target.value)
            }
          />
        </p>
      </div>
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
