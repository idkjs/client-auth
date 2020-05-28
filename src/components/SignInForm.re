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
[@react.component]
let make = () => {

  let logger = () => Js.log("Form submitted");
  let (state, handleChange, handleSubmit) = useForm(~callback=logger);

<SignForm>
<ActualForm>
<Legend>"Sign in"->Utils.str</Legend>
    <Container>
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
    </Container>
  </ActualForm>
  </SignForm>;
};