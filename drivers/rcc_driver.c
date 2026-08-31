#include "rcc_driver.h"

void Enable_RCC_GPIO_CLK(GPIO_TypeDef *GPIO_x)
{
    if (GPIO_x == GPIOA)      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (GPIO_x == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (GPIO_x == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (GPIO_x == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if (GPIO_x == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if (GPIO_x == GPIOH) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    
    volatile uint32_t dummy = RCC->AHB1ENR;
    (void)dummy;
}

void Disable_RCC_GPIO_CLK(GPIO_TypeDef *GPIO_x)
{
    if (GPIO_x == GPIOA)      RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
    else if (GPIO_x == GPIOB) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
    else if (GPIO_x == GPIOC) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
    else if (GPIO_x == GPIOD) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
    else if (GPIO_x == GPIOE) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
    else if (GPIO_x == GPIOH) RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
}

void Enable_RCC_ADC_CLK(ADC_TypeDef *ADC_x)
{
    if (ADC_x == ADC1) {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    }
    volatile uint32_t dummy = RCC->APB2ENR;
    (void)dummy;
}

void Disable_RCC_ADC_CLK(ADC_TypeDef *ADC_x)
{
    if (ADC_x == ADC1) {
        RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
    }
}

void Enable_RCC_USART_CLK(USART_TypeDef *USART_x)
{
    if (USART_x == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    } else if (USART_x == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    } else if (USART_x == USART6) {
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    }
    volatile uint32_t dummy = RCC->APB1ENR;
    (void)dummy;
}

void Disable_RCC_USART_CLK(USART_TypeDef *USART_x)
{
    if (USART_x == USART1) {
        RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
    } else if (USART_x == USART2) {
        RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
    } else if (USART_x == USART6) {
        RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN;
    }
}

void Enable_RCC_TIMER_CLK(TIM_TypeDef *TIM_x)
{
    if (TIM_x == TIM1)        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if (TIM_x == TIM2)   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIM_x == TIM3)   RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if (TIM_x == TIM4)   RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    else if (TIM_x == TIM5)   RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    else if (TIM_x == TIM9)   RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    else if (TIM_x == TIM10)  RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    else if (TIM_x == TIM11)  RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    
    volatile uint32_t dummy = RCC->APB1ENR;
    (void)dummy;
}

void Disable_RCC_TIMER_CLK(TIM_TypeDef *TIM_x)
{
    if (TIM_x == TIM1)        RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
    else if (TIM_x == TIM2)   RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
    else if (TIM_x == TIM3)   RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
    else if (TIM_x == TIM4)   RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
    else if (TIM_x == TIM5)   RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
    else if (TIM_x == TIM9)   RCC->APB2ENR &= ~RCC_APB2ENR_TIM9EN;
    else if (TIM_x == TIM10)  RCC->APB2ENR &= ~RCC_APB2ENR_TIM10EN;
    else if (TIM_x == TIM11)  RCC->APB2ENR &= ~RCC_APB2ENR_TIM11EN;
}
