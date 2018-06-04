
#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


napi_value RFM95js_setMode(napi_env env, napi_callback_info info) {
  napi_value resource_name;
  napi_create_string_utf8(env, "rfm95:setMode", -1, &resource_name);
  return RFM95js_promise(env, info, resource_name, RFM95js_setModeExecute, RFM95js_setModeComplete);
}

void RFM95js_setModeExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_setMode(c->num_val);
}

void RFM95js_setModeComplete(napi_env env, napi_status status, void* data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  napi_value num;
  status = napi_create_int32(env, c->status, &num);
  if (status == napi_ok) {
    if (c->status == RFM95_OK) {
      status = napi_resolve_deferred(env, c->deferred, num);
    } else {
      status = napi_reject_deferred(env, c->deferred, num);
    }
  }

  napi_delete_async_work(env, c->work);
  free(c);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create promise result.");
  }
}

/**
 * Performs the asynchronous work.
 */
void eg_execute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*)data;
  printf("Promise async using num_val = %d\n", c->num_val);
  sleep(3);
}

/**
 * Handle the completion of the asynchronous work.
 */
void eg_complete(napi_env env, napi_status status, void* data) {
  napi_value argv[1];
  status = napi_create_string_utf8(env, "Promise resolved successfully!", NAPI_AUTO_LENGTH, argv);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create resloved message.");
  }

  napi_value global;
  status = napi_get_global(env, &global);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to get global data.");
  }

  RFM95js_data_t* c = (RFM95js_data_t*)data;

  // Resolve or reject the promise associated with the deferred depending on
  // whether the asynchronous action succeeded.
  // Here we assume it's always successfull.
  if (1 == 1) {
    status = napi_resolve_deferred(env, c->deferred, argv[0]);
  } else {
    status = napi_reject_deferred(env, c->deferred, argv[0]);
  }

  napi_delete_async_work(env, c->work);
  free(c);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create promise result.");
  }
}

/**
 * The function called by javascript to get a promise returned.
 */
napi_value eg_promise(napi_env env, napi_callback_info info) {
  napi_value resource_name;
  napi_create_string_utf8(env, "example:promise", -1, &resource_name);
  return RFM95js_promise(env, info, resource_name, eg_execute, eg_complete);
}



/**
 * The function called by javascript to get a promise returned.
 */
napi_value RFM95js_promise(napi_env env, 
  napi_callback_info info, 
  napi_value resource_name,
  napi_async_execute_callback execute,
  napi_async_complete_callback complete) 
  {
  napi_status status;
  napi_value promise;

  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to get javacript data.");
  }

  RFM95js_data_t* c = (RFM95js_data_t*)malloc(sizeof(RFM95js_data_t));
  napi_get_value_int32(env, argv[0], &c->num_val);

  // Create the promise.
  status = napi_create_promise(env, &c->deferred, &promise);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create promise.");
  }

  napi_valuetype valtype;
  napi_typeof(env, argv[0], &valtype);
  // Check for the correct calling of the function.
  if (valtype != napi_number) {
    // Not a number so reject the promise.
    napi_value str[1];
    napi_create_string_utf8(env, "Promise rejected: Argument not a number.", NAPI_AUTO_LENGTH, str);
    napi_reject_deferred(env, c->deferred, str[0]);
    free(c);
  }
  else {
    // Create the async function.
    //napi_create_string_utf8(env, "example:promise", -1, &resource_name);
    napi_create_async_work(env, NULL, resource_name, execute, complete, c, &c->work);
    napi_queue_async_work(env, c->work);
  }

  return promise;
}

napi_value Init(napi_env env, napi_value exports) {

  napi_property_descriptor desc[] = {
    {
      .utf8name = "setMode",
      .method = RFM95js_setMode,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "examplePromise",
      .method = eg_promise,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    }
  };
  napi_status status = napi_define_properties(env, exports, 2, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
