type documentNode;
type errorPolicy;
type apolloClient;
type apolloLink;
type context;
type data = Js.Json.t;
type networkStatus;

type graphqlError;

type queryConfig = {
  query: documentNode,
  variables: option(Js.Json.t),
};

module DataProxy = {
  type t;

  type readQueryOptions = queryConfig;

  type writeQueryOptions('data) = {
    data: 'data,
    query: documentNode,
    variables: option(Js.Json.t),
  };

  [@bs.send]
  external readQuery: (t, readQueryOptions) => Js.Nullable.t('data) =
    "readQuery";
  [@bs.send]
  external writeQuery: (t, writeQueryOptions('data)) => unit = "writeData";
};
