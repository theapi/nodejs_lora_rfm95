
#include <rfm95spi_dummy.h>
#include <rfm95spi.h>

#ifndef RFM95_RPI

#include <unistd.h>

RFM95_status_t RFM95spi_init() {
  /* 100 ms startup */
  usleep(100000); 
  return RFM95_OK;
}

#endif
