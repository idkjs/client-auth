let str = React.string;

type state = {me: Types.fetch(Types.me, string)};


[@react.component]
let make = () => {
  let (simple, _full) = ApolloHooks.useQuery(Queries.MeQuery.definition);
  <div>
    {switch (simple) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       let me =
         switch (data##me) {
         | Some(value) => value->Js.Nullable.return
         | None => Js.Nullable.null
         };
       Js.log2("Me: ", me);

       let me2 = me->Js.Nullable.toOption;
       Js.log2("Me2: ", me2);
       switch (me2) {
       | Some(me) => <ChatsListScreen me />

       | None => <SignInForm />
       };

     | NoData
     | Error(_) => <p> {React.string("Error")} </p>
     }}
  </div>;
};