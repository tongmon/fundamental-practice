import headerImg from "../../assets/investment-calculator-logo.png";

export function Header() {
  return (
    <header id="header">
      <img src={headerImg} alt="Investment Calculator Image" />
      <h1>Investment Calculator</h1>
    </header>
  );
}
