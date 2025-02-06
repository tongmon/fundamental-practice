import { useState } from "react";

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
