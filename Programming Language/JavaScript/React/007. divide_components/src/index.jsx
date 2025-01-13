import React from "react";
import ReactDOM from "react-dom/client";

import App from "./App.jsx";
import "./index.css";

const entryPoint = document.getElementById("root");

// ReactDOM.createRoot(entryPoint).render(<App />);
// JSX를 사용하지 않고 React.createElement(App)를 사용해도 된다.
// 단, JSX를 사용하면 코드가 더 간결해지고 가독성이 좋아진다.
ReactDOM.createRoot(entryPoint).render(React.createElement(App));
