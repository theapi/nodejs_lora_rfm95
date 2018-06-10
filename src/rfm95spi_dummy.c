
#include <rfm95spi_dummy.h>
#include <rfm95spi.h>

#ifndef RFM95_RPI

RFM95_status_t RFM95spi_init() {
  return RFM95_OK;
}

#endif
