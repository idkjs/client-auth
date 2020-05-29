open ReasonApolloTypes;
exception GraphQLErrors(array(graphqlError));
exception EmptyResponse;

let str = ReasonReact.string;

module SignInConfig = [%graphql
  {|
  mutation signIn($username: String!, $password: String!) {
    signIn(username: $username, password: $password) {
      id
    }
  }
|}
];

module SignInMutation = ReasonApollo.CreateMutation(SignInConfig);

type state = {
  username: string,
  password: string,
};
type action =
  | UpdateUsername(string)
  | UpdatePassword(string);

[@react.component]
let make = (~setSession) => {
  let toast = Chakra.Toast.useToast();
  let (touched, setTouched) = React.useState(() => false);
  React.useEffect0(() => {
    toast(
      ~title="Hi there",
      ~description="You need to sign in to continue!",
      ~position=`topRight,
      ~status=`warning,
      (),
    );
    None;
  });

  let (state, dispatch) =
    React.useReducer(
      state =>
        fun
        | UpdateUsername(username) => {...state, username}
        | UpdatePassword(password) => {...state, password},
      {username: "", password: ""},
    );

  <SignInMutation>
    ...{(mutate, {result}) => {
      <Group title="Sign In">
        <Chakra.Text fontSize="md">
          "Sign in to Chat"->React.string
        </Chakra.Text>
        <br />
        <form>
          <Chakra.Input
            _type=`text
            placeholder="Username"
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdateUsername->dispatch
            }
            isRequired=true
            isInvalid={
              touched && !FormValidation.nonEmptyString(state.username)
            }
          />
          <br />
          <br />
          <Chakra.Input
            _type=`password
            placeholder="Password"
            isRequired=true
            onChange={e =>
              e->ReactEvent.Form.target##value->UpdatePassword->dispatch
            }
            isInvalid={
              touched && !FormValidation.nonEmptyString(state.password)
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
              setTouched(_ => true);
              ReactEvent.Synthetic.preventDefault(e);

              switch (
                FormValidation.nonEmptyString(state.username),
                FormValidation.nonEmptyString(state.password),
              ) {
              | (false, _) =>
                toast(
                  ~title="Oops",
                  ~description="Invalid username",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
              | (_, false) =>
                toast(
                  ~title="Oops",
                  ~description="Require non-empty password",
                  ~position=`topRight,
                  ~status=`warning,
                  (),
                )
              | _ =>
                let signinVariables =
                  SignInConfig.makeVariables(
                    ~username=state.username,
                    ~password=state.password,
                    (),
                  );

                mutate(~variables=signinVariables, ())
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
                       open Session;
                       switch (data##signIn##id) {
                       | (Some(id)) =>
                         setSession({token: id, userId: id})
                       | (_) =>
                         toast(
                           ~title="Oops",
                           ~description="Something went wrong!",
                           ~position=`topRight,
                           ~status=`danger,
                           (),
                         )
                       };

                       toast(
                         ~title="Welcome back!",
                         ~description="You've signed in successfully",
                         ~position=`topRight,
                         ~status=`success,
                         (),
                       );
                     };
                     Js.Promise.resolve();
                   })
                |> ignore;
              };
            }}
            variantColor=`blue
            isLoading={result == Loading}>
            {str("Sign in")}
          </Chakra.Button>
        </form>
      </Group>
    }}
  </SignInMutation>;
};