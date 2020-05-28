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

[@react.component]
let make = (~me) => {
  <Container>
    <Text>
      {React.string({j|👋 SignInForm Placeholder ++ me.name |j})}
      {React.string(me##name)}
      <code> {React.string("src/components/SignInForm.re")} </code>
    </Text>
    <span className=[%css "display: flex"] />
  </Container>;
};
