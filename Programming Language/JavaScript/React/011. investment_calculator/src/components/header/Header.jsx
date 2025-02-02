import headerImg from "../../assets/investment-calculator-logo.png";

export function Header() {
  return (
    <header>
      <img src={headerImg} alt="Investment Calculator Image" />
      <h1>React Investment Calculator</h1>
    </header>
  );
}
