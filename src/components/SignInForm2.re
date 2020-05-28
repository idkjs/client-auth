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
open Utils;

[@react.component]
let make = () => {
  let logger = () => Js.log("Form submitted");
  let (state, handleChange, handleSubmit) = useForm(~callback=logger);
  <SignForm>
    <ActualForm>
      <Legend> "Sign in"->str </Legend>
      <Section sectionWidth="100%">
        <TextField
          label="Username"
          type_="username"
          value={state.username}
          onChange=handleChange
          placeholder="Enter your username"
          required=true
        />
        <TextField
          label="Password"
          type_="password"
          value={state.password}
          onChange=handleChange
          placeholder="Enter your password"
          required=true
        />
      </Section>
      <Button type_="submit" onSubmit=handleSubmit>
        {"Sign In" |> React.string}
      </Button>
      <ErrorMessage> {state.error}->str </ErrorMessage>
   </ActualForm>
  </SignForm>;
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