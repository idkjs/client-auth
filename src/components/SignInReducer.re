type state = {
  username: string,
  password: string,
  error: string,
};

type action =
  | SetUsername(string)
  | SetPassword(string)
  | SetError(string)
  | ResetState;

let initialState = {username: "", password: "", error: ""};

let reducer = (state, action) =>
  switch (action) {
  | SetUsername(username) => {...state, username}
  | SetPassword(password) => {...state, password}
  | SetError(error) => {...state, error}
  | ResetState => initialState
  };

let useForm = (~callback) => {
  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = (evt): string => evt->ReactEvent.Form.target##name;

  let (state, dispatch) = React.useReducer(reducer, initialState);

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
    | "error" => valueFromEvent(evt)->SetError |> dispatch
    | _ => ()
    };
  };

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    callback();
    dispatch(ResetState);
  };
  /* we have to return state, handleChange, and handleSubmit, so that we can use it in our form component as a custom hook. */
  (state, handleChange, handleSubmit);
};