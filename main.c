
#include "common_macro.h"

// base address of RCC(Reset and clock control)
#define REG_RCC ((uint32_t) 0x40021000)
// APB2 peripheral clock enable register
#define REG_RCC_APB2ENR (REG_RCC + 0x18)

// base address of GPIO Port C
#define REG_GPIOC ((uint32_t) 0x40011000)
// GPIOC_CRH(Port C configuration register high)
#define REG_GPIOC_CRH (REG_GPIOC + 0x04)
// GPIOC_ODR(Port C output data register)
#define REG_GPIOC_ODR (REG_GPIOC + 0x0c)

void _start() {
  // Enable clock of GPIOC
  uint8_t tmp8 = GET_REG8(REG_RCC_APB2ENR);
  SET_REG8(REG_RCC_APB2ENR, tmp8 | (1 << 4)); // bit4:GPIOC

  // GPIO PC13 is output
  uint32_t tmp32 = GET_REG32(REG_GPIOC_CRH);
  tmp32 &= ~(0b1111 << (13 - 8) * 4); // Reset only PC13
  tmp32 |= (0b0011 << (13 - 8) * 4); // MODE13=0b11:Output mode, max speed 50MHz, CNF13=0b00:General purpose output push-pull
  SET_REG32(REG_GPIOC_CRH, tmp32);

  while (1) {
    tmp32 = GET_REG32(REG_GPIOC_ODR);
    tmp32 ^= (1 << 13); // Toggle PC13(LED)
    SET_REG32(REG_GPIOC_ODR, tmp32);

    volatile int32_t counter = 100000;
    while (counter > 0) {
      counter--;
    }
  }
}


