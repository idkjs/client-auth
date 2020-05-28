[%bs.raw {|require('./index.css')|}];
[%styled.global {|
  html, body {
    margin: 0;
    padding: 0;
  }
|}];

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <ApolloHooks.Provider client=Client.instance>
      <App />
    </ApolloHooks.Provider>
  </ReasonApollo.Provider>,
  "root",
);