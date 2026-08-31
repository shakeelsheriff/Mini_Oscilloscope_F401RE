#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <stdint.h>
#include "stm32_F401RE.h"
#include "gpio_driver.h"
#include "rcc_driver.h"

typedef enum
{
    EIGHT_BIT_DATAFRAME = 0,
    NINE_BIT_DATAFRAME
} Data_Word_Length;

typedef enum
{
    STOP_BIT_ONE          = 0,
    STOP_BIT_HALF         = 1,
    STOP_BIT_TWO          = 2,
    STOP_BIT_ONE_AND_HALF = 3
} Total_Stop_bit;

typedef enum
{
    USART_OVERSAMPLING_16 = 0,
    USART_OVERSAMPLING_8  = 1
} USART_OverSampling;

/* High-level USART Initializer */
void USART2_Init(uint32_t pclk, uint32_t baud);

/* Low-level driver functions */
void Enable_USART(USART_TypeDef *USART_x);
void Disable_USART(USART_TypeDef *USART_x);
void Set_USART_Word_Length(USART_TypeDef *USART_x, Data_Word_Length length);
void Set_USART_Stop_Bits(USART_TypeDef *USART_x, Total_Stop_bit stop_bit);
void Set_USART_Oversampling(USART_TypeDef *USART_x, USART_OverSampling oversamp);
void Set_USART_Baudrate(USART_TypeDef *USART_x, uint32_t pclk, uint32_t baud);
void Set_Transmitter_enable(USART_TypeDef *USART_x);
void Set_Receiver_enable(USART_TypeDef *USART_x);

/* Generic transmission functions */
void USART_SendChar(USART_TypeDef *USART_x, char c);
void USART_SendString(USART_TypeDef *USART_x, const char *str);
void USART_SendInt(USART_TypeDef *USART_x, int32_t num);
void Write_USART_Buffer(USART_TypeDef *USART_x, const char *t_buff);

/* Convenience USART2 transmission helpers */
void USART2_SendChar(char c);
void USART2_SendString(const char *str);
void USART2_SendInt(int32_t num);

#endif /* USART_DRIVER_H */
