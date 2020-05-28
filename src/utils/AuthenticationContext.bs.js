// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";

var context = React.createContext("");

function getToken(param) {
  return React.useContext(context);
}

var make = context.Provider;

function makeProps(value, children, param) {
  return {
          value: value,
          children: children
        };
}

export {
  context ,
  getToken ,
  make ,
  makeProps ,
  
}
/* context Not a pure module */