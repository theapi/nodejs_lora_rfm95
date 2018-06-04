
#ifndef __rfm95_H
#define __rfm95_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

/* Max number of octets the LORA Rx/Tx FIFO can hold */
#define RF95_FIFO_SIZE 255

/* This is the maximum number of bytes that can be carried by the LORA. */
#define RF95_MAX_PAYLOAD_LEN RF95_FIFO_SIZE

// A wnr bit, which is 1 for write access and 0 for read access.
// binary = 10000000
#define RFM95_WRITE_MASK 0x80

#define RFM95_BROADCAST_ADDRESS 0xff

// The length of the headers we add.
// The headers are inside the LORA's payload
#define RFM95_HEADER_LEN 4

// Register names (LoRa Mode, from table 41 of sx_1276 datasheet)
#define RFM95_REG_FIFO                                0x00
#define RFM95_REG_OP_MODE                             0x01
#define RFM95_REG_FRF_MSB                             0x06
#define RFM95_REG_FRF_MID                             0x07
#define RFM95_REG_FRF_LSB                             0x08
#define RFM95_REG_PA_CONFIG                           0x09
#define RFM95_REG_PA_RAMP                             0x0a
#define RFM95_REG_OCP                                 0x0b
#define RFM95_REG_LNA                                 0x0c
#define RFM95_REG_FIFO_ADDR_PTR                       0x0d
#define RFM95_REG_FIFO_TX_BASE_ADDR                   0x0e
#define RFM95_REG_FIFO_RX_BASE_ADDR                   0x0f
#define RFM95_REG_FIFO_RX_CURRENT_ADDR                0x10
#define RFM95_REG_IRQ_FLAGS_MASK                      0x11
#define RFM95_REG_IRQ_FLAGS                           0x12
#define RFM95_REG_RX_NB_BYTES                         0x13
#define RFM95_REG_RX_HEADER_CNT_VALUE_MSB             0x14
#define RFM95_REG_RX_HEADER_CNT_VALUE_LSB             0x15
#define RFM95_REG_RX_PACKET_CNT_VALUE_MSB             0x16
#define RFM95_REG_RX_PACKET_CNT_VALUE_LSB             0x17
#define RFM95_REG_MODEM_STAT                          0x18
#define RFM95_REG_PKT_SNR_VALUE                       0x19
#define RFM95_REG_PKT_RSSI_VALUE                      0x1a
#define RFM95_REG_RSSI_VALUE                          0x1b
#define RFM95_REG_HOP_CHANNEL                         0x1c
#define RFM95_REG_MODEM_CONFIG1                       0x1d
#define RFM95_REG_MODEM_CONFIG2                       0x1e
#define RFM95_REG_SYMB_TIMEOUT_LSB                    0x1f
#define RFM95_REG_PREAMBLE_MSB                        0x20
#define RFM95_REG_PREAMBLE_LSB                        0x21
#define RFM95_REG_PAYLOAD_LENGTH                      0x22
#define RFM95_REG_MAX_PAYLOAD_LENGTH                  0x23
#define RFM95_REG_HOP_PERIOD                          0x24
#define RFM95_REG_FIFO_RX_BYTE_ADDR                   0x25
#define RFM95_REG_MODEM_CONFIG3                       0x26
#define RFM95_REG_FEI_MSB                             0x28
#define RFM95_REG_FEI_MID                             0x29
#define RFM95_REG_FEI_LSB                             0x2a
#define RFM95_REG_RSSI_WIDEBAND                       0x2c
#define RFM95_REG_DETECT_OPTIMIZ                      0x31
#define RFM95_REG_INVERT_IQ                           0x33
#define RFM95_REG_DETECTION_THRESHOLD                 0x37
#define RFM95_REG_SYNC_WORD                           0x39
#define RFM95_REG_DIO_MAPPING1                        0x40
#define RFM95_REG_DIO_MAPPING2                        0x41
#define RFM95_REG_VERSION                             0x42
#define RFM95_REG_TCXO                                0x4b
#define RFM95_REG_PA_DAC                              0x4d
#define RFM95_REG_FORMER_TEMP                         0x5b
#define RFM95_REG_AGC_REF                             0x61
#define RFM95_REG_AGC_THRESH1                         0x62
#define RFM95_REG_AGC_THRESH2                         0x63
#define RFM95_REG_AGC_THRESH3                         0x64
#define RFM95_REG_PLL                                 0x70

// RFM95_REG_OP_MODE                             0x01
#define RFM95_LONG_RANGE_MODE                       0x80
#define RFM95_ACCESS_SHARED_REG                     0x40
#define RFM95_LOW_FREQUENCY_MODE                    0x08
#define RFM95_MODE                                  0x07
#define RFM95_MODE_SLEEP                            0x00
#define RFM95_MODE_STDBY                            0x01
#define RFM95_MODE_FSTX                             0x02
#define RFM95_MODE_TX                               0x03
#define RFM95_MODE_FSRX                             0x04
#define RFM95_MODE_RXCONTINUOUS                     0x05
#define RFM95_MODE_RXSINGLE                         0x06
#define RFM95_MODE_CAD                              0x07

// RFM_REG_PA_CONFIG                           0x09
#define RFM_PA_SELECT                             0x80
#define RFM_MAX_POWER                             0x70
#define RFM_OUTPUT_POWER                          0x0f

// RFM95_REG_MODEM_STAT                          0x18
#define RFM95_RX_CODING_RATE                        0xe0
#define RFM95_MODEM_STATUS_CLEAR                    0x10
#define RFM95_MODEM_STATUS_HEADER_INFO_VALID        0x08
#define RFM95_MODEM_STATUS_RX_ONGOING               0x04
#define RFM95_MODEM_STATUS_SIGNAL_SYNCHRONIZED      0x02
#define RFM95_MODEM_STATUS_SIGNAL_DETECTED          0x01

// RFM95_REG_MODEM_CONFIG1                       0x1d
#define RFM95_BW_7_8KHZ                             0x00
#define RFM95_BW_10_4KHZ                            0x10
#define RFM95_BW_15_6KHZ                            0x20
#define RFM95_BW_20_8KHZ                            0x30
#define RFM95_BW_31_25KHZ                           0x40
#define RFM95_BW_41_7KHZ                            0x50
#define RFM95_BW_62_5KHZ                            0x60
#define RFM95_BW_125KHZ                             0x70
#define RFM95_BW_250KHZ                             0x80
#define RFM95_BW_500KHZ                             0x90
#define RFM95_CODING_RATE_4_5                       0x02
#define RFM95_CODING_RATE_4_6                       0x04
#define RFM95_CODING_RATE_4_7                       0x06
#define RFM95_CODING_RATE_4_8                       0x08
#define RFM95_IMPLICIT_HEADER_MODE_ON               0x01

// RFM95_REG_MODEM_CONFIG2                       0x1e
#define RFM95_SPREADING_FACTOR_64CPS                0x60
#define RFM95_SPREADING_FACTOR_128CPS               0x70
#define RFM95_SPREADING_FACTOR_256CPS               0x80
#define RFM95_SPREADING_FACTOR_512CPS               0x90
#define RFM95_SPREADING_FACTOR_1024CPS              0xa0
#define RFM95_SPREADING_FACTOR_2048CPS              0xb0
#define RFM95_SPREADING_FACTOR_4096CPS              0xc0
#define RFM95_TX_CONTINUOUS_MODE                    0x08
#define RFM95_PAYLOAD_CRC_ON                        0x04
#define RFM95_SYM_TIMEOUT_MSB                       0x03


typedef struct
{
    uint8_t bufLen; /* Number of octets in the recieved buffer */
    uint8_t buf[RF95_MAX_PAYLOAD_LEN];
    int8_t snf;     /* Last SNR */
} RFM95_TypeDef;

/**
 * Status structures definition
 */
typedef enum
{
  RFM95_OK       = 0x00U,
  RFM95_ERROR    = 0x01U,
  RFM95_BUSY     = 0x02U,
  RFM95_TIMEOUT  = 0x03U
} RFM95_status_t;

/**
 * Initialise the module.
 */
void RFM95_init();

RFM95_status_t RFM95_writeRegister(uint8_t addr, uint8_t val);
uint8_t RFM95_readRegister(uint8_t addr);
RFM95_status_t RFM95_writeRegisterBurst(uint8_t addr, uint8_t *data, uint8_t len);

RFM95_status_t RFM95_setMode(uint8_t mode);
RFM95_status_t RFM95_send(uint8_t* data, uint8_t len);

#ifdef __cplusplus
}
#endif
#endif /*__rfm95_H */
