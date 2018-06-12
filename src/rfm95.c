

#include <rfm95spi.h>
#include <rfm95.h>
#include <stdbool.h>
#include <unistd.h>

RFM95_status_t RFM95_init() {
  RFM95_status_t status;
  status = RFM95spi_init();
  if (status != RFM95_OK) {
    return status;
  }

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

RFM95_status_t RFM95_available() {
  sleep(5);
  return RFM95_OK;
}

RFM95_status_t RFM95_recv(uint8_t* buf, uint8_t* len) {
  return RFM95_OK;
}

int16_t RFM95_lastRssi() {
  return 123;
}
