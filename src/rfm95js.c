
#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


napi_value RFM95js_init(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    0,
    "rfm95:init",
    RFM95js_initExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_initExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_init();
}

napi_value RFM95js_setFrequency(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value argv[1];
  size_t argc = 1;
  int32_t freq;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  status = napi_get_value_int32(env, argv[0], &freq);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to undestand the frequency to set.");
  }

  return RFM95js_promise(
    env,
    freq,
    "rfm95:setFrequency",
    RFM95js_setFrequencyExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_setFrequencyExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_setFrequency(c->num_val);
}

// napi_value RFM95js_setModemConfig(napi_env env, napi_callback_info info) {

// }

napi_value RFM95js_setTxPower(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value argv[1];
  size_t argc = 1;
  int32_t num;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  status = napi_get_value_int32(env, argv[0], &num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to undestand the power to set.");
  }

  return RFM95js_promise(
    env,
    num,
    "rfm95:setTxPower",
    RFM95js_setTxPowerExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_setTxPowerExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_setTxPower(c->num_val);
}

// napi_value RFM95js_available(napi_env env, napi_callback_info info) {

// }

// napi_value RFM95js_recv(napi_env env, napi_callback_info info) {

// }

// napi_value RFM95js_lastRssi(napi_env env, napi_callback_info info) {

// }

napi_value RFM95js_sleep(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_SLEEP,
    "rfm95:sleep",
    RFM95js_setModeExecute,
    RFM95js_promiseComplete
  );
}

napi_value RFM95js_standby(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_STDBY,
    "rfm95:standby",
    RFM95js_setModeExecute,
    RFM95js_promiseComplete
  );
}

napi_value RFM95js_listen(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    RFM95_MODE_RXCONTINUOUS,
    "rfm95:listen",
    RFM95js_listenExecute,
    RFM95js_promiseComplete
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

void RFM95js_promiseComplete(napi_env env, napi_status status, void* data) {
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

/**
 * Enum (eqivelent) of modem configs.
 */
napi_value RFM95js_modemConfigs(napi_env env, const napi_callback_info info) {
  napi_status status;
  napi_value obj;
  status = napi_create_object(env, &obj);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create object.");
  }

  /*
  Bw125Cr45Sf128 = 0,	   ///< Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. Default medium range
	Bw500Cr45Sf128,	           ///< Bw = 500 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on. Fast+short range
	Bw31_25Cr48Sf512,	   ///< Bw = 31.25 kHz, Cr = 4/8, Sf = 512chips/symbol, CRC on. Slow+long range
	Bw125Cr48Sf4096,           ///< Bw = 125 kHz, Cr = 4/8, Sf = 4096chips/symbol, CRC on. Slow+long range
  */
  napi_value num;
  status = napi_create_int32(env, 0, &num);
  status = napi_set_named_property(env, obj, "Bw125Cr45Sf128", num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to use object.");
  }
  status = napi_create_int32(env, 1, &num);
  status = napi_set_named_property(env, obj, "Bw500Cr45Sf128", num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to use object.");
  }
  status = napi_create_int32(env, 2, &num);
  status = napi_set_named_property(env, obj, "Bw31_25Cr48Sf512", num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to use object.");
  }
  status = napi_create_int32(env, 3, &num);
  status = napi_set_named_property(env, obj, "Bw125Cr48Sf4096", num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to use object.");
  }

  return obj;
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
    },
    {
      .utf8name = "getModemConfigs",
      .method = RFM95js_modemConfigs,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    }
  };
  napi_status status = napi_define_properties(env, exports, 4, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
