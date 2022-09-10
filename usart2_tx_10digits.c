
#include "stm32f103c8.h"

// GPIO A2 USART2:TX
// GPIO A3 USART2:RX

void _start() {
  uint32_t tmp32;

  // Enable clock of USART2
  tmp32 = GET_REG32(REG_RCC_APB1ENR);
  SET_REG32(REG_RCC_APB1ENR, tmp32 | (1 << 17)); // bit17:USART2

  // Reset USART2
  tmp32 = GET_REG32(REG_RCC_APB1RSTR);
  tmp32 |= (1 << 17); // bit17: USART2 RST
  SET_REG32(REG_RCC_APB1RSTR, tmp32);
  tmp32 &= ~(1 << 17);
  SET_REG32(REG_RCC_APB1RSTR, tmp32);

  // CPU = 8MHz
  //
  // Baud rate : 115200
  //  USARTDIV = (8MHz / (16 * 115200)) = 4.3402777777...
  //   Mantissa = 4
  //   Fraction = (0.3402777....) * 16 = 5.4... = 5
  uint16_t wDIV_Mantissa = 4, wDIV_Fraction = 5;
  SET_REG32(REG_USART2_BRR, (wDIV_Mantissa << 4) | (wDIV_Fraction << 0));

  SET_REG32(REG_USART2_CR1, (1 << 13) | (1 << 3)); // bit 13 UE: USART enable, bit3 TE: Transmitter enable

  tmp32 = GET_REG32(REG_USART2_SR); // dummy read

  // Enable clock of GPIOA
  tmp32 = GET_REG32(REG_RCC_APB2ENR);
  SET_REG32(REG_RCC_APB2ENR, tmp32 | (1 << 2)); // bit2:GPIOA

  // GPIO A2 is AF Output Push-pull
  tmp32 = GET_REG32(REG_GPIOA_CRL);
  tmp32 &= ~(0b1111 << 2 * 4); // Reset only PA2
  tmp32 |= (0b1011 << 2 * 4); // MODE9=0b11:Output mode, max speed 50MHz, CNF9=0b10:Alternate function output Push-pull
  SET_REG32(REG_GPIOA_CRL, tmp32);

  const uint8_t chars[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

  while (1) {
    for (int i = 0; i < sizeof(chars); i++) {
      SET_REG8(REG_USART2_DR, chars[i]);

      while (1) {
        uint32_t status = GET_REG32(REG_USART2_SR);
        if (status & (1 << 7)) { // Bit 7 TXE: Transmit data register empty
          break;
        }
      }
    }

    // wait...
    for (int wait = 0; wait < 1000000; wait++) {
    }
  }
}

