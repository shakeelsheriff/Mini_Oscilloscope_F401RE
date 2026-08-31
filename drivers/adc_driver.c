#include "adc_driver.h"

void Enable_ADC(ADC_TypeDef *ADC_x)
{
    if (ADC_x == ADC1)
    {
        ADC_x->CR2 |= ADC_CR2_ADON;
    }
}

void Disable_ADC(ADC_TypeDef *ADC_x)
{
    if (ADC_x == ADC1)
    {
        ADC_x->CR2 &= ~ADC_CR2_ADON;
    }
}

void Configure_clock_ADC(void)
{
    // ADC prescaler: PCLK2 divided by 4 (ADCPRE in ADC_CCR bits [17:16] = 0b01)
    ADC->CCR &= ~ADC_CCR_ADCPRE_Msk;
    ADC->CCR |=  (1UL << ADC_CCR_ADCPRE_Pos);
}

void Select_Channel_ADC(ADC_TypeDef *ADC_x, uint8_t channel)
{
    if (ADC_x == ADC1)
    {
        // 1 conversion in sequence (L[3:0] in SQR1 = 0)
        ADC_x->SQR1 &= ~(0x0FUL << 20);
        
        // 1st conversion in regular sequence (SQ1[4:0] in SQR3)
        ADC_x->SQR3 &= ~(0x1FUL);
        ADC_x->SQR3 |= (channel & 0x1FUL);
    }
}

void Set_ADC_Sampling_time(ADC_TypeDef *ADC_x, uint8_t channel_SMPx, ADC_Sampling_time sampling_time)
{
    if (channel_SMPx > 18) return;
    
    if (channel_SMPx <= 9)
    {
        ADC_x->SMPR2 &= ~(0x07UL << (channel_SMPx * 3));
        ADC_x->SMPR2 |=  (((uint32_t)sampling_time & 0x07UL) << (channel_SMPx * 3));
    }
    else
    {
        ADC_x->SMPR1 &= ~(0x07UL << ((channel_SMPx - 10) * 3));
        ADC_x->SMPR1 |=  (((uint32_t)sampling_time & 0x07UL) << ((channel_SMPx - 10) * 3));
    }
}

void Start_Conversion_ADC(ADC_TypeDef *ADC_x, ADC_Mode_t mode)
{
    ADC_x->CR2 &= ~ADC_CR2_CONT;
    if (mode == ADC_CONTINUOUS_CONVERSION)
    {
        ADC_x->CR2 |= ADC_CR2_CONT;
    }
    ADC_x->CR2 |= ADC_CR2_SWSTART;
}

void ADC_WaitForConversion(ADC_TypeDef *ADC_x)
{
    while (!(ADC_x->SR & ADC_SR_EOC));
}

uint16_t Read_ADC(ADC_TypeDef *ADC_x)
{
    return (uint16_t)(ADC_x->DR & 0x0FFF);
}
