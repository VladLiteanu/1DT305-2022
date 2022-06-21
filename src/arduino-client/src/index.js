import { render } from "react-dom";
import { BrowserRouter, Routes, Route, Link } from "react-router-dom";
import Home from './home/index';

render(
  <BrowserRouter>
    <Routes>
      <Route path="/" element={<Home />} />
    </Routes>
  </BrowserRouter>,
  document.getElementById("root")
);
