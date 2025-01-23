import React from "react";
import { createRoot } from "react-dom/client";
import App from "./App";

const container = document.getElementById("root");
const root = createRoot(container); // Create a root.
root.render(<App />); // Render the App component.
//so big announcement react 18 has created createroot function in order to handle concurrent start 
//congratulation react