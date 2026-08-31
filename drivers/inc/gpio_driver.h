#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include "stm32_F401RE.h"

/* GPIO Pin Definitions */
#define PIN_0   (0U)
#define PIN_1   (1U)
#define PIN_2   (2U)
#define PIN_3   (3U)
#define PIN_4   (4U)
#define PIN_5   (5U)
#define PIN_6   (6U)
#define PIN_7   (7U)
#define PIN_8   (8U)
#define PIN_9   (9U)
#define PIN_10  (10U)
#define PIN_11  (11U)
#define PIN_12  (12U)
#define PIN_13  (13U)
#define PIN_14  (14U)
#define PIN_15  (15U)

/* GPIO Pin Modes (MODER) */
typedef enum
{
    GPIO_MODE_INPUT     = 0x00U,
    GPIO_MODE_OUTPUT    = 0x01U,
    GPIO_MODE_AF        = 0x02U,
    GPIO_MODE_ANALOG    = 0x03U,
    
    /* Legacy aliases */
    INPUT_STATE         = 0x00U,
    OUTPUT_STATE        = 0x01U,
    ALT_FN_STATE        = 0x02U,
    ANALOG_STATE        = 0x03U
} GPIO_Mode_t;

typedef GPIO_Mode_t MODER_STATES;

/* GPIO Output Types (OTYPER) */
typedef enum
{
    GPIO_OTYPE_PUSHPULL  = 0x00U,
    GPIO_OTYPE_OPENDRAIN = 0x01U
} GPIO_OType_t;

/* GPIO Output Speed (OSPEEDR) */
typedef enum
{
    GPIO_SPEED_LOW       = 0x00U,
    GPIO_SPEED_MEDIUM    = 0x01U,
    GPIO_SPEED_HIGH      = 0x02U,
    GPIO_SPEED_VERY_HIGH = 0x03U
} GPIO_Speed_t;

/* GPIO Pull-Up / Pull-Down (PUPDR) */
typedef enum
{
    GPIO_NO_PULL   = 0x00U,
    GPIO_PULL_UP   = 0x01U,
    GPIO_PULL_DOWN = 0x02U
} GPIO_Pull_t;

/* GPIO Logic Level */
typedef enum
{
    LOW  = 0U,
    HIGH = 1U
} GPIO_STATE;

/* Modern Driver API */
void GPIO_Set_Pin_Mode(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Mode_t mode);
void GPIO_Set_Alt_Function(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t af_num);
void GPIO_Set_Speed(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Speed_t speed);
void GPIO_Set_Pull(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_Pull_t pull);
void GPIO_Set_OutputType(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_OType_t otype);

void GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint8_t pin, GPIO_STATE state);
uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint8_t pin);
void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint8_t pin);

/* Backward compatibility aliases */
void configure_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number, MODER_STATES mode);
void Write_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number, GPIO_STATE state);
uint8_t Read_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number);
void Toggle_GPIO(GPIO_TypeDef *GPIO_PORT, uint8_t pin_number);

#endif /* GPIO_DRIVER_H */
