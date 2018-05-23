#include <node_api.h>
#include "rfm95.h"

/**
 * Just a hello world example function as a start.
 */
napi_value Hello(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  int number = 0;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  status = napi_get_value_int32(env, argv[0], &number);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }
  napi_value myNumber;
  number = number * 2;
  status = napi_create_int32(env, number, &myNumber);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return myNumber;
}


napi_value RFM95_sleep(napi_env env, napi_callback_info info) {
  napi_status status;
  uint8_t mode;
  napi_value response;

  mode = RFM95_MODE_SLEEP;

  /* @todo Really set the mode */
  status = napi_create_int32(env, mode, &response);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return response;
}

napi_value RFM95_rxContinuous(napi_env env, napi_callback_info info) {
  napi_status status;
  uint8_t mode;
  napi_value response;

  mode = RFM95_MODE_RXCONTINUOUS;

  /* @todo Really set the mode */
  status = napi_create_int32(env, mode, &response);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return response;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn_hello;
  napi_value fn_sleep;
  napi_value fn_rxC;

  status = napi_create_function(env, NULL, 0, Hello, NULL, &fn_hello);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "hello", fn_hello);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_create_function(env, NULL, 0, RFM95_sleep, NULL, &fn_sleep);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "sleep", fn_sleep);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_create_function(env, NULL, 0, RFM95_rxContinuous, NULL, &fn_rxC);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "listen", fn_rxC);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
