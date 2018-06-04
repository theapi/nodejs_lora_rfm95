
#ifndef __rfm95js_H
#define __rfm95js_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <node_api.h>
#include <rfm95.h>

typedef struct {
  int32_t num_val;
  napi_deferred deferred;
  napi_ref callback;
  napi_async_work work;
  RFM95_status_t status;
} RFM95js_data_t;

napi_value RFM95js_setMode(napi_env env, napi_callback_info info);
void RFM95js_setModeExecute(napi_env env, void *data);
void RFM95js_setModeComplete(napi_env env, napi_status status, void* data);

/**
 * Start a promise for a js function.
 */
napi_value RFM95js_promise(
  napi_env env, 
  napi_callback_info info, 
  napi_value async_resource_name,
  napi_async_execute_callback execute,
  napi_async_complete_callback complete
);


#ifdef __cplusplus
}
#endif
#endif /*__rfm95js_H */
