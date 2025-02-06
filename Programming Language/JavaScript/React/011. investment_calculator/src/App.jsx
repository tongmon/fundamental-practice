import { Header } from "./components/header/Header";
import { Inputs } from "./components/inputs/Inputs";
import { Table } from "./components/table/table";
import { useState } from "react";

const INITIAL_INVESTMENT = 10000;
const ANNUAL_INVESTMENT = 1200;
const EXPECTED_RETURN = 6;
const DURATION = 10;

function App() {
  const [initialInvestment, setInitialInvestment] =
    useState(INITIAL_INVESTMENT);
  const [annualInvestment, setAnnualInvestment] = useState(ANNUAL_INVESTMENT);
  const [expectedReturn, setExpectedReturn] = useState(EXPECTED_RETURN);
  const [duration, setDuration] = useState(DURATION);

  function handleInitialInvestmentChange(event) {
    setInitialInvestment(Number(event.target.value));
  }

  function handleAnnualInvestmentChange(event) {
    setAnnualInvestment(Number(event.target.value));
  }

  function handleExpectedReturnChange(event) {
    setExpectedReturn(Number(event.target.value));
  }

  function handleDurationChange(event) {
    setDuration(Number(event.target.value));
  }

  return (
    <>
      <Header />
      <Inputs
        IIInfo={[initialInvestment, handleInitialInvestmentChange]}
        AIInfo={[annualInvestment, handleAnnualInvestmentChange]}
        ERInfo={[expectedReturn, handleExpectedReturnChange]}
        DInfo={[duration, handleDurationChange]}
      />
      <Table
        II={initialInvestment}
        AI={annualInvestment}
        ER={expectedReturn}
        D={duration}
      />
    </>
  );
}

export default App;
