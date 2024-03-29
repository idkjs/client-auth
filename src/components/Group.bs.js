// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Core from "@chakra-ui/core";

function Group(Props) {
  var title = Props.title;
  var children = Props.children;
  return React.createElement("div", {
              style: {
                borderWidth: "1px",
                marginTop: "2rem",
                padding: "1.25rem",
                borderRadius: "0.25rem",
                boxShadow: "rgba(0, 0, 0, 0.1) 0px 4px 6px -1px, rgba(0, 0, 0, 0.06) 0px 2px 4px -1px",
                flex: "1 1 0%"
              }
            }, React.createElement(Core.Heading, {
                  fontSize: "xl",
                  children: title
                }), React.createElement("br", undefined), children);
}

var make = Group;

export {
  make ,
  
}
/* react Not a pure module */
