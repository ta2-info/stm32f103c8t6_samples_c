
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

