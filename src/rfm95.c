

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

  /* Start in sleep mode */
  RFM95_writeRegister(RFM95_REG_OP_MODE, RFM95_MODE_SLEEP);

  /* Wait a bit for sleep mode to be activated */
  usleep(10000);

  /* Now LoRa mode can be set */
  RFM95_writeRegister(RFM95_REG_OP_MODE, RFM95_LONG_RANGE_MODE);

  /* Check the register was set. */
  uint8_t val = RFM95_readRegister(RFM95_REG_OP_MODE);
  if (val != RFM95_LONG_RANGE_MODE) {
    /* Failed to set the register, can't continue. */
    return RFM95_ERROR;
  }

  /**
   * Set up FIFO
   * Configure the 256 byte FIFO for either receive or transmit,
   * but not both at the same time.
   */
  RFM95_writeRegister(RFM95_REG_FIFO_TX_BASE_ADDR, 0);
  RFM95_writeRegister(RFM95_REG_FIFO_RX_BASE_ADDR, 0);

  //@todo: move the next commands to their own functions.

  /* Set frequency */
  // {0x06D9, 0x0700, 0x0800}, //868MHz from HopeRf demo code
  RFM95_writeRegister(RFM95_REG_FRF_MSB, 0xD9);
  RFM95_writeRegister(RFM95_REG_FRF_MID, 0x00);
  RFM95_writeRegister(RFM95_REG_FRF_LSB, 0x00);

  /* Set config */
//  1d,     1e,      26
//    { 0x72,   0x74,    0x00}, // Bw125Cr45Sf128 (the chip default)
//    { 0x92,   0x74,    0x00}, // Bw500Cr45Sf128
//    { 0x48,   0x94,    0x00}, // Bw31_25Cr48Sf512
//    { 0x78,   0xc4,    0x00}, // Bw125Cr48Sf4096

  // Bw500Cr45Sf128
  RFM95_writeRegister(RFM95_REG_MODEM_CONFIG1, 0x92);
  RFM95_writeRegister(RFM95_REG_MODEM_CONFIG2, 0x74);
  RFM95_writeRegister(RFM95_REG_MODEM_CONFIG3, 0x00);

  /* Set TX power with PA_BOOST */
  // 0x09F6,                   //11dbm  from HopeRf demo code
  RFM95_writeRegister(RFM95_REG_PA_CONFIG, RFM_PA_SELECT | 0xF6);

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
  /* Ensure LoRa mode is also set in RFM95_REG_OP_MODE. */
  RFM95_writeRegister(RFM95_REG_OP_MODE, mode | RFM95_LONG_RANGE_MODE);
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

void RFM95_writeRegister(uint8_t addr, uint8_t val) {
  char tbuf[2];
  char rbuf[2];
  /* Enable the write bit to the address. */
  tbuf[0] = addr | RFM95_WRITE_MASK;
  tbuf[1] = val;

  RFM95spi_transfernb(tbuf, rbuf, 2);
}
