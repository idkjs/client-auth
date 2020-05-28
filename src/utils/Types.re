type fetch('s, 'f) =
  | NotAsked
  | Loading
  | Failure('f)
  | Success('s);

type me = {
  id: string,
  name: string,
  picture: option(Js.Json.t),
};
