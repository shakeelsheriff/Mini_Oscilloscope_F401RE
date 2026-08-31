#include "timer_driver.h"

void Enable_Timer(TIM_TypeDef *TIM_x){
	//Enable counter(CEN)
	TIM_x->CR1 |= TIM_CR1_CEN;
}

void Disable_Timer(TIM_TypeDef *TIM_x){
	//Disable counter(CEN)
	TIM_x->CR1 &= ~TIM_CR1_CEN;
}

void Set_Timer_Prescaler(TIM_TypeDef *TIM_x, uint16_t prescaler){
	TIM_x->PSC = prescaler;
}

void Set_Timer_AutoReload(TIM_TypeDef *TIM_x, uint32_t autoreload)
{
    TIM_x->ARR = autoreload;
}

void Update_Timer_Event_Generation(TIM_TypeDef *TIM_x){
	TIM_x->EGR |= TIM_EGR_UG;
}

void Set_Timer_Counter(TIM_TypeDef *TIM_x, uint32_t value)
{
    TIM_x->CNT = value;
}

uint32_t Read_Timer_Counter(TIM_TypeDef *TIM_x)
{
    return TIM_x->CNT;
}

bool Timer_UpdateFlag(TIM_TypeDef *TIM_x)
{
    return ((TIM_x->SR & TIM_SR_UIF) != 0U);
}

void Clear_Timer_UpdateFlag(TIM_TypeDef *TIM_x)
{
    TIM_x->SR &= ~TIM_SR_UIF;
}

void Reset_Timer(TIM_TypeDef *TIM_x)
{
    TIM_x->CNT = 0;
}

void Enable_Timer_AutoReloadPreload(TIM_TypeDef *TIM_x)
{
    TIM_x->CR1 |= TIM_CR1_ARPE;
}

void Disable_Timer_AutoReloadPreload(TIM_TypeDef *TIM_x)
{
    TIM_x->CR1 &= ~TIM_CR1_ARPE;
}
