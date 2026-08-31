#include "gpio_driver.h"

void GPIO_Set_Pin_Mode(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Mode_t mode)
{
    GPIOx->MODER &= ~(0x03UL << (pin * 2));
    GPIOx->MODER |=  (((uint32_t)mode & 0x03UL) << (pin * 2));
}

void GPIO_Set_Alt_Function(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t af_num)
{
    uint8_t reg_index = pin / 8;
    uint8_t bit_shift = (pin % 8) * 4;
    
    GPIOx->AFR[reg_index] &= ~(0x0FUL << bit_shift);
    GPIOx->AFR[reg_index] |=  (((uint32_t)af_num & 0x0FUL) << bit_shift);
}

void GPIO_Set_Speed(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Speed_t speed)
{
    GPIOx->OSPEEDR &= ~(0x03UL << (pin * 2));
    GPIOx->OSPEEDR |=  (((uint32_t)speed & 0x03UL) << (pin * 2));
}

void GPIO_Set_Pull(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Pull_t pull)
{
    GPIOx->PUPDR &= ~(0x03UL << (pin * 2));
    GPIOx->PUPDR |=  (((uint32_t)pull & 0x03UL) << (pin * 2));
}

void GPIO_Set_OutputType(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_OType_t otype)
{
    if (otype == GPIO_OTYPE_OPENDRAIN)
    {
        GPIOx->OTYPER |=  (1UL << pin);
    }
    else
    {
        GPIOx->OTYPER &= ~(1UL << pin);
    }
}

void GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_STATE state)
{
    if (state == HIGH)
    {
        GPIOx->BSRR = (1UL << pin);
    }
    else
    {
        GPIOx->BSRR = (1UL << (pin + 16));
    }
}

uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    return ((GPIOx->IDR & (1UL << pin)) != 0) ? 1 : 0;
}

void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    GPIOx->ODR ^= (1UL << pin);
}

/* Backward compatibility */
void configure_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number, MODER_STATES mode)
{
    GPIO_Set_Pin_Mode(GPIO_PORT, pin_number, mode);
    if (mode == INPUT_STATE)
    {
        GPIO_Set_Pull(GPIO_PORT, pin_number, GPIO_PULL_UP);
    }
}

void Write_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number, GPIO_STATE state)
{
    GPIO_Write_Pin(GPIO_PORT, pin_number, state);
}

uint8_t Read_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number)
{
    return GPIO_Read_Pin(GPIO_PORT, pin_number);
}

void Toggle_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number)
{
    GPIO_Toggle_Pin(GPIO_PORT, pin_number);
}
