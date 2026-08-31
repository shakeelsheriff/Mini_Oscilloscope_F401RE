#ifndef PARALLELCOMM_DRIVER_H
#define PARALLELCOMM_DRIVER_H

#include "main.h"
#include "gpio_driver.h"

typedef enum{
	COMMAND = 0,
	DATA
}Register_Select;
void parallel_init();
void parallel_write(uint8_t data);
void parallel_reset(uint8_t state);
void parallel_chip_select(uint8_t enable);
void parallel_register_select(Register_Select RS_);
void parallel_write_strobe(void);
void parallel_read_strobe(void);
#endif
