
#ifndef __rfm95js_H
#define __rfm95js_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <node_api.h>

typedef struct {
  int32_t num_val;
  napi_ref callback;
  napi_async_work work;
} RFM95js_data_t;

napi_value RFM95js_sleep(napi_env env, napi_callback_info info);
napi_value RFM95js_rxContinuous(napi_env env, napi_callback_info info);


#ifdef __cplusplus
}
#endif
#endif /*__rfm95js_H */
