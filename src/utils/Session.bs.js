// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Js_mapperRt from "bs-platform/lib/es6/js_mapperRt.js";

var tokenKey = "__TOKEN__";

var roleKey = "__ROLE__";

var userIdKey = "__USER_ID__";

var squadIdKey = "__SQUAD_ID__";

var jsMapperConstantArray = [
  [
    -889065687,
    "Leader"
  ],
  [
    796400751,
    "Admin"
  ],
  [
    961173114,
    "Member"
  ]
];

function roleToJs(param) {
  return Js_mapperRt.binarySearch(3, param, jsMapperConstantArray);
}

function roleFromJs(param) {
  return Js_mapperRt.revSearch(3, jsMapperConstantArray, param);
}

function setSessionToStorage(session) {
  localStorage.setItem(tokenKey, session.token);
  var role = session.role;
  if (role !== undefined) {
    localStorage.setItem(roleKey, roleToJs(role));
  }
  localStorage.setItem(userIdKey, session.userId);
  var squadId = session.squadId;
  if (squadId !== undefined) {
    localStorage.setItem(squadIdKey, squadId);
    return ;
  }
  
}

function getSessionFromStorage(param) {
  var token = localStorage.getItem(tokenKey);
  var role = localStorage.getItem(roleKey);
  var userId = localStorage.getItem(userIdKey);
  var squadId = localStorage.getItem(squadIdKey);
  if (token == null) {
    return /* Invalid */0;
  }
  if (userId == null) {
    return /* Invalid */0;
  }
  var tmp;
  if (role == null) {
    tmp = /* Member */961173114;
  } else {
    switch (role) {
      case "Admin" :
          tmp = /* Admin */796400751;
          break;
      case "Leader" :
          tmp = /* Leader */-889065687;
          break;
      default:
        tmp = /* Member */961173114;
    }
  }
  return /* Valid */{
          _0: {
            token: token,
            role: tmp,
            userId: userId,
            squadId: (squadId == null) ? undefined : Caml_option.some(squadId)
          }
        };
}

function clearSession(param) {
  List.map((function (prim) {
          localStorage.removeItem(prim);
          
        }), /* :: */{
        _0: tokenKey,
        _1: /* :: */{
          _0: roleKey,
          _1: /* :: */{
            _0: userIdKey,
            _1: /* :: */{
              _0: squadIdKey,
              _1: /* [] */0
            }
          }
        }
      });
  
}

export {
  tokenKey ,
  roleKey ,
  userIdKey ,
  squadIdKey ,
  roleToJs ,
  roleFromJs ,
  setSessionToStorage ,
  getSessionFromStorage ,
  clearSession ,
  
}
/* No side effect */
