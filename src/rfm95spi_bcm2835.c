
#include <rfm95spi_bcm2835.h>
#include <rfm95spi.h>


#ifdef RFM95_RPI //RPI

#include <bcm2835.h>

RFM95_status_t RFM95spi_init() {
  if (!bcm2835_init()) {
    return RFM95_ERROR;
  }

  return RFM95_OK;
}

#endif
