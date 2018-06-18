
#ifndef __rfm95js_H
#define __rfm95js_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <node_api.h>
#include <rfm95.h>

typedef struct {
  int32_t num_val;
  int32_t addr_val;
  napi_deferred deferred;
  napi_ref callback;
  napi_async_work work;
  char* resource_name;
  RFM95_status_t status;
} RFM95js_data_t;

napi_value RFM95js_init(napi_env env, napi_callback_info info);
napi_value RFM95js_setFrequency(napi_env env, napi_callback_info info);
napi_value RFM95js_setModemConfig(napi_env env, napi_callback_info info);
napi_value RFM95js_setTxPower(napi_env env, napi_callback_info info);
napi_value RFM95js_available(napi_env env, napi_callback_info info);
napi_value RFM95js_recv(napi_env env, napi_callback_info info);
napi_value RFM95js_lastRssi(napi_env env, napi_callback_info info);

napi_value RFM95js_readRegister(napi_env env, napi_callback_info info);
void RFM95js_readRegisterExecute(napi_env env, void *data);
void RFM95js_readRegisterComplete(napi_env env, napi_status status, void* data);
napi_value RFM95js_writeRegister(napi_env env, napi_callback_info info);
void RFM95js_writeRegisterExecute(napi_env env, void *data);
void RFM95js_writeRegisterComplete(napi_env env, napi_status status, void* data);

/**
 * Start a promise for a js function.
 */
napi_value RFM95js_promise(
  napi_env env,
  int32_t number,
  char *name,
  napi_async_execute_callback execute,
  napi_async_complete_callback complete
);
void RFM95js_promiseComplete(napi_env env, napi_status status, void* data);

void RFM95js_initExecute(napi_env env, void *data);
void RFM95js_setFrequencyExecute(napi_env env, void *data);
void RFM95js_setTxPowerExecute(napi_env env, void *data);
void RFM95js_setModemConfigExecute(napi_env env, void *data);
void RFM95js_availableExecute(napi_env env, void *data);
void RFM95js_recvExecute(napi_env env, void *data);


#ifdef __cplusplus
}
#endif
#endif /*__rfm95js_H */
