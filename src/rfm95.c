

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

uint8_t RFM95_readRegister(uint8_t addr) {
  char cmd[2] = {0, 0};
  char data[2] = {0, 0};

  /* Add the read command to the address. */
  cmd[0] = addr & ~RFM95_WRITE_MASK;

  /* Transmit 1 byte and receive 1. Actually receive 2, but the first doesn't matter. */
  RFM95spi_transfernb(cmd, data, 2);

  /* The returned value is the second byte */
  return data[1];
}

RFM95_status_t RFM95_writeRegister(uint8_t addr, uint8_t val) {
  return RFM95_OK;
}