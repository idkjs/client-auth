open ApolloHooks;
module Container = [%styled {|
  text-align: center;
  margin-top: 3rem;
|}];

module Text = [%styled
  {|
  font-size: 1.875rem;
  text-decoration: none;
  color: #4299e1;
|}
];

module Link = [%styled.a
  {| font-size: 1.875rem; color: #1a202c; margin-bottom: 1rem; |}
];
open FormComponents;
open SignInReducer;
module StateLenses = [%lenses
  type state = {
    email: string,
    password: string,
  }
];

module LoginForm = ReForm.Make(StateLenses);

let useLoginForm = (~onSubmit) => {
  LoginForm.use(
    ~schema={
      LoginForm.Validation.Schema([|
        Email(Email),
        Custom(
          Email,
          values =>
            Js.String.length(values.email) == 0
              ? Error("Email must not be empty") : Valid,
        ),
        Custom(
          Password,
          values =>
            Js.String.length(values.password) == 0
              ? Error("Password must not be empty") : Valid,
        ),
      |]);
    },
    ~onSubmit=
      ({state}) => {
        onSubmit(state.values);

        None;
      },
    ~initialState={email: "", password: ""},
    (),
  );
};
[@react.component]
let make = () => {
  let (signInMutation, simple, _full) =
    useMutation(Mutations.SignIn.definition);
  let logger = () => Js.log("Form submitted");
  let (state, handleChange, handleSubmit) = useForm(~callback=logger);

<div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <div className="box">
          <form onSubmit=handleSubmit>
            <div className="field">
              <label className="label">
                {"Username" |> React.string}
              </label>
              <div className="control">
                <input
                  className="input"
                  type_="username"
                  name="username"
                  value={state.username}
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
  // <SignInForm.Provider value=reform>
  //   <div className="w-full max-w-lg mx-auto">
  //     <form className="bg-white px-8 pt-6 pb-8 mb-4" onSubmit>
  //       <FieldString
  //         field=StateLenses.Email
  //         inputType=FormField.Text
  //         label="Email"
  //       />
  //       <FieldString
  //         field=StateLenses.Password
  //         inputType=FormField.Password
  //         label="Senha"
  //       />
  //       {switch (simple) {
  //        | Error(_) =>
  //          <p className="text-red-500 text-sm mb-4">
  //            {"E-mail ou senha incorretos" |> React.string}
  //          </p>
  //        | _ => React.null
  //        }}
  //       <div className="w-full flex justify-end">
  //         <OutlinedButton> "Entrar"->React.string </OutlinedButton>
  //       </div>
  //     </form>
  //   </div>
  // </SignInForm.Provider>;
};