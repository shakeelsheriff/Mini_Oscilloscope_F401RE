#include "usart_driver.h"

void Enable_USART(USART_TypeDef *USART_x)
{
    USART_x->CR1 |= USART_CR1_UE;
}

void Disable_USART(USART_TypeDef *USART_x)
{
    USART_x->CR1 &= ~USART_CR1_UE;
}

void Set_USART_Word_Length(USART_TypeDef *USART_x, Data_Word_Length length)
{
    if (length == NINE_BIT_DATAFRAME)
    {
        USART_x->CR1 |= USART_CR1_M;
    }
    else
    {
        USART_x->CR1 &= ~USART_CR1_M;
    }
}

void Set_USART_Stop_Bits(USART_TypeDef *USART_x, Total_Stop_bit stop_bit)
{
    USART_x->CR2 &= ~USART_CR2_STOP;
    USART_x->CR2 |= (((uint32_t)stop_bit & 0x03UL) << USART_CR2_STOP_Pos);
}

void Set_USART_Oversampling(USART_TypeDef *USART_x, USART_OverSampling oversamp)
{
    if (oversamp == USART_OVERSAMPLING_16)
    {
        USART_x->CR1 &= ~USART_CR1_OVER8;
    }
    else
    {
        USART_x->CR1 |= USART_CR1_OVER8;
    }
}

void Set_USART_Baudrate(USART_TypeDef *USART_x, uint32_t pclk, uint32_t baud)
{
    if ((USART_x->CR1 & USART_CR1_OVER8) == 0) // OVER16
    {
        // For OVER16, USARTDIV = pclk / (16 * baud)
        // With 4-bit fraction in BRR, BRR = (pclk + (baud / 2)) / baud
        USART_x->BRR = (pclk + (baud / 2UL)) / baud;
    }
    else // OVER8
    {
        // For OVER8, fraction is 3 bits: [2:0]
        uint32_t mantissa = pclk / (8UL * baud);
        uint32_t fraction = ((pclk % (8UL * baud)) * 8UL + (baud / 2UL)) / baud;
        USART_x->BRR = (mantissa << USART_BRR_DIV_Mantissa_Pos) | (fraction & 0x07UL);
    }
}

void Set_Transmitter_enable(USART_TypeDef *USART_x)
{
    USART_x->CR1 |= USART_CR1_TE;
}

void Set_Receiver_enable(USART_TypeDef *USART_x)
{
    USART_x->CR1 |= USART_CR1_RE;
}

void USART2_Init(uint32_t pclk, uint32_t baud)
{
    // 1. Enable Clocks for GPIOA and USART2
    Enable_RCC_GPIO_CLK(GPIOA);
    Enable_RCC_USART_CLK(USART2);

    // 2. Configure PA2 (TX) as Alternate Function 7 (USART2)
    GPIO_Set_Pin_Mode(GPIOA, PIN_2, GPIO_MODE_AF);
    GPIO_Set_Alt_Function(GPIOA, PIN_2, 7); // AF7 = USART2
    GPIO_Set_Speed(GPIOA, PIN_2, GPIO_SPEED_VERY_HIGH);
    GPIO_Set_Pull(GPIOA, PIN_2, GPIO_PULL_UP);

    // 3. Disable USART before configuring
    Disable_USART(USART2);

    // 4. Set word length: 8-bit, 1 stop bit, oversampling by 16
    Set_USART_Word_Length(USART2, EIGHT_BIT_DATAFRAME);
    Set_USART_Stop_Bits(USART2, STOP_BIT_ONE);
    Set_USART_Oversampling(USART2, USART_OVERSAMPLING_16);

    // 5. Calculate and set baud rate
    Set_USART_Baudrate(USART2, pclk, baud);

    // 6. Enable Transmitter and Enable USART2
    Set_Transmitter_enable(USART2);
    Enable_USART(USART2);
}

void USART_SendChar(USART_TypeDef *USART_x, char c)
{
    while (!(USART_x->SR & USART_SR_TXE));
    USART_x->DR = (uint8_t)c;
}

void USART_SendString(USART_TypeDef *USART_x, const char *str)
{
    if (str == NULL) return;
    while (*str)
    {
        USART_SendChar(USART_x, *str++);
    }
    while (!(USART_x->SR & USART_SR_TC));
}

void USART_SendInt(USART_TypeDef *USART_x, int32_t num)
{
    char buf[12];
    int i = 0;
    
    if (num == 0)
    {
        USART_SendChar(USART_x, '0');
        return;
    }
    
    if (num < 0)
    {
        USART_SendChar(USART_x, '-');
        num = -num;
    }
    
    while (num > 0)
    {
        buf[i++] = (char)('0' + (num % 10));
        num /= 10;
    }
    
    while (i > 0)
    {
        USART_SendChar(USART_x, buf[--i]);
    }
}

void Write_USART_Buffer(USART_TypeDef *USART_x, const char *t_buff)
{
    USART_SendString(USART_x, t_buff);
}

void USART2_SendChar(char c)
{
    USART_SendChar(USART2, c);
}

void USART2_SendString(const char *str)
{
    USART_SendString(USART2, str);
}

void USART2_SendInt(int32_t num)
{
    USART_SendInt(USART2, num);
}
