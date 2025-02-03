export function Inputs() {
  return (
    <div id="user-input" className="input-group">
      <div>
        <label>Initial Investment</label>
        <input type="number" />
        <label>Annual Investment</label>
        <input type="number" />
      </div>
      <div>
        <label>Expected Return</label>
        <input type="number" />
        <label>Duration</label>
        <input type="number" />
      </div>
    </div>
  );
}
