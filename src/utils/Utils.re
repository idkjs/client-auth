[@bs.val] [@bs.scope ("process", "env")]
external graphEndpoint: Js.Nullable.t(string) = "GRAPHQL_ENDPOINT";
let graphEndpoint = graphEndpoint->Js.Nullable.toOption;

let str = React.string;

let toOption = value => Some(value);

let optionToString =
  fun
  | Some(x) => x
  | None => "";