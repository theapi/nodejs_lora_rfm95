
#include <rfm95spi.h>
#include <stdint.h>


#ifdef RFM95_RPI //RPI
  #include <rfm95spi_bcm2835.h>
  //printf("It's a Pi!\n");
#else
  #include <rfm95spi_dummy.h>
  //printf("Not a Pi\n");
#endif
