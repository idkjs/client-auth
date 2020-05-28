open Fragments;
module ChatAddedSubscription = [%graphql
  {|
  subscription ChatAdded {
    chatAdded {
      ...ChatFragment.Chat
    }
  }
 |}
];

module ChatRemovedSubscription = [%graphql
  {|
  subscription ChatRemoved {
    chatRemoved
  }
 |}
];
module MessageAddedSubscription = [%graphql
  {|
  subscription MessageAdded {
    messageAdded {
      ...MessageFragment.Message
    }
  }
 |}
];