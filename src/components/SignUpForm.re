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
let make = () => {
  <Container>
    <Text>
      {React.string({j|👋 SignUpForm Placeholder |j})}
      <code> {React.string("src/components/SignUpForm.re")} </code>
    </Text>
    <span className=[%css "display: flex"] />
  </Container>;
};
