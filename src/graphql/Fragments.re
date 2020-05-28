module UserFragment = [%graphql
  {|
  fragment User on User {
    id
    name
    picture
  }
|}
];

module MessageFragment = [%graphql
  {|
  fragment Message on Message {
    id
    createdAt
    content
    isMine
    chat {
      id
    }
  }
|}
];

module ChatFragment = [%graphql
  {|
  fragment Chat on Chat {
      id
      name
      picture
      lastMessage {
        ...MessageFragment.Message
      }
    }
  |}
];

module MessagesResultFragment = [%graphql
  {|
  fragment MessagesResult on MessagesResult {
    cursor
    hasMore
    messages {
      ...MessageFragment.Message
    }
  }
  |}
];

// module FullChatFragment = [%graphql
//   {|
//   fragment FullChat on Chat {
//     ...ChatFragment.Chat
//     messages(limit: $limit, after: $after) @connection(key: "messages") {
//       ...MessagesResultFragment.MessagesResult.messages
//     }
//   }
// |}
// ];
