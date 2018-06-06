
#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

napi_value RFM95js_sleep(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_SLEEP,
    "rfm95:sleep",
    RFM95js_setModeExecute,
    RFM95js_setModeComplete
  );
}

napi_value RFM95js_standby(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_STDBY,
    "rfm95:standby",
    RFM95js_setModeExecute,
    RFM95js_setModeComplete
  );
}

napi_value RFM95js_listen(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_RXCONTINUOUS,
    "rfm95:listen",
    RFM95js_listenExecute,
    RFM95js_setModeComplete
  );
}

void RFM95js_listenExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_setMode(c->num_val);

  /* Wait for a message */
  sleep(5);

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
 * Boilerplate promise creation.
 */
napi_value RFM95js_promise(
    napi_env env,
    int32_t number,
    char *name,
    napi_async_execute_callback execute,
    napi_async_complete_callback complete) {

  RFM95js_data_t* c = (RFM95js_data_t*) malloc(sizeof(RFM95js_data_t));
  c->num_val = number;

  // Create the promise.
  napi_value promise;
  napi_status status;
  status = napi_create_promise(env, &c->deferred, &promise);
  if (status != napi_ok) {
    free(c);
    napi_throw_error(env, NULL, "Unable to create promise.");
  }

  napi_value resource_name;
  napi_create_string_utf8(env, name, -1, &resource_name);

  // Create the async function.
  napi_create_async_work(env, NULL, resource_name, execute, complete, c, &c->work);
  napi_queue_async_work(env, c->work);

  return promise;
}

napi_value Init(napi_env env, napi_value exports) {

  napi_property_descriptor desc[] = {
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
      .utf8name = "standby",
      .method = RFM95js_standby,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "listen",
      .method = RFM95js_listen,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    }
  };
  napi_status status = napi_define_properties(env, exports, 3, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
