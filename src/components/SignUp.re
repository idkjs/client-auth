open !ReasonApolloTypes;
exception GraphQLErrors(array(graphqlError));
exception EmptyResponse;

let str = ReasonReact.string;

module SignUpConfig = [%graphql
  {|
    mutation signUp(
      $name: String!
      $username: String!
      $password: String!
      $passwordConfirm: String!
    ) {
      signUp(
        name: $name
        username: $username
        password: $password
        passwordConfirm: $passwordConfirm
      ) {
        id
      }
    }
|}
];

module SignUpMutation = ReasonApollo.CreateMutation(SignUpConfig);

type state = {
  name: string,
  username: string,
  password: string,
  passwordConfirm: string,
};

type action =
  | UpdateName(string)
  | UpdateUsername(string)
  | UpdatePassword(string)
  | UpdatePasswordConfirm(string);

[@react.component]
let make = (~onSignUpSuccess) => {
  let (state, dispatch) =
    React.useReducer(
      state =>
        fun
        | UpdateName(name) => {...state, name}
        | UpdateUsername(username) => {...state, username}
        | UpdatePassword(password) => {...state, password}
        | UpdatePasswordConfirm(passwordConfirm) => {
            ...state,
            passwordConfirm,
          },
      {name: "", username: "", password: "", passwordConfirm: ""},
    );

  let toast = Chakra.Toast.useToast();

  <SignUpMutation>
    ...{(mutate, {result}) => {
      <Group title="Sign Up">
        <Chakra.Text fontSize="md">
          "SignUp to Chat"->React.string
        </Chakra.Text>
        <br />
        <form>
          <Chakra.Input
            _type=`text
            placeholder="Name"
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdateName->dispatch
            }
          />
          <br />
          <br />
          <Chakra.Input
            _type=`text
            placeholder="Username"
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdateUsername->dispatch
            }
          />
          <br />
          <br />
          <Chakra.Input
            _type=`password
            placeholder="Password"
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdatePassword->dispatch
            }
          />
          <br />
          <br />
          <Chakra.Input
            _type=`password
            placeholder="PasswordConfirm"
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdatePasswordConfirm->dispatch
            }
          />
          {switch (result) {
           | Error(e) => <ErrorAlert message={e.message} />
           | _ => React.null
           }}
          <br />
          <br />
          <Chakra.Button
            _type=`submit
            onClick={e => {
              ReactEvent.Synthetic.preventDefault(e);

              switch (
                FormValidation.nonEmptyString(state.name),
                FormValidation.nonEmptyString(state.password),
                FormValidation.nonEmptyString(state.username),
                FormValidation.nonEmptyString(state.passwordConfirm),
              ) {
              | (false, _,_,_) =>
                toast(
                  ~title="Oops",
                  ~description="Invalid name",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
              | (_, false,_,_) =>
                toast(
                  ~title="Oops",
                  ~description="Require non-empty username",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
              | (_, _,false,_) =>
                toast(
                  ~title="Oops",
                  ~description="Require non-empty password",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
              | (_, _,_, false) =>
                toast(
                  ~title="Oops",
                  ~description="Require non-empty password confirmation",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
                |> ignore
              | _ =>
                let signinVariables =
                  SignUpConfig.makeVariables(
                    ~name=state.name,
                    ~username=state.username,
                    ~password=state.password,
                    ~passwordConfirm=state.passwordConfirm,
                  );

                mutate(~variables=signinVariables(), ())
                |> Js.Promise.then_(res => {
                     switch (res) {
                     | Errors(_)
                     | EmptyResponse =>
                       toast(
                         ~title="Oops",
                         ~description="Something went wrong!",
                         ~position=`topRight,
                         ~status=`danger,
                         (),
                       )
                     | Data(data) =>
                       switch (data##signUp) {
                       | None =>
                         toast(
                           ~title="Oops",
                           ~description="Something went wrong!",
                           ~position=`topRight,
                           ~status=`danger,
                           (),
                         )
                       | Some(user) =>
                         onSignUpSuccess(
                           state.username,
                           state.password,
                           user##id,
                         )
                       }
                     };
                     Js.Promise.resolve();
                   })
                |> ignore;
              };
            }}
            variantColor=`blue
            isLoading={result == Loading}>
            {str("Next")}
          </Chakra.Button>
        </form>
      </Group>
    }}
  </SignUpMutation>;
};