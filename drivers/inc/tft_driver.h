#ifndef TFT_DRIVER_H
#define TFT_DRIVER_H
#include "main.h"
#include "gpio_driver.h"
#include "parallelcomm_driver.h"
void ili941_init();
void TFT_HW_Reset(void);
void TFT_WriteCommand(uint8_t command);
void TFT_WriteData(uint8_t data);
void No_operation_mode(void);
void TFT_SW_reset(void);

#define PIN_0_RST	0
#define PIN_1_CS	1
#define PIN_2_RS	2
#define PIN_3_WR	3
#define PIN_4_RD	4


#define NOP	0x00
#define SFT_RST	0x01
#endif
