#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32_F401RE.h"
#include "rcc_driver.h"

#define PRESCALER_84MHZ_10KHZ  (8399U)
#define PRESCALER_16MHZ_10KHZ  (1599U)

void Enable_Timer(TIM_TypeDef *TIM_x);
void Disable_Timer(TIM_TypeDef *TIM_x);
void Set_Timer_Prescaler(TIM_TypeDef *TIM_x, uint16_t prescaler);
void Set_Timer_AutoReload(TIM_TypeDef *TIM_x, uint32_t autoreload);
void Update_Timer_Event_Generation(TIM_TypeDef *TIM_x);
void Set_Timer_Counter(TIM_TypeDef *TIM_x, uint32_t value);
uint32_t Read_Timer_Counter(TIM_TypeDef *TIM_x);
bool Timer_UpdateFlag(TIM_TypeDef *TIM_x);
void Clear_Timer_UpdateFlag(TIM_TypeDef *TIM_x);
void Reset_Timer(TIM_TypeDef *TIM_x);
void Enable_Timer_AutoReloadPreload(TIM_TypeDef *TIM_x);
void Disable_Timer_AutoReloadPreload(TIM_TypeDef *TIM_x);

#endif /* TIMER_DRIVER_H */
