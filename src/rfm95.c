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


napi_value RFM95_setMode(napi_env env, napi_callback_info info){
  napi_status status;
  size_t argc = 1;
  int mode = 0;
  napi_value argv[1];
  napi_value response;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  /* Get the requested mode value from the first argument */
  status = napi_get_value_int32(env, argv[0], &mode);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid number was passed as argument");
  }

  /* Do work with the mode value */

  /* Fake response using a defined value */
  status = napi_create_int32(env, RFM95_LOW_FREQUENCY_MODE, &response);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return response;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn_hello;
  napi_value fn_setMode;

  status = napi_create_function(env, NULL, 0, Hello, NULL, &fn_hello);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "hello", fn_hello);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_create_function(env, NULL, 0, RFM95_setMode, NULL, &fn_setMode);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "setMode", fn_setMode);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
