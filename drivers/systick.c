#include "systick.h"

static volatile uint32_t g_system_ticks = 0;

void SysTick_Init(uint32_t sysclk_freq)
{
    // Reload value for 1ms tick: (sysclk_freq / 1000) - 1
    SysTick->LOAD = (sysclk_freq / 1000UL) - 1UL;
    SysTick->VAL  = 0UL;
    // CLKSOURCE = Processor clock (bit 2), TICKINT = Enable IRQ (bit 1), ENABLE = Enable counter (bit 0)
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
    g_system_ticks++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start_time = g_system_ticks;
    while ((g_system_ticks - start_time) < ms)
    {
        __asm__ volatile ("nop");
    }
}

uint32_t get_millis(void)
{
    return g_system_ticks;
}
