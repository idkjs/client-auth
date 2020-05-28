module Intro = [%styled.div {|
  height: 265px;
 |}];

module Icon = [%styled.img
  {|
  width: 125px;
  height: auto;
  margin-left: auto;
  margin-right: auto;
  padding-top: 70px;
  display: block;
 |}
];

module Title = [%styled.h2
  {|
  width: 100%;
  text-align: center;
  color: white;
 |}
];

// eslint-disable-next-line
module Alternative = [%styled.div
  {|
  position: fixed;
  bottom: 10px;
  left: 10px;

  label {
    color: #4299e1;
  }
 |}
];

// module AuthScreen: React.FC<RouteComponentProps<any>> = ({
//   history,
//   location,
// }) => {
//   module alternative = useMemo(() => {
//     if (location.pathname === '/sign-in') {
//       module handleSignUp = () => {
//         history.replace('/sign-up');
//       };

//       return (
//         <Alternative>
//           Don't have an account yet?{' '}
//           <label onClick={handleSignUp}>Sign up!</label>
//         </Alternative>
//       );
//     } else {
//       module handleSignIn = () => {
//         history.replace('/sign-in');
//       };

//       return (
//         <Alternative>
//           Already have an accout? <label onClick={handleSignIn}>Sign in!</label>
//         </Alternative>
//       );
//     }
//   }, [location.pathname, history]);

//   return (
//     <Container className="AuthScreen Screen">
//       <Intro className="AuthScreen-intro">
//         <Icon src="assets/whatsapp-icon.png" className="AuthScreen-icon" />
//         <Title className="AuthScreen-title">WhatsApp</Title>
//       </Intro>
//       <AnimatedSwitch>
//         <Route exact path="/sign-in" component={SignInForm} />
//         <Route exact path="/sign-up" component={SignUpForm} />
//       </AnimatedSwitch>
//       {alternative}
//     </Container>
