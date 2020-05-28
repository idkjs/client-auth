open Fragments;

module MeQuery = [%graphql
  {|
  query Me {
    me {
      ...UserFragment.User
    }
  }
|}
];
module ChatsQuery = [%graphql
  {|
    query Chats {
    chats {
      ...ChatFragment.Chat
    }
  }
|}
];
