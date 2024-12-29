import React from 'react';
import './../styles/Home.css';

export default function Home() {
  return (
    <>
     <div className='app-container'>
      <nav className={`sidebar${issidebaropen ? 'open' : 'closed'}`}></nav>
      <div className='sidebar-header'>
        <img src="logo.png"></img>
        
      </div>
     </div>
    </>
  );
}
