// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_obj from "bs-platform/lib/es6/caml_obj.js";
import * as ReSchema from "reschema/src/ReSchema.bs.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as ReactUpdate from "reason-react-update/src/ReactUpdate.bs.js";
import * as ReSchemaI18n from "reschema/src/ReSchemaI18n.bs.js";

function Make(Config) {
  var ReSchema$1 = ReSchema.Make(Config);
  var getInitialFieldsState = function (schema) {
    return Belt_Array.map(schema._0, (function (validator) {
                  return [
                          /* Field */{
                            _0: validator._0
                          },
                          /* Pristine */0
                        ];
                }));
  };
  var formContext = React.createContext(undefined);
  var useFormContext = function (param) {
    return React.useContext(formContext);
  };
  var useField = function (field) {
    var $$interface = React.useContext(formContext);
    return Belt_Option.map($$interface, (function (param) {
                  var validateField = param.validateField;
                  return {
                          handleChange: Curry._1(param.handleChange, field),
                          error: Curry._1(param.getFieldError, /* Field */{
                                _0: field
                              }),
                          state: Curry._1(param.getFieldState, /* Field */{
                                _0: field
                              }),
                          validate: (function (param) {
                              return Curry._1(validateField, /* Field */{
                                          _0: field
                                        });
                            }),
                          value: Curry._2(Config.get, param.state.values, field)
                        };
                }));
  };
  var makeProps = function (value, children, param) {
    return {
            value: Caml_option.some(value),
            children: children
          };
  };
  var make = formContext.Provider;
  var Provider = {
    makeProps: makeProps,
    make: make
  };
  var ReForm$Make$Field = function (Props) {
    var field = Props.field;
    var render = Props.render;
    var renderOnMissingContextOpt = Props.renderOnMissingContext;
    var renderOnMissingContext = renderOnMissingContextOpt !== undefined ? Caml_option.valFromOption(renderOnMissingContextOpt) : null;
    var fieldInterface = useField(field);
    return React.useMemo((function () {
                  return Belt_Option.getWithDefault(Belt_Option.map(fieldInterface, render), renderOnMissingContext);
                }), [
                Belt_Option.getWithDefault(Belt_Option.flatMap(fieldInterface, (function (param) {
                            return param.error;
                          })), ""),
                Belt_Option.map(fieldInterface, (function (param) {
                        return param.value;
                      })),
                Belt_Option.map(fieldInterface, (function (param) {
                        return param.state;
                      }))
              ]);
  };
  var Field = {
    make: ReForm$Make$Field
  };
  var use = function (initialState, schema, onSubmit, onSubmitFailOpt, i18nOpt, validationStrategyOpt, param) {
    var onSubmitFail = onSubmitFailOpt !== undefined ? onSubmitFailOpt : (function (prim) {
          
        });
    var i18n = i18nOpt !== undefined ? i18nOpt : ReSchemaI18n.$$default;
    var validationStrategy = validationStrategyOpt !== undefined ? validationStrategyOpt : /* OnChange */0;
    var match = ReactUpdate.useReducer({
          formState: /* Pristine */2,
          values: initialState,
          fieldsState: getInitialFieldsState(schema)
        }, (function (action, state) {
            if (typeof action === "number") {
              switch (action) {
                case /* TrySubmit */0 :
                    return {
                            TAG: /* SideEffects */2,
                            _0: (function (self) {
                                Curry._1(self.send, {
                                      TAG: /* ValidateForm */1,
                                      _0: true
                                    });
                                
                              })
                          };
                case /* Submit */1 :
                    return {
                            TAG: /* UpdateWithSideEffects */1,
                            _0: {
                              formState: /* Submitting */1,
                              values: state.values,
                              fieldsState: state.fieldsState
                            },
                            _1: (function (self) {
                                return Curry._1(onSubmit, {
                                            send: self.send,
                                            state: self.state,
                                            raiseSubmitFailed: (function (error) {
                                                return Curry._1(self.send, {
                                                            TAG: /* RaiseSubmitFailed */13,
                                                            _0: error
                                                          });
                                              })
                                          });
                              })
                          };
                case /* ResetForm */2 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: /* Pristine */2,
                              values: initialState,
                              fieldsState: getInitialFieldsState(schema)
                            }
                          };
                
              }
            } else {
              switch (action.TAG | 0) {
                case /* ValidateField */0 :
                    var field = action._0;
                    return {
                            TAG: /* SideEffects */2,
                            _0: (function (self) {
                                var fieldState = Curry._4(ReSchema$1.validateOne, field, self.state.values, i18n, schema);
                                var newFieldState = Belt_Option.map(fieldState, (function (param) {
                                        var message = param[1];
                                        if (message) {
                                          return /* Error */{
                                                  _0: message._0
                                                };
                                        } else {
                                          return /* Valid */1;
                                        }
                                      }));
                                var newFieldsState = Belt_Array.concat(Belt_Array.keep(state.fieldsState, (function (elem) {
                                            return Caml_obj.caml_notequal(elem[0], field);
                                          })), newFieldState !== undefined ? [[
                                          field,
                                          newFieldState
                                        ]] : []);
                                Curry._1(self.send, {
                                      TAG: /* SetFieldsState */2,
                                      _0: newFieldsState
                                    });
                                
                              })
                          };
                case /* ValidateForm */1 :
                    var submit = action._0;
                    return {
                            TAG: /* SideEffects */2,
                            _0: (function (self) {
                                var recordState = Curry._3(ReSchema$1.validate, i18n, self.state.values, schema);
                                if (recordState) {
                                  var newFieldsState = Belt_Array.map(recordState._0, (function (param) {
                                          return [
                                                  param[0],
                                                  /* Error */{
                                                    _0: param[1]
                                                  }
                                                ];
                                        }));
                                  Curry._1(self.send, {
                                        TAG: /* SetFieldsState */2,
                                        _0: newFieldsState
                                      });
                                  if (submit) {
                                    Curry._1(onSubmitFail, {
                                          send: self.send,
                                          state: self.state,
                                          raiseSubmitFailed: (function (error) {
                                              return Curry._1(self.send, {
                                                          TAG: /* RaiseSubmitFailed */13,
                                                          _0: error
                                                        });
                                            })
                                        });
                                  }
                                  Curry._1(self.send, {
                                        TAG: /* SetFormState */10,
                                        _0: /* Errored */3
                                      });
                                } else {
                                  Curry._1(self.send, {
                                        TAG: /* SetFormState */10,
                                        _0: /* Valid */4
                                      });
                                  if (submit) {
                                    Curry._1(self.send, /* Submit */1);
                                  }
                                  
                                }
                                
                              })
                          };
                case /* SetFieldsState */2 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: state.values,
                              fieldsState: action._0
                            }
                          };
                case /* FieldChangeState */3 :
                    return /* NoUpdate */0;
                case /* FieldChangeValue */4 :
                    var field$1 = action._0;
                    return {
                            TAG: /* UpdateWithSideEffects */1,
                            _0: {
                              formState: state.formState === /* Errored */3 ? /* Errored */3 : /* Dirty */0,
                              values: Curry._3(Config.set, state.values, field$1, action._1),
                              fieldsState: state.fieldsState
                            },
                            _1: (function (self) {
                                if (validationStrategy) {
                                  
                                } else {
                                  Curry._1(self.send, {
                                        TAG: /* ValidateField */0,
                                        _0: /* Field */{
                                          _0: field$1
                                        }
                                      });
                                }
                                
                              })
                          };
                case /* FieldChangeValueWithCallback */5 :
                    var field$2 = action._0;
                    var oldValue = Curry._2(Config.get, state.values, field$2);
                    return {
                            TAG: /* UpdateWithSideEffects */1,
                            _0: {
                              formState: state.formState === /* Errored */3 ? /* Errored */3 : /* Dirty */0,
                              values: Curry._3(Config.set, state.values, field$2, Curry._1(action._1, oldValue)),
                              fieldsState: state.fieldsState
                            },
                            _1: (function (self) {
                                if (validationStrategy) {
                                  
                                } else {
                                  Curry._1(self.send, {
                                        TAG: /* ValidateField */0,
                                        _0: /* Field */{
                                          _0: field$2
                                        }
                                      });
                                }
                                
                              })
                          };
                case /* FieldArrayAdd */6 :
                    var field$3 = action._0;
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: Curry._3(Config.set, state.values, field$3, Belt_Array.concat(Curry._2(Config.get, state.values, field$3), [action._1])),
                              fieldsState: state.fieldsState
                            }
                          };
                case /* FieldArrayUpdateByIndex */7 :
                    var index = action._2;
                    var value = action._1;
                    var field$4 = action._0;
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: Curry._3(Config.set, state.values, field$4, Belt_Array.mapWithIndex(Curry._2(Config.get, state.values, field$4), (function (i, currentValue) {
                                          if (i === index) {
                                            return value;
                                          } else {
                                            return currentValue;
                                          }
                                        }))),
                              fieldsState: state.fieldsState
                            }
                          };
                case /* FieldArrayRemove */8 :
                    var index$1 = action._1;
                    var field$5 = action._0;
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: Curry._3(Config.set, state.values, field$5, Belt_Array.keepWithIndex(Curry._2(Config.get, state.values, field$5), (function (param, i) {
                                          return i !== index$1;
                                        }))),
                              fieldsState: state.fieldsState
                            }
                          };
                case /* FieldArrayRemoveBy */9 :
                    var predicate = action._1;
                    var field$6 = action._0;
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: Curry._3(Config.set, state.values, field$6, Belt_Array.keep(Curry._2(Config.get, state.values, field$6), (function (entry) {
                                          return !Curry._1(predicate, entry);
                                        }))),
                              fieldsState: state.fieldsState
                            }
                          };
                case /* SetFormState */10 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: action._0,
                              values: state.values,
                              fieldsState: state.fieldsState
                            }
                          };
                case /* SetValues */11 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: action._0,
                              fieldsState: state.fieldsState
                            }
                          };
                case /* SetFieldValue */12 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: state.formState,
                              values: Curry._3(Config.set, state.values, action._0, action._1),
                              fieldsState: state.fieldsState
                            }
                          };
                case /* RaiseSubmitFailed */13 :
                    return {
                            TAG: /* Update */0,
                            _0: {
                              formState: /* SubmitFailed */{
                                _0: action._0
                              },
                              values: state.values,
                              fieldsState: state.fieldsState
                            }
                          };
                
              }
            }
          }));
    var send = match[1];
    var state = match[0];
    var getFieldState = function (field) {
      var field$1 = Belt_List.getBy($$Array.to_list(state.fieldsState), (function (param) {
              var match = Caml_obj.caml_equal(param[0], field);
              if (match) {
                return true;
              } else {
                return false;
              }
            }));
      if (field$1 !== undefined) {
        return field$1[1];
      } else {
        return /* Pristine */0;
      }
    };
    var getFieldError = function (field) {
      var error = getFieldState(field);
      if (typeof error === "number") {
        return ;
      } else {
        return error._0;
      }
    };
    var validateFields = function (fields) {
      var fieldsValidated = Curry._4(ReSchema$1.validateFields, fields, state.values, i18n, schema);
      var newFieldsState = Belt_Array.reduce(Belt_Array.map(state.fieldsState, (function (fieldStateItem) {
                  var field = fieldStateItem[0];
                  if (!Belt_Array.some(fields, (function (fieldItem) {
                            return Caml_obj.caml_equal(fieldItem, field);
                          }))) {
                    return [fieldStateItem];
                  }
                  var newFieldState = Belt_Array.get(Belt_Array.keep(fieldsValidated, (function (fieldStateValidated) {
                              return Caml_obj.caml_equal(Belt_Option.map(fieldStateValidated, (function (param) {
                                                return param[0];
                                              })), field);
                            })), 0);
                  if (newFieldState === undefined) {
                    return [];
                  }
                  var fieldStateValidated = Caml_option.valFromOption(newFieldState);
                  if (fieldStateValidated === undefined) {
                    return [];
                  }
                  var newFieldStateValidated = fieldStateValidated[1];
                  if (newFieldStateValidated) {
                    return [[
                              field,
                              /* Error */{
                                _0: newFieldStateValidated._0
                              }
                            ]];
                  } else {
                    return [[
                              field,
                              /* Valid */1
                            ]];
                  }
                })), [], Belt_Array.concat);
      Curry._1(send, {
            TAG: /* SetFieldsState */2,
            _0: newFieldsState
          });
      return Belt_Array.map(Belt_Array.keep(newFieldsState, (function (param) {
                        var field = param[0];
                        return Belt_Array.some(fields, (function (fieldItem) {
                                      return Caml_obj.caml_equal(fieldItem, field);
                                    }));
                      })), (function (fieldState) {
                    return fieldState[1];
                  }));
    };
    var raiseSubmitFailed = function (error) {
      return Curry._1(send, {
                  TAG: /* RaiseSubmitFailed */13,
                  _0: error
                });
    };
    return {
            state: state,
            getFieldState: getFieldState,
            getFieldError: getFieldError,
            handleChange: (function (field, value) {
                return Curry._1(send, {
                            TAG: /* FieldChangeValue */4,
                            _0: field,
                            _1: value
                          });
              }),
            handleChangeWithCallback: (function (field, updateFn) {
                return Curry._1(send, {
                            TAG: /* FieldChangeValueWithCallback */5,
                            _0: field,
                            _1: updateFn
                          });
              }),
            arrayPush: (function (field, value) {
                return Curry._1(send, {
                            TAG: /* FieldArrayAdd */6,
                            _0: field,
                            _1: value
                          });
              }),
            arrayUpdateByIndex: (function (field, index, value) {
                return Curry._1(send, {
                            TAG: /* FieldArrayUpdateByIndex */7,
                            _0: field,
                            _1: value,
                            _2: index
                          });
              }),
            arrayRemoveByIndex: (function (field, index) {
                return Curry._1(send, {
                            TAG: /* FieldArrayRemove */8,
                            _0: field,
                            _1: index
                          });
              }),
            arrayRemoveBy: (function (field, predicate) {
                return Curry._1(send, {
                            TAG: /* FieldArrayRemoveBy */9,
                            _0: field,
                            _1: predicate
                          });
              }),
            submit: (function (param) {
                return Curry._1(send, /* TrySubmit */0);
              }),
            resetForm: (function (param) {
                return Curry._1(send, /* ResetForm */2);
              }),
            setValues: (function (values) {
                return Curry._1(send, {
                            TAG: /* SetValues */11,
                            _0: values
                          });
              }),
            setFieldValue: (function (field, value, shouldValidateOpt, param) {
                var shouldValidate = shouldValidateOpt !== undefined ? shouldValidateOpt : true;
                if (shouldValidate) {
                  return Curry._1(send, {
                              TAG: /* FieldChangeValue */4,
                              _0: field,
                              _1: value
                            });
                } else {
                  return Curry._1(send, {
                              TAG: /* SetFieldValue */12,
                              _0: field,
                              _1: value
                            });
                }
              }),
            validateField: (function (field) {
                return Curry._1(send, {
                            TAG: /* ValidateField */0,
                            _0: field
                          });
              }),
            validateForm: (function (param) {
                return Curry._1(send, {
                            TAG: /* ValidateForm */1,
                            _0: false
                          });
              }),
            validateFields: validateFields,
            raiseSubmitFailed: raiseSubmitFailed
          };
  };
  return {
          ReSchema: ReSchema$1,
          Validation: undefined,
          getInitialFieldsState: getInitialFieldsState,
          formContext: formContext,
          useFormContext: useFormContext,
          useField: useField,
          Provider: Provider,
          Field: Field,
          use: use
        };
}

export {
  Make ,
  
}
/* react Not a pure module */
