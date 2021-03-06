
#include <node_api.h>
#include "rfm95js.h"
#include "rfm95.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


napi_value RFM95js_init(napi_env env, napi_callback_info info) {

  #ifdef RFM95_RPI
    printf("It's a Pi!\n");
  #else
    printf("Not a Raspberry\n");
  #endif

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

napi_value RFM95js_setModemConfig(napi_env env, napi_callback_info info) {
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
    napi_throw_error(env, NULL, "Failed to undestand the frequency to set.");
  }

  return RFM95js_promise(
    env,
    num,
    "rfm95:setModemConfig",
    RFM95js_setModemConfigExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_setModemConfigExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_setModemConfig(c->num_val);
}

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

napi_value RFM95js_available(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    0,
    "rfm95:available",
    RFM95js_availableExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_availableExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  c->status = RFM95_available();
}

napi_value RFM95js_recv(napi_env env, napi_callback_info info) {
  return RFM95js_promise(
    env,
    0,
    "rfm95:recv",
    RFM95js_recvExecute,
    RFM95js_promiseComplete
  );
}

void RFM95js_recvExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  uint8_t buf[32];
  uint8_t len[32];
  //@todo do this properly; return the buffer etc
  c->status = RFM95_recv(buf, len);
}

// napi_value RFM95js_lastRssi(napi_env env, napi_callback_info info) {

// }

napi_value RFM95js_readRegister(napi_env env, napi_callback_info info) {
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
    napi_throw_error(env, NULL, "Failed to undestand the register address.");
  }

  return RFM95js_promise(
    env,
    num,
    "rfm95:readRegister",
    RFM95js_readRegisterExecute,
    RFM95js_readRegisterComplete
  );
}

void RFM95js_readRegisterExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  uint8_t val = RFM95_readRegister(c->num_val);
  c->num_val = val;
  c->status = RFM95_OK;
  //printf("reg: 0x%02X\n", val);
}

void RFM95js_readRegisterComplete(napi_env env, napi_status status, void* data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;

  char msg[64];
  sprintf(msg, "Failed to read register. RFM95_status_t = %d", c->status);
  napi_value err;
  status = napi_create_string_utf8(env, msg, NAPI_AUTO_LENGTH, &err);

  napi_value num;
  status = napi_create_int32(env, c->num_val, &num);
  if (status == napi_ok) {
    if (c->status == RFM95_OK) {
      status = napi_resolve_deferred(env, c->deferred, num);
    } else {
      status = napi_reject_deferred(env, c->deferred, err);
    }
  }

  napi_delete_async_work(env, c->work);
  free(c);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create promise result.");
  }
}

napi_value RFM95js_writeRegister(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value argv[2];
  size_t argc = 2;
  int32_t num;
  int32_t addr;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  status = napi_get_value_int32(env, argv[0], &addr);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to undestand the register address.");
  }

  status = napi_get_value_int32(env, argv[1], &num);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to undestand the register value to set.");
  }

  RFM95js_data_t* c = (RFM95js_data_t*) malloc(sizeof(RFM95js_data_t));
  c->num_val = num;
  c->addr_val = addr;
  c->resource_name = "rfm95:writeRegister";

  // Create the promise.
  napi_value promise;
  status = napi_create_promise(env, &c->deferred, &promise);
  if (status != napi_ok) {
    free(c);
    napi_throw_error(env, NULL, "Unable to create promise.");
  }

  napi_value resource_name;
  napi_create_string_utf8(env, c->resource_name, -1, &resource_name);

  // Create the async function.
  napi_create_async_work(env, NULL, resource_name,
    RFM95js_writeRegisterExecute, RFM95js_writeRegisterComplete, c, &c->work);
  napi_queue_async_work(env, c->work);

  return promise;
}

void RFM95js_writeRegisterExecute(napi_env env, void *data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;
  RFM95_writeRegister(c->addr_val, c->num_val);
}

void RFM95js_writeRegisterComplete(napi_env env, napi_status status, void* data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;

  napi_value num;
  status = napi_create_int32(env, c->num_val, &num);
  if (status == napi_ok) {
    status = napi_resolve_deferred(env, c->deferred, num);
  } else {
    status = napi_reject_deferred(env, c->deferred, num);
  }

  napi_delete_async_work(env, c->work);
  free(c);
}

void RFM95js_promiseComplete(napi_env env, napi_status status, void* data) {
  RFM95js_data_t* c = (RFM95js_data_t*) data;

  char msg[64];
  sprintf(msg, "%s : %d", c->resource_name, c->status);

  napi_value js_msg;
  status = napi_create_string_utf8(env, msg, NAPI_AUTO_LENGTH, &js_msg);
  if (status == napi_ok) {
    if (c->status == RFM95_OK) {
      status = napi_resolve_deferred(env, c->deferred, js_msg);
    } else {
      status = napi_reject_deferred(env, c->deferred, js_msg);
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
  c->resource_name = name;

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
      .utf8name = "init",
      .method = RFM95js_init,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "setFrequency",
      .method = RFM95js_setFrequency,
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
    },
    {
      .utf8name = "setModemConfig",
      .method = RFM95js_setModemConfig,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "setTxPower",
      .method = RFM95js_setTxPower,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "available",
      .method = RFM95js_available,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "recv",
      .method = RFM95js_recv,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "readRegister",
      .method = RFM95js_readRegister,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    },
    {
      .utf8name = "writeRegister",
      .method = RFM95js_writeRegister,
      .getter = NULL,
      .setter = NULL,
      .value = NULL,
      .attributes = napi_default,
      .data = NULL
    }
  };
  napi_status status = napi_define_properties(env, exports, 9, desc);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
