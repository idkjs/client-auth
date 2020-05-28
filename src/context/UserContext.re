// Define the type of the value we will put in context - pair of user and dispatch
type dispatch = Types.fetch(Types.me, string) => unit;
// type contextValue = (Types.me, dispatch);
// type contextValue = (Types.fetch(Types.me, string));
type contextValue = {me: Types.fetch(Types.me, string)};
type state = {me: Types.fetch(Types.me, string)};

let initValue: contextValue = {me: Loading};
let context = React.createContext(initValue);
let useMe = () => React.useContext(context);

module ContextProvider = {
  let make = React.Context.provider(context);
  let makeProps = (~value: state, ~children, ()) => {
    "value": value,
    "children": children,
  };
};
