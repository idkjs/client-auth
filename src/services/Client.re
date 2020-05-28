let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

// let httpLink =
//   ApolloLinks.createHttpLink(
//     ~uri=[%bs.raw {| process.env.GRAPHQL_SERVER_URI |}],
//     (),
//   );
let httpLink = ApolloLinks.createHttpLink(~uri="/graphql", ());

/* WebSocket client */
let webSocketLink =
  ApolloLinks.webSocketLink({
    uri: "wss://localhost:4000/graphql",
    options: {
      reconnect: true,
      connectionParams: None,
    },
  });

/* Using the ability to split links, you can send data to each link
   depending on what kind of operation is being sent */
let webSocketHttpLink =
  ApolloLinks.split(
    operation => {
      let operationDefition =
        ApolloUtilities.getMainDefinition(operation.query);
      operationDefition.kind == "OperationDefinition"
      && operationDefition.operation == "subscription";
    },
    webSocketLink,
    httpLink,
  );

let instance =
  ReasonApollo.createApolloClient(
    ~link=webSocketHttpLink,
    ~cache=inMemoryCache,
    (),
  );
