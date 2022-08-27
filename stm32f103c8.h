
// stm32f103c8.h

#pragma once

#include <stdint.h>

#include "common_macro.h"

// base address of RCC(Reset and clock control)
#define REG_RCC ((uint32_t) 0x40021000)
// APB2 peripheral reset register
#define REG_RCC_APB2RSTR (REG_RCC + 0x0c)
// APB2 peripheral clock enable register
#define REG_RCC_APB2ENR (REG_RCC + 0x18)

// base address of GPIO Port A
#define REG_GPIOA ((uint32_t) 0x40010800)
// GPIOA_CRL(Port A configuration register low)
#define REG_GPIOA_CRL (REG_GPIOA + 0x00)
// GPIOA_CRH(Port A configuration register high)
#define REG_GPIOA_CRH (REG_GPIOA + 0x04)

// base address of GPIO Port C
#define REG_GPIOC ((uint32_t) 0x40011000)
// GPIOC_CRL(Port C configuration register low)
#define REG_GPIOC_CRL (REG_GPIOC + 0x00)
// GPIOC_CRH(Port C configuration register high)
#define REG_GPIOC_CRH (REG_GPIOC + 0x04)
// GPIOC_ODR(Port C output data register)
#define REG_GPIOC_ODR (REG_GPIOC + 0x0c)

// base address of USART1
#define REG_USART1 ((uint32_t) 0x40013800)
// USART1 status register
#define REG_USART1_SR (REG_USART1 + 0x00)
// USART1 data register
#define REG_USART1_DR (REG_USART1 + 0x04)
// USART1 baud rate register
#define REG_USART1_BRR (REG_USART1 + 0x08)
// USART1 control register
#define REG_USART1_CR1 (REG_USART1 + 0x0c)


// Coretex-M3
// SCS:System Control Space
#define REG_SCS ((uint32_t)0xe000e000)

// Coretex-M3
// SYST:System timer
#define REG_SYST (REG_SCS + 0x10)
// SysTick Control and Status Register
#define REG_SYST_CSR (REG_SYST + 0x00)
// SysTick Reload Value Register
#define REG_SYST_RVR (REG_SYST + 0x04)
// SysTick Current Value Register
#define REG_SYST_CVR (REG_SYST + 0x08)
// SysTick Calibration Value Register
#define REG_SYST_CALIB (REG_SYST + 0x0c)

// Coretex-M3
// NVIC:Nested Vectord Interrupt Contoller
#define REG_NVIC (REG_SCS + 0x0100)
#define REG_NVIC_ISER_0 (REG_NVIC + (0 * 4))
#define REG_NVIC_ISER_1 (REG_NVIC + (0 * 4) + 4)
#define REG_NVIC_ICER_0 (REG_NVIC + (32 * 4))
#define REG_NVIC_ICER_1 (REG_NVIC + (32 * 4) + 4)
#define REG_NVIC_ISPR_0 (REG_NVIC + (64 * 4))
#define REG_NVIC_ISPR_1 (REG_NVIC + (64 * 4) + 4)
#define REG_NVIC_ICPR_0 (REG_NVIC + (96 * 4))
#define REG_NVIC_ICPR_1 (REG_NVIC + (96 * 4) + 4)
#define REG_NVIC_IABR_0 (REG_NVIC + (128 * 4))
#define REG_NVIC_IABR_1 (REG_NVIC + (128 * 4) + 4)
#define REG_NVIC_IPR_0 (REG_NVIC + (192 * 4))
#define REG_NVIC_IPR_1 (REG_NVIC + (192 * 4) + 4 * 1)
#define REG_NVIC_IPR_2 (REG_NVIC + (192 * 4) + 4 * 2)
#define REG_NVIC_IPR_3 (REG_NVIC + (192 * 4) + 4 * 3)
#define REG_NVIC_IPR_4 (REG_NVIC + (192 * 4) + 4 * 4)
#define REG_NVIC_IPR_5 (REG_NVIC + (192 * 4) + 4 * 5)
#define REG_NVIC_IPR_6 (REG_NVIC + (192 * 4) + 4 * 6)
#define REG_NVIC_IPR_7 (REG_NVIC + (192 * 4) + 4 * 7)
#define REG_NVIC_IPR_8 (REG_NVIC + (192 * 4) + 4 * 8)
#define REG_NVIC_IPR_9 (REG_NVIC + (192 * 4) + 4 * 9)
#define REG_NVIC_IPR_10 (REG_NVIC + (192 * 4) + 4 * 10)
#define REG_NVIC_IPR_11 (REG_NVIC + (192 * 4) + 4 * 11)
#define REG_NVIC_IPR_12 (REG_NVIC + (192 * 4) + 4 * 12)
#define REG_NVIC_IPR_13 (REG_NVIC + (192 * 4) + 4 * 13)
#define REG_NVIC_IPR_14 (REG_NVIC + (192 * 4) + 4 * 14)

// Coretex-M3
// SCB:System Control Block
#define REG_SCB (REG_SCS + 0x0d00)
#define REG_SCB_CPUID (REG_SCB + 0x00)
#define REG_SCB_ICSR (REG_SCB + 0x04)
#define REG_SCB_VTOR (REG_SCB + 0x08)
#define REG_SCB_AIRCR (REG_SCB + 0x0c)
#define REG_SCB_SCR (REG_SCB + 0x10)
#define REG_SCB_CCR (REG_SCB + 0x14)
#define REG_SCB_SHPR_0 (REG_SCB + 0x18)
#define REG_SCB_SHPR_1 (REG_SCB + 0x1c)
#define REG_SCB_SHPR_2 (REG_SCB + 0x20)
#define REG_SCB_SHCSR (REG_SCB + 0x24)
#define REG_SCB_CFSR (REG_SCB + 0x28)
#define REG_SCB_HFSR (REG_SCB + 0x2c)
#define REG_SCB_DFSR (REG_SCB + 0x30)
#define REG_SCB_MMFAR (REG_SCB + 0x34)
#define REG_SCB_BFAR (REG_SCB + 0x38)
#define REG_SCB_AFSR (REG_SCB + 0x3c)


extern void (*SysTick_Handler_callback)();

