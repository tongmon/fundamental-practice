import { calculateInvestmentResults, formatter } from "../../util/investment";

export function Table({ II, AI, ER, D }) {
  const annualData = calculateInvestmentResults({
    initialInvestment: II,
    annualInvestment: AI,
    expectedReturn: ER,
    duration: D,
  });

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
        {annualData.map((data, i) => (
          <tr key={i}>
            <td>{data.year}</td>
            <td>{formatter.format(data.valueEndOfYear)}</td>
            <td>{formatter.format(data.interest)}</td>
            <td>{formatter.format(data.totalInterest)}</td>
            <td>{formatter.format(data.investedCapital)}</td>
          </tr>
        ))}
      </tbody>
    </table>
  );
}
