open !ReasonApolloTypes;
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

[@bs.deriving jsConverter]
type currentStep =
  | [@bs.as 1] ProvidingusernamePwd
  | [@bs.as 2] SelectingSquad;

type state = {
  username: string,
  password: string,
  // userId: string,
  currentStep,
};

type action =
  | UpdateSignUpInfo(string, string)
  | UpdateCurrentStep(currentStep);

[@react.component]
let make = (~setSession) => {
  let toast = Chakra.Toast.useToast();

  let (state, dispatch) =
    React.useReducer(
      state =>
        fun
        | UpdateSignUpInfo(username, password) => {
            ...state,
            username,
            password,
            
          }
        | UpdateCurrentStep(currentStep) => {...state, currentStep},
      {username: "", password: "", currentStep: ProvidingusernamePwd},
    );
  <div>
    {switch (state.currentStep) {
     | ProvidingusernamePwd =>
       <SignUp
         onSignUpSuccess={(username, password) => {
           dispatch(UpdateSignUpInfo(username, password));
           dispatch(UpdateCurrentStep(SelectingSquad));
         }}
       />
     | SelectingSquad =>
       <SignInMutation>
         ...{(mutate, _) => {
           <SquadSelection
             onSquadSelectSuccess={() => {
               let signinVariables =
                 SignInConfig.make(
                   ~username=state.username,
                   ~password=state.password,
                   (),
                 )##variables;

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
                      open !Session;
                      switch (data##signinUser##token, data##signinUser##user) {
                      | (Some(tk), Some(user)) =>
                        setSession({
                          token: tk,
                          role: user##role,
                          userId: user##id,
                          squadId:
                            Belt.Option.map(user##squad, squad => squad##id),
                        })
                      | (_, _) =>
                        toast(
                          ~title="Oops",
                          ~description="Something went wrong!",
                          ~position=`topRight,
                          ~status=`danger,
                          (),
                        )
                      };
                      toast(
                        ~title="Nice",
                        ~description="You've signed up successfully",
                        ~position=`topRight,
                        ~status=`success,
                        (),
                      );
                    };
                    Js.Promise.resolve();
                  })
               |> ignore;
             }}
             userId={state.userId}
           />
         }}
       </SignInMutation>
     }}
  </div>;
};
