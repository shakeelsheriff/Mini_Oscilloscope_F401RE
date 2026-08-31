#ifndef STM32_F401RE_H
#define STM32_F401RE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ========================================================================== */
/*                         Peripheral Memory Map                              */
/* ========================================================================== */
#define PERIPH_BASE           (0x40000000UL) /* Base address of Peripheral Space */

/* Bus Offsets */
#define APB1PERIPH_BASE       (PERIPH_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000UL)

/* Core System & Cortex-M4 Peripherals */
#define SCS_BASE              (0xE000E000UL)
#define SYSTICK_BASE          (SCS_BASE + 0x0010UL)
#define SCB_BASE              (SCS_BASE + 0x0D00UL)
#define CPACR_REG             (*(volatile uint32_t *)(SCB_BASE + 0x88UL)) /* Coprocessor Access Control Register (FPU) */

typedef volatile uint32_t vuint32_t;

/* ========================================================================== */
/*                              SysTick Timer                                 */
/* ========================================================================== */
typedef struct
{
  vuint32_t CTRL;   /*!< SysTick Control and Status Register, Address offset: 0x00 */
  vuint32_t LOAD;   /*!< SysTick Reload Value Register,       Address offset: 0x04 */
  vuint32_t VAL;    /*!< SysTick Current Value Register,      Address offset: 0x08 */
  vuint32_t CALIB;  /*!< SysTick Calibration Value Register,  Address offset: 0x0C */
} SysTick_TypeDef;

#define SysTick               ((SysTick_TypeDef *) SYSTICK_BASE)

#define SysTick_CTRL_ENABLE_Pos     (0U)
#define SysTick_CTRL_ENABLE_Msk     (1UL << SysTick_CTRL_ENABLE_Pos)
#define SysTick_CTRL_TICKINT_Pos    (1U)
#define SysTick_CTRL_TICKINT_Msk    (1UL << SysTick_CTRL_TICKINT_Pos)
#define SysTick_CTRL_CLKSOURCE_Pos  (2U)
#define SysTick_CTRL_CLKSOURCE_Msk  (1UL << SysTick_CTRL_CLKSOURCE_Pos)
#define SysTick_CTRL_COUNTFLAG_Pos  (16U)
#define SysTick_CTRL_COUNTFLAG_Msk  (1UL << SysTick_CTRL_COUNTFLAG_Pos)

/* ========================================================================== */
/*                    RCC (Reset and Clock Control)                           */
/* ========================================================================== */
typedef struct
{
  vuint32_t CR;            /*!< Clock control register,                                  Address offset: 0x00 */
  vuint32_t PLLCFGR;       /*!< PLL configuration register,                              Address offset: 0x04 */
  vuint32_t CFGR;          /*!< Clock configuration register,                            Address offset: 0x08 */
  vuint32_t CIR;           /*!< Clock interrupt register,                                Address offset: 0x0C */
  vuint32_t AHB1RSTR;      /*!< AHB1 peripheral reset register,                          Address offset: 0x10 */
  vuint32_t AHB2RSTR;      /*!< AHB2 peripheral reset register,                          Address offset: 0x14 */
  vuint32_t AHB3RSTR;      /*!< AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t  RESERVED0;     /*!< Reserved, 0x1C                                                                */
  vuint32_t APB1RSTR;      /*!< APB1 peripheral reset register,                          Address offset: 0x20 */
  vuint32_t APB2RSTR;      /*!< APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t  RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                           */
  vuint32_t AHB1ENR;       /*!< AHB1 peripheral clock register,                          Address offset: 0x30 */
  vuint32_t AHB2ENR;       /*!< AHB2 peripheral clock register,                          Address offset: 0x34 */
  vuint32_t AHB3ENR;       /*!< AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t  RESERVED2;     /*!< Reserved, 0x3C                                                                */
  vuint32_t APB1ENR;       /*!< APB1 peripheral clock enable register,                   Address offset: 0x40 */
  vuint32_t APB2ENR;       /*!< APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t  RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                           */
  vuint32_t AHB1LPENR;     /*!< AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  vuint32_t AHB2LPENR;     /*!< AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  vuint32_t AHB3LPENR;     /*!< AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t  RESERVED4;     /*!< Reserved, 0x5C                                                                */
  vuint32_t APB1LPENR;     /*!< APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  vuint32_t APB2LPENR;     /*!< APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t  RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                           */
  vuint32_t BDCR;          /*!< Backup domain control register,                          Address offset: 0x70 */
  vuint32_t CSR;           /*!< Clock control & status register,                         Address offset: 0x74 */
  uint32_t  RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                           */
  vuint32_t SSCGR;         /*!< Spread spectrum clock generation register,               Address offset: 0x80 */
  vuint32_t PLLI2SCFGR;    /*!< PLLI2S configuration register,                           Address offset: 0x84 */
  uint32_t  RESERVED7[1];  /*!< Reserved, 0x88                                                                */
  vuint32_t DCKCFGR;       /*!< Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_TypeDef;

#define RCC_OFFSET            (0x3800UL)
#define RCC_BASE              (AHB1PERIPH_BASE + RCC_OFFSET)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)

/* Bit definitions for RCC_AHB1ENR */
#define RCC_AHB1ENR_GPIOAEN_Pos (0U)
#define RCC_AHB1ENR_GPIOAEN     (1UL << RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_AHB1ENR_GPIOBEN_Pos (1U)
#define RCC_AHB1ENR_GPIOBEN     (1UL << RCC_AHB1ENR_GPIOBEN_Pos)
#define RCC_AHB1ENR_GPIOCEN_Pos (2U)
#define RCC_AHB1ENR_GPIOCEN     (1UL << RCC_AHB1ENR_GPIOCEN_Pos)
#define RCC_AHB1ENR_GPIODEN_Pos (3U)
#define RCC_AHB1ENR_GPIODEN     (1UL << RCC_AHB1ENR_GPIODEN_Pos)
#define RCC_AHB1ENR_GPIOEEN_Pos (4U)
#define RCC_AHB1ENR_GPIOEEN     (1UL << RCC_AHB1ENR_GPIOEEN_Pos)
#define RCC_AHB1ENR_GPIOHEN_Pos (7U)
#define RCC_AHB1ENR_GPIOHEN     (1UL << RCC_AHB1ENR_GPIOHEN_Pos)

/* Bit definitions for RCC_APB1ENR */
#define RCC_APB1ENR_TIM2EN_Pos  (0U)
#define RCC_APB1ENR_TIM2EN      (1UL << RCC_APB1ENR_TIM2EN_Pos)
#define RCC_APB1ENR_TIM3EN_Pos  (1U)
#define RCC_APB1ENR_TIM3EN      (1UL << RCC_APB1ENR_TIM3EN_Pos)
#define RCC_APB1ENR_TIM4EN_Pos  (2U)
#define RCC_APB1ENR_TIM4EN      (1UL << RCC_APB1ENR_TIM4EN_Pos)
#define RCC_APB1ENR_TIM5EN_Pos  (3U)
#define RCC_APB1ENR_TIM5EN      (1UL << RCC_APB1ENR_TIM5EN_Pos)
#define RCC_APB1ENR_USART2EN_Pos (17U)
#define RCC_APB1ENR_USART2EN    (1UL << RCC_APB1ENR_USART2EN_Pos)

/* Bit definitions for RCC_APB2ENR */
#define RCC_APB2ENR_TIM1EN_Pos  (0U)
#define RCC_APB2ENR_TIM1EN      (1UL << RCC_APB2ENR_TIM1EN_Pos)
#define RCC_APB2ENR_USART1EN_Pos (4U)
#define RCC_APB2ENR_USART1EN    (1UL << RCC_APB2ENR_USART1EN_Pos)
#define RCC_APB2ENR_USART6EN_Pos (5U)
#define RCC_APB2ENR_USART6EN    (1UL << RCC_APB2ENR_USART6EN_Pos)
#define RCC_APB2ENR_ADC1EN_Pos  (8U)
#define RCC_APB2ENR_ADC1EN      (1UL << RCC_APB2ENR_ADC1EN_Pos)
#define RCC_APB2ENR_TIM9EN_Pos  (16U)
#define RCC_APB2ENR_TIM9EN      (1UL << RCC_APB2ENR_TIM9EN_Pos)
#define RCC_APB2ENR_TIM10EN_Pos (17U)
#define RCC_APB2ENR_TIM10EN     (1UL << RCC_APB2ENR_TIM10EN_Pos)
#define RCC_APB2ENR_TIM11EN_Pos (18U)
#define RCC_APB2ENR_TIM11EN     (1UL << RCC_APB2ENR_TIM11EN_Pos)

/* ========================================================================== */
/*                                   GPIO                                     */
/* ========================================================================== */
typedef struct
{
  vuint32_t MODER;    /*!< Mode register,               Address offset: 0x00      */
  vuint32_t OTYPER;   /*!< Output type register,        Address offset: 0x04      */
  vuint32_t OSPEEDR;  /*!< Output speed register,       Address offset: 0x08      */
  vuint32_t PUPDR;    /*!< Pull-up/pull-down register,  Address offset: 0x0C      */
  vuint32_t IDR;      /*!< Input data register,         Address offset: 0x10      */
  vuint32_t ODR;      /*!< Output data register,        Address offset: 0x14      */
  vuint32_t BSRR;     /*!< Bit set/reset register,      Address offset: 0x18      */
  vuint32_t LCKR;     /*!< Configuration lock register, Address offset: 0x1C      */
  vuint32_t AFR[2];   /*!< Alternate function [0:Low, 1:High], Address offset: 0x20-0x24 */
} GPIO_TypeDef;

#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00UL)

#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                 ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                 ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD                 ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE                 ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOH                 ((GPIO_TypeDef *) GPIOH_BASE)

/* ========================================================================== */
/*                                    ADC                                     */
/* ========================================================================== */
typedef struct
{
  vuint32_t SR;     /*!< Status register,                         Address offset: 0x00 */
  vuint32_t CR1;    /*!< Control register 1,                      Address offset: 0x04 */
  vuint32_t CR2;    /*!< Control register 2,                      Address offset: 0x08 */
  vuint32_t SMPR1;  /*!< Sample time register 1,                  Address offset: 0x0C */
  vuint32_t SMPR2;  /*!< Sample time register 2,                  Address offset: 0x10 */
  vuint32_t JOFR1;  /*!< Injected channel data offset register 1, Address offset: 0x14 */
  vuint32_t JOFR2;  /*!< Injected channel data offset register 2, Address offset: 0x18 */
  vuint32_t JOFR3;  /*!< Injected channel data offset register 3, Address offset: 0x1C */
  vuint32_t JOFR4;  /*!< Injected channel data offset register 4, Address offset: 0x20 */
  vuint32_t HTR;    /*!< Watchdog higher threshold register,      Address offset: 0x24 */
  vuint32_t LTR;    /*!< Watchdog lower threshold register,       Address offset: 0x28 */
  vuint32_t SQR1;   /*!< Regular sequence register 1,             Address offset: 0x2C */
  vuint32_t SQR2;   /*!< Regular sequence register 2,             Address offset: 0x30 */
  vuint32_t SQR3;   /*!< Regular sequence register 3,             Address offset: 0x34 */
  vuint32_t JSQR;   /*!< Injected sequence register,              Address offset: 0x38 */
  vuint32_t JDR1;   /*!< Injected data register 1,                Address offset: 0x3C */
  vuint32_t JDR2;   /*!< Injected data register 2,                Address offset: 0x40 */
  vuint32_t JDR3;   /*!< Injected data register 3,                Address offset: 0x44 */
  vuint32_t JDR4;   /*!< Injected data register 4,                Address offset: 0x48 */
  vuint32_t DR;     /*!< Regular data register,                   Address offset: 0x4C */
} ADC_TypeDef;

typedef struct
{
  vuint32_t CSR;    /*!< ADC Common status register,              Address offset: 0x00 */
  vuint32_t CCR;    /*!< ADC Common control register,             Address offset: 0x04 */
  vuint32_t CDR;    /*!< ADC Common regular data register,        Address offset: 0x08 */
} ADC_Common_TypeDef;

#define ADC1_BASE             (APB2PERIPH_BASE + 0x2000UL)
#define ADC_COMMON_BASE       (APB2PERIPH_BASE + 0x2300UL)

#define ADC1                  ((ADC_TypeDef *) ADC1_BASE)
#define ADC                   ((ADC_Common_TypeDef *) ADC_COMMON_BASE)

/* Bit definitions for ADC_SR */
#define ADC_SR_EOC_Pos        (1U)
#define ADC_SR_EOC            (1UL << ADC_SR_EOC_Pos)
#define ADC_SR_STRT_Pos       (4U)
#define ADC_SR_STRT           (1UL << ADC_SR_STRT_Pos)

/* Bit definitions for ADC_CR2 */
#define ADC_CR2_ADON_Pos      (0U)
#define ADC_CR2_ADON          (1UL << ADC_CR2_ADON_Pos)
#define ADC_CR2_CONT_Pos      (1U)
#define ADC_CR2_CONT          (1UL << ADC_CR2_CONT_Pos)
#define ADC_CR2_SWSTART_Pos   (30U)
#define ADC_CR2_SWSTART       (1UL << ADC_CR2_SWSTART_Pos)

/* Bit definitions for ADC_CCR */
#define ADC_CCR_ADCPRE_Pos    (16U)
#define ADC_CCR_ADCPRE_Msk    (3UL << ADC_CCR_ADCPRE_Pos)

/* ========================================================================== */
/*                                   TIMERS                                   */
/* ========================================================================== */
typedef struct
{
  vuint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  vuint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
  vuint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  vuint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  vuint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
  vuint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  vuint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  vuint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  vuint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  vuint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  vuint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  vuint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  vuint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  vuint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  vuint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  vuint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  vuint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  vuint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  vuint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  vuint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  vuint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
} TIM_TypeDef;

#define TIM1_BASE             (APB2PERIPH_BASE + 0x0000UL)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00UL)
#define TIM9_BASE             (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x4800UL)

#define TIM1                  ((TIM_TypeDef *) TIM1_BASE)
#define TIM2                  ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                  ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                  ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                  ((TIM_TypeDef *) TIM5_BASE)
#define TIM9                  ((TIM_TypeDef *) TIM9_BASE)
#define TIM10                 ((TIM_TypeDef *) TIM10_BASE)
#define TIM11                 ((TIM_TypeDef *) TIM11_BASE)

/* Bit definitions for TIM_CR1 */
#define TIM_CR1_CEN_Pos       (0U)
#define TIM_CR1_CEN           (1UL << TIM_CR1_CEN_Pos)
#define TIM_CR1_ARPE_Pos      (7U)
#define TIM_CR1_ARPE          (1UL << TIM_CR1_ARPE_Pos)

/* Bit definitions for TIM_SR */
#define TIM_SR_UIF_Pos        (0U)
#define TIM_SR_UIF            (1UL << TIM_SR_UIF_Pos)

/* Bit definitions for TIM_EGR */
#define TIM_EGR_UG_Pos        (0U)
#define TIM_EGR_UG            (1UL << TIM_EGR_UG_Pos)

/* ========================================================================== */
/*                                   USART                                    */
/* ========================================================================== */
typedef struct
{
  vuint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  vuint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  vuint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  vuint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  vuint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  vuint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  vuint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000UL)
#define USART6_BASE           (APB2PERIPH_BASE + 0x1400UL)

#define USART1                ((USART_TypeDef *) USART1_BASE)
#define USART2                ((USART_TypeDef *) USART2_BASE)
#define USART6                ((USART_TypeDef *) USART6_BASE)

/* Bit definitions for USART_SR */
#define USART_SR_RXNE_Pos     (5U)
#define USART_SR_RXNE         (1UL << USART_SR_RXNE_Pos)
#define USART_SR_TC_Pos       (6U)
#define USART_SR_TC           (1UL << USART_SR_TC_Pos)
#define USART_SR_TXE_Pos      (7U)
#define USART_SR_TXE          (1UL << USART_SR_TXE_Pos)

/* Bit definitions for USART_CR1 */
#define USART_CR1_RE_Pos      (2U)
#define USART_CR1_RE          (1UL << USART_CR1_RE_Pos)
#define USART_CR1_TE_Pos      (3U)
#define USART_CR1_TE          (1UL << USART_CR1_TE_Pos)
#define USART_CR1_M_Pos       (12U)
#define USART_CR1_M           (1UL << USART_CR1_M_Pos)
#define USART_CR1_UE_Pos      (13U)
#define USART_CR1_UE          (1UL << USART_CR1_UE_Pos)
#define USART_CR1_OVER8_Pos   (15U)
#define USART_CR1_OVER8       (1UL << USART_CR1_OVER8_Pos)

/* Bit definitions for USART_CR2 */
#define USART_CR2_STOP_Pos    (12U)
#define USART_CR2_STOP_Msk    (3UL << USART_CR2_STOP_Pos)
#define USART_CR2_STOP        USART_CR2_STOP_Msk

/* Bit definitions for USART_BRR */
#define USART_BRR_DIV_Fraction_Pos (0U)
#define USART_BRR_DIV_Mantissa_Pos (4U)

#endif /* STM32_F401RE_H */