#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "stm32_F401RE.h"
#include "rcc_driver.h"
#include "gpio_driver.h"
#include "usart_driver.h"
#include "adc_driver.h"
#include "timer_driver.h"
#include "systick.h"
#include "circular_buffer.h"

/* Clock configuration: STM32 default reset clock is HSI = 16 MHz */
#define SYSTEM_CLOCK_FREQ    (16000000UL)
#define USART_BAUDRATE       (115200UL)

/* Trigger thresholds (12-bit ADC: 0..4095, Mid-rail is ~2048) */
#define TRIGGER_LEVEL_HIGH   (2200U)
#define TRIGGER_LEVEL_LOW    (1800U)

typedef enum {
    TRIGGER_RISING_EDGE = 0,
    TRIGGER_FALLING_EDGE
} TriggerMode_t;

typedef enum {
    OSC_STATE_INIT = 0,
    OSC_STATE_WAIT_TRIGGER,
    OSC_STATE_SAMPLE,
    OSC_STATE_SEND_UART
} OscState_t;

#endif /* MAIN_H */
