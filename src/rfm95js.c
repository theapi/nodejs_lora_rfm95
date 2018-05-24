#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdio.h>
#include <unistd.h>

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

/* @todo Async */
napi_value RFM95js_sleep(napi_env env, napi_callback_info info) {
  napi_value val;

  RFM95_StatusTypeDef rfm95_status = RFM95_setMode(RFM95_MODE_SLEEP);

  napi_status status = napi_create_int32(env, rfm95_status, &val);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return val;
}

napi_value RFM95js_rxContinuous(napi_env env, napi_callback_info info) {
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

void bye_async_execute(napi_env env, void *data)
{
	sleep(1);
	printf("Hello async\n");
}

void bye_async_complete(napi_env env, napi_status status, void* data)
{
	printf("Hello completed async\n");
}

napi_value bye_async(napi_env env, napi_callback_info info)
{
	napi_value retval;
	napi_async_work work;
	napi_value async_resource_name;

	/*
	 * napi_status napi_create_async_work(napi_env env,
                                   napi_value async_resource,
                                   napi_value async_resource_name,
                                   napi_async_execute_callback execute,
                                   napi_async_complete_callback complete,
                                   void* data,
                                   napi_async_work* result);
	 * async_resource_name should be a null-terminated, UTF-8-encoded string.
	 * Note: The async_resource_name identifier is provided by the user and should be representative of the type of async work being performed. It is also recommended to apply namespacing to the identifier, e.g. by including the module name.
	 * See the async_hooks documentation for more information.
	 */
	napi_create_string_utf8(env, "bye:sleep", -1, &async_resource_name);
	napi_create_async_work(env, NULL, async_resource_name, bye_async_execute, bye_async_complete, NULL, &work);
	napi_queue_async_work(env, work);

	napi_create_int64(env, 1373, &retval);

	return retval;
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

  status = napi_create_function(env, NULL, 0, RFM95js_sleep, NULL, &fn_sleep);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "sleep", fn_sleep);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  status = napi_create_function(env, NULL, 0, RFM95js_rxContinuous, NULL, &fn_rxC);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }
  status = napi_set_named_property(env, exports, "listen", fn_rxC);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  napi_property_descriptor desc[] = {
  		{
  			.utf8name = "byeASync",
  			.method = bye_async,
  			.getter = NULL,
  			.setter = NULL,
  			.value = NULL,
  			.attributes = napi_default,
  			.data = NULL
  		}
  	};
  status = napi_define_properties(env, exports, 2, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
