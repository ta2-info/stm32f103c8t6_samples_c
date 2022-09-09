
// stm32f103c8.h

#pragma once

#include <stdint.h>

#include "common_macro.h"

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
// USART1 control register 1
#define REG_USART1_CR1 (REG_USART1 + 0x0c)
// USART1 control register 2
#define REG_USART1_CR2 (REG_USART1 + 0x10)
// USART1 control register 3
#define REG_USART1_CR3 (REG_USART1 + 0x14)

// base address of DMA1
#define REG_DMA1 ((uint32_t) 0x40020000)
// DMA1 interrupt status register
#define REG_DMA1_ISR (REG_DMA1 + 0x00)
// DMA1 interrupt flag clear register
#define REG_DMA1_IFCR (REG_DMA1 + 0x04)
// DMA1 channel 1 configuration register
#define REG_DMA1_CCR1 (REG_DMA1 + 0x08)
// DMA1 channel 1 number of data register
#define REG_DMA1_CNDTR1 (REG_DMA1 + 0x0c)
// DMA1 channel 1 peripheral address register
#define REG_DMA1_CPAR1 (REG_DMA1 + 0x10)
// DMA1 channel 1 memory address register
#define REG_DMA1_CMAR1 (REG_DMA1 + 0x14)
// DMA1 channel 2 configuration register
#define REG_DMA1_CCR2 (REG_DMA1 + 0x1c)
// DMA1 channel 2 number of data register
#define REG_DMA1_CNDTR2 (REG_DMA1 + 0x20)
// DMA1 channel 2 peripheral address register
#define REG_DMA1_CPAR2 (REG_DMA1 + 0x24)
// DMA1 channel 2 memory address register
#define REG_DMA1_CMAR2 (REG_DMA1 + 0x28)
// DMA1 channel 3 configuration register
#define REG_DMA1_CCR3 (REG_DMA1 + 0x30)
// DMA1 channel 3 number of data register
#define REG_DMA1_CNDTR3 (REG_DMA1 + 0x34)
// DMA1 channel 3 peripheral address register
#define REG_DMA1_CPAR3 (REG_DMA1 + 0x38)
// DMA1 channel 3 memory address register
#define REG_DMA1_CMAR3 (REG_DMA1 + 0x3c)
// DMA1 channel 4 configuration register
#define REG_DMA1_CCR4 (REG_DMA1 + 0x44)
// DMA1 channel 4 number of data register
#define REG_DMA1_CNDTR4 (REG_DMA1 + 0x48)
// DMA1 channel 4 peripheral address register
#define REG_DMA1_CPAR4 (REG_DMA1 + 0x4c)
// DMA1 channel 4 memory address register
#define REG_DMA1_CMAR4 (REG_DMA1 + 0x50)
// DMA1 channel 5 configuration register
#define REG_DMA1_CCR5 (REG_DMA1 + 0x58)
// DMA1 channel 5 number of data register
#define REG_DMA1_CNDTR5 (REG_DMA1 + 0x5c)
// DMA1 channel 5 peripheral address register
#define REG_DMA1_CPAR5 (REG_DMA1 + 0x60)
// DMA1 channel 5 memory address register
#define REG_DMA1_CMAR5 (REG_DMA1 + 0x64)
// DMA1 channel 6 configuration register
#define REG_DMA1_CCR6 (REG_DMA1 + 0x6c)
// DMA1 channel 6 number of data register
#define REG_DMA1_CNDTR6 (REG_DMA1 + 0x70)
// DMA1 channel 6 peripheral address register
#define REG_DMA1_CPAR6 (REG_DMA1 + 0x74)
// DMA1 channel 6 memory address register
#define REG_DMA1_CMAR6 (REG_DMA1 + 0x78)
// DMA1 channel 7 configuration register
#define REG_DMA1_CCR7 (REG_DMA1 + 0x80)
// DMA1 channel 7 number of data register
#define REG_DMA1_CNDTR7 (REG_DMA1 + 0x84)
// DMA1 channel 7 peripheral address register
#define REG_DMA1_CPAR7 (REG_DMA1 + 0x88)
// DMA1 channel 7 memory address register
#define REG_DMA1_CMAR7 (REG_DMA1 + 0x8c)


// base address of RCC(Reset and clock control)
#define REG_RCC ((uint32_t) 0x40021000)
// Clock control register
#define REG_RCC_CR (REG_RCC + 0x00)
// Clock configuration register
#define REG_RCC_CFGR (REG_RCC + 0x04)
// Clock interrupt register
#define REG_RCC_CIR (REG_RCC + 0x08)
// APB2 peripheral reset register
#define REG_RCC_APB2RSTR (REG_RCC + 0x0c)
// APB1 peripheral reset register
#define REG_RCC_APB1RSTR (REG_RCC + 0x10)
// AHB peripheral clock enable register
#define REG_RCC_AHBENR (REG_RCC + 0x14)
// APB2 peripheral clock enable register
#define REG_RCC_APB2ENR (REG_RCC + 0x18)
// APB1 peripheral clock enable register
#define REG_RCC_APB1ENR (REG_RCC + 0x1c)


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



