#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "stm32_F401RE.h"

void SysTick_Init(uint32_t sysclk_freq);
void delay_ms(uint32_t ms);
uint32_t get_millis(void);

#endif /* SYSTICK_H */
