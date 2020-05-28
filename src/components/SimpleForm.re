type state = {
  username: string,
  email: string,
  password: string,
};

type action =
  | SetUsername(string)
  | SetEmail(string)
  | SetPassword(string)
  | ResetState;

let initialState = {username: "", email: "", password: ""};

let reducer = (state, action) =>
  switch (action) {
  | SetUsername(username) => {...state, username}
  | SetEmail(email) => {...state, email}
  | SetPassword(password) => {...state, password}
  | ResetState => initialState
  };

let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

/* custom hook takes a callback function `~callback` that we'll use when we submit the form. Now different forms could add different logic! */
let useForm = (~callback) => {
  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = (evt): string => evt->ReactEvent.Form.target##name;

  let (state, dispatch) = React.useReducer(reducer, initialState);

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "email" => valueFromEvent(evt)->SetEmail |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
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

[@react.component]
let make = () => {
  // let (state, dispatch) = React.useReducer(reducer, initialState);
  /* we will pass this as our callback */
  let logger = () => Js.log("Form submitted");

  let (state, handleChange, handleSubmit) = useForm(~callback=logger);
  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <div className="box">
          <form onSubmit=handleSubmit>
            <div className="field">
              <label className="label">
                {"Email Address" |> React.string}
              </label>
              <div className="control">
                <input
                  className="input"
                  type_="email"
                  name="email"
                  value={state.email}
                  required=true
                  onChange=handleChange
                />
              </div>
            </div>
            <div className="field">
              <label className="label"> {"Password" |> React.string} </label>
              <div className="control">
                <input
                  className="input"
                  type_="password"
                  name="password"
                  value={state.password}
                  required=true
                  onChange=handleChange
                />
              </div>
            </div>
            <button
              type_="submit" className="button is-block is-info is-fullwidth">
              {"Login" |> React.string}
            </button>
          </form>
        </div>
      </div>
    </div>
  </div>;
};