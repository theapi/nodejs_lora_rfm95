
#ifndef __rfm95js_H
#define __rfm95js_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <node_api.h>


napi_value RFM95js_sleep(napi_env env, napi_callback_info info);
napi_value RFM95js_rxContinuous(napi_env env, napi_callback_info info);


#ifdef __cplusplus
}
#endif
#endif /*__rfm95js_H */
