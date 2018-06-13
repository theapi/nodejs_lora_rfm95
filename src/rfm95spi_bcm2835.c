
#include <rfm95spi_bcm2835.h>
#include <rfm95spi.h>
#include <stdio.h>

#define RFM95_RPI 1
#ifdef RFM95_RPI //RPI

#include <bcm2835.h>

RFM95_status_t RFM95spi_init() {
  if (!bcm2835_init()) {
    return RFM95_ERROR;
  }

  if (!bcm2835_spi_begin()) {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
    return RFM95_ERROR;
  }
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

  return RFM95_OK;
}

void RFM95spi_transfernb(char* tbuf, char* rbuf, uint32_t len) {
  bcm2835_spi_transfernb(tbuf, rbuf, len);
}

#endif
