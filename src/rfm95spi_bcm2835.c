
#include <rfm95spi_bcm2835.h>
#include <rfm95spi.h>


#ifdef RFM95_RPI //RPI

#include <bcm2835.h>

int RFM95spi_init() {
  return bcm2835_init();
}

#endif
