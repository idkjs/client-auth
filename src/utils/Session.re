let tokenKey = "__TOKEN__";
let userIdKey = "__USER_ID__";

type session = {
  token: string,
  userId: string,
};

type token =
  | Invalid
  | Valid(session);

let setSessionToStorage = session => {
  LocalStorage.setItem(tokenKey, session.token->Some);

  LocalStorage.setItem(userIdKey, session.userId->Some);
};

let getSessionFromStorage = () => {
  let token = LocalStorage.getItem(tokenKey) |> Js.Nullable.toOption;
  let userId = LocalStorage.getItem(userIdKey) |> Js.Nullable.toOption;

  switch (token, userId) {
  | (Some(token), Some(userId)) => Valid({token, userId})
  | _ => Invalid
  };
};

let clearSession = () => {
  [tokenKey, userIdKey] |> List.map(LocalStorage.removeItem) |> ignore;
};