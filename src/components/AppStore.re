let str = React.string;

type state = {me: Types.fetch(Types.me, string)};

let initialState = {me: Loading};

let context = React.createContext(initialState);

module ContextProvider = {
  let make = React.Context.provider(context);
  let makeProps = (~value: state, ~children, ()) => {
    "value": value,
    "children": children,
  };
};

[@react.component]
let make = (~children) => {
  // let url = ReasonReactRouter.useUrl();
  // let value = ApolloHooks.useQuery(Queries.MeQuery.definition);
  let (value, setValue) = React.useState(() => initialState);

  React.useEffect1(
    () => {
      switch (value.me) {
      | Success(_) => ()
      | _ => setValue(value => {me: value.me})
      };

      None;
    },
    [|value|],
  );

  <ContextProvider value>
    {switch (value.me) {
     | Success(me) =>
       <ReasonApollo.Provider client=Client.instance>
         <ApolloHooks.Provider client=Client.instance>
           children
         </ApolloHooks.Provider>
       </ReasonApollo.Provider>
     | _ => children
     }}
  </ContextProvider>;
};
