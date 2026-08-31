#include "main.h"

static void System_Init(void)
{
    // 1. Initialize SysTick for accurate millisecond timing (16 MHz HSI)
    SysTick_Init(SYSTEM_CLOCK_FREQ);

    // 2. Initialize USART2 on PA2 (TX) at 115200 Baud 8N1
    USART2_Init(SYSTEM_CLOCK_FREQ, USART_BAUDRATE);
    
    // 3. Send welcome message over UART
    delay_ms(10);
    USART2_SendString("\r\n\r\n");
    USART2_SendString("==================================================\r\n");
    USART2_SendString(" STM32F401RE Pure Bare-Metal Mini Oscilloscope   \r\n");
    USART2_SendString(" ADC Pin: PA0 (ADC1_IN0) | Baud: 115200 8N1      \r\n");
    USART2_SendString("==================================================\r\n\r\n");

    // 4. Configure PA0 as Analog Mode for ADC1 Input Channel 0
    Enable_RCC_GPIO_CLK(GPIOA);
    GPIO_Set_Pin_Mode(GPIOA, PIN_0, GPIO_MODE_ANALOG);
    GPIO_Set_Pull(GPIOA, PIN_0, GPIO_NO_PULL);

    // 5. Configure and Enable ADC1
    Enable_RCC_ADC_CLK(ADC1);
    Configure_clock_ADC();
    Enable_ADC(ADC1);
    Select_Channel_ADC(ADC1, 0); // PA0 is ADC1 Channel 0
    Set_ADC_Sampling_time(ADC1, 0, ADC_SAMPLING_TIME_84_CYCLES);

    // 6. Configure TIM2 as Sample Rate Timebase (e.g. 10 kHz sample rate)
    Enable_RCC_TIMER_CLK(TIM2);
    Set_Timer_Prescaler(TIM2, 0);     // 16 MHz timer clock
    Set_Timer_AutoReload(TIM2, 1599); // 16,000,000 / (1599 + 1) = 10,000 Hz (100 us sample interval)
    Set_Timer_Counter(TIM2, 0);
    Update_Timer_Event_Generation(TIM2);
    Clear_Timer_UpdateFlag(TIM2);
    Enable_Timer(TIM2);
}

static uint16_t Sample_ADC_Channel(void)
{
    Start_Conversion_ADC(ADC1, ADC_SINGLE_CONVERSION);
    ADC_WaitForConversion(ADC1);
    return Read_ADC(ADC1);
}

int main(void)
{
    System_Init();

    ring_struct osc_samples;
    circular_buffer_init(&osc_samples);

    OscState_t state = OSC_STATE_INIT;
    TriggerMode_t trigger_mode = TRIGGER_RISING_EDGE;
    
    uint16_t prev_adc = 0;
    uint16_t curr_adc = 0;
    uint32_t trigger_timeout_start = 0;

    while (1)
    {
        switch (state)
        {
            case OSC_STATE_INIT:
                circular_buffer_init(&osc_samples);
                trigger_timeout_start = get_millis();
                state = OSC_STATE_WAIT_TRIGGER;
                break;

            case OSC_STATE_WAIT_TRIGGER:
                curr_adc = Sample_ADC_Channel();

                // Check Trigger Conditions:
                // 1. Rising edge trigger
                // 2. Auto-trigger after 250ms timeout (so waveform is visible even without transition)
                if (trigger_mode == TRIGGER_RISING_EDGE)
                {
                    if ((prev_adc < TRIGGER_LEVEL_HIGH && curr_adc >= TRIGGER_LEVEL_HIGH) ||
                        ((get_millis() - trigger_timeout_start) > 250))
                    {
                        circular_buffer_init(&osc_samples);
                        write_to_ring(curr_adc, &osc_samples);
                        state = OSC_STATE_SAMPLE;
                    }
                }
                else // FALLING_EDGE
                {
                    if ((prev_adc > TRIGGER_LEVEL_LOW && curr_adc <= TRIGGER_LEVEL_LOW) ||
                        ((get_millis() - trigger_timeout_start) > 250))
                    {
                        circular_buffer_init(&osc_samples);
                        write_to_ring(curr_adc, &osc_samples);
                        state = OSC_STATE_SAMPLE;
                    }
                }

                prev_adc = curr_adc;
                break;

            case OSC_STATE_SAMPLE:
                // Wait for timer tick for consistent timebase sampling
                if (Timer_UpdateFlag(TIM2))
                {
                    Clear_Timer_UpdateFlag(TIM2);
                    
                    curr_adc = Sample_ADC_Channel();
                    write_to_ring(curr_adc, &osc_samples);

                    if (is_buffer_full(&osc_samples))
                    {
                        state = OSC_STATE_SEND_UART;
                    }
                }
                break;

            case OSC_STATE_SEND_UART:
                USART2_SendString("--- FRAME START ---\r\n");
                
                while (is_data_available(&osc_samples))
                {
                    uint16_t val = 0;
                    read_from_ring(&val, &osc_samples);
                    
                    USART2_SendInt(val);
                    USART2_SendString("\r\n");
                }

                USART2_SendString("--- FRAME END ---\r\n");

                // Small hold-off delay between frames
                delay_ms(50);
                state = OSC_STATE_INIT;
                break;

            default:
                state = OSC_STATE_INIT;
                break;
        }
    }
}