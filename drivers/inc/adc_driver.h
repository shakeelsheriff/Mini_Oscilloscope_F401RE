#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include "stm32_F401RE.h"
#include "rcc_driver.h"

typedef enum
{
    ADC_SINGLE_CONVERSION = 0,
    ADC_CONTINUOUS_CONVERSION
} ADC_Mode_t;

typedef enum
{
    ADC_SAMPLING_TIME_3_CYCLES   = 0,
    ADC_SAMPLING_TIME_15_CYCLES  = 1,
    ADC_SAMPLING_TIME_28_CYCLES  = 2,
    ADC_SAMPLING_TIME_56_CYCLES  = 3,
    ADC_SAMPLING_TIME_84_CYCLES  = 4,
    ADC_SAMPLING_TIME_112_CYCLES = 5,
    ADC_SAMPLING_TIME_144_CYCLES = 6,
    ADC_SAMPLING_TIME_480_CYCLES = 7
} ADC_Sampling_time;

void Enable_ADC(ADC_TypeDef *ADC_x);
void Disable_ADC(ADC_TypeDef *ADC_x);
void Configure_clock_ADC(void);
void Select_Channel_ADC(ADC_TypeDef *ADC_x, uint8_t channel);
void Set_ADC_Sampling_time(ADC_TypeDef *ADC_x, uint8_t channel_SMPx, ADC_Sampling_time sampling_time);
void Start_Conversion_ADC(ADC_TypeDef *ADC_x, ADC_Mode_t mode);
void ADC_WaitForConversion(ADC_TypeDef *ADC_x);
uint16_t Read_ADC(ADC_TypeDef *ADC_x);

#endif /* ADC_DRIVER_H */
