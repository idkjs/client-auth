module SignIn = [%graphql
  {|
  mutation signIn($username: String!, $password: String!) {
    signIn(username: $username, password: $password) {
      id
    }
  }
 |}
];

module SignUp = [%graphql
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
