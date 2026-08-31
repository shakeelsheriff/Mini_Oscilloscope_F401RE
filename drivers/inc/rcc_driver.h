#ifndef RCC_DRIVER_H
#define RCC_DRIVER_H

#include "stm32_F401RE.h"

void Enable_RCC_GPIO_CLK(GPIO_TypeDef *GPIO_x);
void Disable_RCC_GPIO_CLK(GPIO_TypeDef *GPIO_x);

void Enable_RCC_ADC_CLK(ADC_TypeDef *ADC_x);
void Disable_RCC_ADC_CLK(ADC_TypeDef *ADC_x);

void Enable_RCC_USART_CLK(USART_TypeDef *USART_x);
void Disable_RCC_USART_CLK(USART_TypeDef *USART_x);

void Enable_RCC_TIMER_CLK(TIM_TypeDef *TIM_x);
void Disable_RCC_TIMER_CLK(TIM_TypeDef *TIM_x);

#endif /* RCC_DRIVER_H */
