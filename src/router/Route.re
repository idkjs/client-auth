module type Config = {
  type route;

  let toUrl: route => string;
  let toRoute: ReasonReact.Router.url => route;
};

module Config = {
  type route =
    | Home
    | Chat(string)
    | NotFound;

  let toRoute = (url: ReasonReact.Router.url) => {
    let hashes = url.hash |> Js.String.split("/") |> Array.to_list;
    switch (url.path) {
    | [""]
    | []
    | ["/"] =>
      switch (hashes) {
      | [""] => Home
      | ["", "chats", chatId] => Chat(chatId)
      | _ => NotFound
      }
    | _ => NotFound
    };
  };

  let toUrl =
    fun
    | Home => "#"
    | Chat(id) => "#/chats/" ++ id
    | NotFound => "#/404";
};

module Link = {
  [@react.component]
  let make = (~route, ~style=?, ~className=?, ~children) => {
    let href = Config.toUrl(route);
    let onClick = e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(href);
    };
    <a href onClick ?style ?className> children </a>;
  };
};
