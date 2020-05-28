// const Container = [%styled.div {|
//   background: radial-gradient(rgb(34, 65, 67), rgb(17, 48, 50)),
//     url(/assets/chat-background.jpg) no-repeat;
//   background-size: cover;
//   background-blend-mode: multiply;
//   color: white;
//  |};
module Container = [%styled
  {|
  text-align: center;
  margin-top: 3rem;
  color: white;
|}
];

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

module SignForm = [%styled.div {|
  height: 75px;
|}];

module ActualForm = [%styled.form {|
  padding: 20px;
|}];

module App = [%styled.div (~background) => {j|
  position: absolute;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;

  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;

  background-color: $background;

  cursor: pointer;

  & > div {
    padding: 20px;
  }
|j}];

module Section = [%styled.div (~sectionWidth:string) => {|
  padding-bottom: 35px;
  width: $sectionWidth;
|}];

module Legend = [%styled.legend {|
  font-weight: 400;
  color: white;
|}];

module Label = [%styled.label {|
  color: white !important;
|}];

module Input = [%styled.input (~primaryBg) =>
  {|
  color: white;

  &::placeholder {
    color: $primaryBg;
  }
|}
];

module ErrorMessage = [%styled.div
  {|
  position: fixed;
  color: red;
  font-size: 15px;
  margin-top: 20px;
|}
];

module TextField = [%styled.div
{|
  width: 100%;
  position: relative;
  input {
    color: white !important;

    &::placeholder {
      color: red !important;
    }
  };

  > div::before {
    border-color: white !important;
  }
|}];

module Button = [%styled.button{|
width: 100px;
  display: block !important;
  margin: auto !important;
  background-color: green !important;

|}];
// module TextField = [%styled.div (~primaryBg) =>
// {|
//   width: 100%;
//   position: relative;
//   input {
//     color: white !important;

//     &::placeholder {
//       color: $primaryBg !important;
//     }
//   };

//   > div::before {
//     border-color: white !important;
//   }
// |}];

// module Button = [%styled.button (~secondaryBg) =>{|
// width: 100px;
//   display: block !important;
//   margin: auto !important;
//   background-color: $secondaryBg !important;

// |}];