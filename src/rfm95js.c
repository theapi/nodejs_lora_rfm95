#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdio.h>
#include <unistd.h>

#include <assert.h>

typedef struct carrier{
int32_t _input;
int32_t _output;
napi_ref _callback;
napi_async_work _request;
}carrier;

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



/* async example from https://github.com/1995parham/Napi101 */
napi_value bye_sync(napi_env env, napi_callback_info info) {
	napi_value retval;

	printf("Hello sync\n");
	sleep(1);
	printf("Bye sync\n");

	napi_create_int64(env, 1373, &retval);

	return retval;
}

void bye_async_execute(napi_env env, void *data) {
	printf("Hello async\n");
	sleep(3);
}

void bye_async_complete(napi_env env, napi_status status, void* data) {
	printf("Hello completed async\n");

  napi_value argv[1];
  status = napi_create_string_utf8(env, "HeY!!! an async callback!", NAPI_AUTO_LENGTH, argv);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global(env, &global);
  assert(status == napi_ok);

  napi_value result;

  napi_ref cb_ref = (napi_ref)data;
  napi_value cb;
	napi_get_reference_value(env, cb_ref, &cb);

  printf("cb %p\n", cb);
  status = napi_call_function(env, global, cb, 1, argv, &result);
  printf("status %u\n", status);
  assert(status == napi_ok);
  napi_delete_reference(env, cb_ref);
  //@todo delete async work too
  //napi_delete_async_work(env, cb);
}

napi_value bye_async(napi_env env, napi_callback_info info) {
	napi_value retval;
	napi_async_work work;
	napi_value async_resource_name;


  //carrier* c=(carrier*)malloc(sizeof(carrier));

  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  //napi_ref cb = args[0];
  napi_ref cb;
  napi_create_reference(env, args[0], 1, &cb);
  printf("cb %p\n", cb);


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
	napi_create_async_work(env, NULL, async_resource_name, bye_async_execute, bye_async_complete, cb, &work);
	napi_queue_async_work(env, work);

	napi_create_int64(env, 1373, &retval);

	return retval;
}

// https://github.com/nodejs/abi-stable-node-addon-examples/blob/master/3_callbacks/napi/addon.js

napi_value RunCallback(napi_env env, const napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  napi_value cb = args[0];
//printf("cb %p\n", args[0]);
  napi_value argv[1];
  status = napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, argv);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global(env, &global);
  assert(status == napi_ok);

  napi_value result;
  status = napi_call_function(env, global, cb, 1, argv, &result);
  assert(status == napi_ok);

  return NULL;
}

napi_value Init(napi_env env, napi_value exports) {

  napi_property_descriptor desc[] = {
    {
      .utf8name = "hello",
      .method = Hello,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "sleep",
      .method = RFM95js_sleep,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "listen",
      .method = RFM95js_rxContinuous,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "byeSync",
      .method = bye_sync,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "byeASync",
      .method = bye_async,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "cbtest",
      .method = RunCallback,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    }
  };
  napi_status status = napi_define_properties(env, exports, 6, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
