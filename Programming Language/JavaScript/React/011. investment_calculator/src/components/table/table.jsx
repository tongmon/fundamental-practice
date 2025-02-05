import { calculateInvestmentResults, formatter } from "../../util/investment";

export function Table({ II, AI, ER, D }) {
  return (
    <table id="result">
      <thead>
        <tr>
          <th>Year</th>
          <th>Investment Value</th>
          <th>Interest (Year)</th>
          <th>Total Interest</th>
          <th>Invested Capital</th>
        </tr>
      </thead>
      <tbody>
        {calculateInvestmentResults(II, AI, ER, D).map((data, i) => (
          <tr key={i}>
            <td>{i + 1}</td>
            <td>{data.year}</td>
            <td>{data.interest}</td>
            <td>{data.valueEndOfYear}</td>
            <td>{data.annualInvestment}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}
