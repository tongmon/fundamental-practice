import { useState } from "react";

// Solution
export function Inputs({ userInput, handleChange }) {
  return (
    <section id="user-input">
      <div className="input-group">
        <p>
          <label>Initial Investment</label>
          <input
            type="number"
            required
            value={userInput.initialInvestment}
            onChange={(event) =>
              handleChange("initialInvestment", event.target.value)
            }
          />
        </p>
        <p>
          <label>Annual Investment</label>
          <input
            type="number"
            required
            value={userInput.annualInvestment}
            onChange={(event) =>
              handleChange("annualInvestment", event.target.value)
            }
          />
        </p>
      </div>
      <div className="input-group">
        <p>
          <label>Expected Return</label>
          <input
            type="number"
            required
            value={userInput.expectedReturn}
            onChange={(event) =>
              handleChange("expectedReturn", event.target.value)
            }
          />
        </p>
        <p>
          <label>Duration</label>
          <input
            type="number"
            required
            value={userInput.duration}
            onChange={(event) => handleChange("duration", event.target.value)}
          />
        </p>
      </div>
    </section>
  );
}

/*
// My solution
export function Inputs({ IIInfo, AIInfo, ERInfo, DInfo }) {
  return (
    <div id="user-input" className="input-group">
      <div>
        <label>Initial Investment</label>
        <input type="number" required value={IIInfo[0]} onChange={IIInfo[1]} />
        <label>Expected Return</label>
        <input type="number" required value={ERInfo[0]} onChange={ERInfo[1]} />
      </div>
      <div>
        <label>Annual Investment</label>
        <input type="number" required value={AIInfo[0]} onChange={AIInfo[1]} />
        <label>Duration</label>
        <input type="number" required value={DInfo[0]} onChange={DInfo[1]} />
      </div>
    </div>
  );
}
*/
