
#include "stm32f103c8.h"

// GPIO A9  USART1:TX
// GPIO A10 USART1:RX

void _start() {
  uint32_t tmp32;

  // Enable clock of USART1
  tmp32 = GET_REG32(REG_RCC_APB2ENR);
  SET_REG32(REG_RCC_APB2ENR, tmp32 | (1 << 14)); // bit14:USART1

  // Reset USART1
  tmp32 = GET_REG32(REG_RCC_APB2RSTR);
  tmp32 |= (1 << 14); // bit14: USART1 RST
  SET_REG32(REG_RCC_APB2RSTR, tmp32);
  tmp32 &= ~(1 << 14);
  SET_REG32(REG_RCC_APB2RSTR, tmp32);

  // CPU = 8MHz
  //
  // Baud rate : 115200
  //  USARTDIV = (8MHz / (16 * 115200)) = 4.3402777777...
  //   Mantissa = 4
  //   Fraction = (0.3402777....) * 16 = 5.4... = 5
  uint16_t wDIV_Mantissa = 4, wDIV_Fraction = 5;
  SET_REG32(REG_USART1_BRR, (wDIV_Mantissa << 4) | (wDIV_Fraction << 0));

  SET_REG32(REG_USART1_CR1, (1 << 13) | (1 << 2)); // bit 13 UE: USART enable, bit2 RE: Receiver enable

  tmp32 = GET_REG32(REG_USART1_SR); // dummy read

  // Enable clock of GPIOA
  tmp32 = GET_REG32(REG_RCC_APB2ENR);
  SET_REG32(REG_RCC_APB2ENR, tmp32 | (1 << 2)); // bit2:GPIOA

  // GPIO A10 is Floating input
  tmp32 = GET_REG32(REG_GPIOA_CRH);
  tmp32 &= ~(0b1111 << (10 - 8) * 4); // Reset only PA10
  tmp32 |= (0b0100 << (10 - 8) * 4); // MODE10=0b00:Înput mode, CNF10=0b01:Floating input
  SET_REG32(REG_GPIOA_CRH, tmp32);


  // Enable clock of GPIOC
  uint8_t tmp8 = GET_REG8(REG_RCC_APB2ENR);
  SET_REG8(REG_RCC_APB2ENR, tmp8 | (1 << 4)); // bit4:GPIOC

  // GPIO PC13 is output
  tmp32 = GET_REG32(REG_GPIOC_CRH);
  tmp32 &= ~(0b1111 << (13 - 8) * 4); // Reset only PC13
  tmp32 |= (0b0011 << (13 - 8) * 4); // MODE13=0b11:Output mode, max speed 50MHz, CNF13=0b00:General purpose output push-pull
  SET_REG32(REG_GPIOC_CRH, tmp32);

  uint8_t ch;

  while (1) {
    tmp32 = GET_REG32(REG_USART1_SR);
    if (tmp32 & (1 << 5)) { // Bit5 RXNE: Read data register not empty
      ch = GET_REG8(REG_USART1_DR);

      tmp32 = GET_REG32(REG_GPIOC_ODR);
      tmp32 ^= (1 << 13); // Toggle PC13(LED)
      SET_REG32(REG_GPIOC_ODR, tmp32);
    }
  }
}

