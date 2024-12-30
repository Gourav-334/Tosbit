import React, { useState } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faBars } from "@fortawesome/free-solid-svg-icons";
import Body from './../components/Body'
import "./../styles/Home.css";

export default function Home() {
  const[isDataset,setDataset] = useState(false);
  const[isColumnset,setColumnset] = useState(false);

  const toggleDataset = () => {
    setDataset((prevState) => {
      console.log("Previous State:", prevState);
      return !prevState;
    });
  };
  
  const togglcolumnset = () =>{
    setColumnset((prevState)=>{
      console.log("Previous State:",prevState);
      return !prevState;
    });
  }
  
  return (
   <>
   <div className="body">
   <nav id='sidebar'>
     <ul>
      <li>
        <span className="logo">Datox</span>
        <button id="toggle-btn">
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M120-240v-80h720v80H120Zm0-200v-80h720v80H120Zm0-200v-80h720v80H120Z"/></svg>
        </button>
      </li>
      <li className="active">
      <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M240-200h120v-240h240v240h120v-360L480-740 240-560v360Zm-80 80v-480l320-240 320 240v480H520v-240h-80v240H160Zm320-350Z"/></svg>
        <a href='/'><span>Home</span></a>
      </li>
      <li className="dropdown-btn">
        <button onClick={toggleDataset}>
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M480-120q-151 0-255.5-46.5T120-280v-400q0-66 105.5-113T480-840q149 0 254.5 47T840-680v400q0 67-104.5 113.5T480-120Zm0-479q89 0 179-25.5T760-679q-11-29-100.5-55T480-760q-91 0-178.5 25.5T200-679q14 30 101.5 55T480-599Zm0 199q42 0 81-4t74.5-11.5q35.5-7.5 67-18.5t57.5-25v-120q-26 14-57.5 25t-67 18.5Q600-528 561-524t-81 4q-42 0-82-4t-75.5-11.5Q287-543 256-554t-56-25v120q25 14 56 25t66.5 18.5Q358-408 398-404t82 4Zm0 200q46 0 93.5-7t87.5-18.5q40-11.5 67-26t32-29.5v-98q-26 14-57.5 25t-67 18.5Q600-328 561-324t-81 4q-42 0-82-4t-75.5-11.5Q287-343 256-354t-56-25v99q5 15 31.5 29t66.5 25.5q40 11.5 88 18.5t94 7Z"/></svg>
        <span>Datasets</span>
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M480-360 280-560h400L480-360Z"/></svg>
        </button>
        <ul className={`submenu${isDataset?"show":""}`}>
          <li><a href="#">Database 1</a></li>
          <li><a href="#">Database 2</a></li>
          <li><a href="#">Database 3</a></li>
          <li><a href="#">Database 4</a></li>
        </ul>
      </li>
      <li className="dropdown-btn">
        <button onClick={togglcolumnset}>
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M480-120q-151 0-255.5-46.5T120-280v-400q0-66 105.5-113T480-840q149 0 254.5 47T840-680v400q0 67-104.5 113.5T480-120Zm0-479q89 0 179-25.5T760-679q-11-29-100.5-55T480-760q-91 0-178.5 25.5T200-679q14 30 101.5 55T480-599Zm0 199q42 0 81-4t74.5-11.5q35.5-7.5 67-18.5t57.5-25v-120q-26 14-57.5 25t-67 18.5Q600-528 561-524t-81 4q-42 0-82-4t-75.5-11.5Q287-543 256-554t-56-25v120q25 14 56 25t66.5 18.5Q358-408 398-404t82 4Zm0 200q46 0 93.5-7t87.5-18.5q40-11.5 67-26t32-29.5v-98q-26 14-57.5 25t-67 18.5Q600-328 561-324t-81 4q-42 0-82-4t-75.5-11.5Q287-343 256-354t-56-25v99q5 15 31.5 29t66.5 25.5q40 11.5 88 18.5t94 7Z"/></svg>
        <span>Columnsets</span>
        <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#ffffff"><path d="M480-360 280-560h400L480-360Z"/></svg>
        </button>
        <ul className={`submenu${isColumnset?"show":""}`}>
          <li><a href="#">Column 1</a></li>
          <li><a href="#">Column 2</a></li>
          <li><a href="#">Column 3</a></li>
          <li><a href="#">Column 4</a></li>
        </ul>
      </li>
      
     </ul>
   </nav>
   <main>
    <div className="container">
       <Body/>
    </div>
    
   </main>
   </div>
   </>
  );
}
