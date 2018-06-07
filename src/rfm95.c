
#include "rfm95.h"
#include <stdbool.h>


RFM95_status_t RFM95_init() {
  return RFM95_OK;
}

RFM95_status_t RFM95_setFrequency(int32_t freq) {
  return RFM95_OK;
}

RFM95_status_t RFM95_setModemConfig(uint8_t mc) {
  return RFM95_OK;
}

RFM95_status_t RFM95_setTxPower(int8_t power) {
  return RFM95_OK;
}

RFM95_status_t RFM95_setMode(uint8_t mode) {
  return RFM95_OK;
}

bool RFM95_available() {
  return true;
}

bool RFM95_recv(uint8_t* buf, uint8_t* len) {
  return true;
}

int16_t RFM95_lastRssi() {
  return 123;
}
