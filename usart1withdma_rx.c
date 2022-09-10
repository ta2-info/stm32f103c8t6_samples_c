
#include "stm32f103c8.h"

#include "interrupt.h"

// GPIO A9  USART1:TX
// GPIO A10 USART1:RX
//
// USART1_TX : DMA 1 ch4
// USART1_RX : DMA 1 ch5
// USART2_TX : DMA 1 ch7
// USART2_RX : DMA 1 ch6
// USART3_TX : DMA 1 ch2
// USART3_RX : DMA 1 ch3

static uint8_t buffer256[256] = {0};

static void MyDMAHandler(void) {
  uint32_t tmp32 = GET_REG32(REG_GPIOC_ODR);
  tmp32 ^= (1 << 13); // Toggle PC13(LED)
  SET_REG32(REG_GPIOC_ODR, tmp32);

  uint32_t isr = GET_REG32(REG_DMA1_ISR);
  uint32_t ccr = GET_REG32(REG_DMA1_CCR5);

  // Transfer error interrupt

  // Half transfer interrupt

  // Transfer complete interrupt
  if ((ccr & (1 << 1) && (isr & (0b0010 << ((5 - 1) * 4))))) {
    SET_REG32(REG_DMA1_IFCR, (0b0010 << ((5 - 1) * 4))); // Clear TC flag

    // Disable DMA
    //  bit 0 EN(Channel enable): 0(disabled)
    uint32_t tmp32 = GET_REG32(REG_DMA1_CCR5);
    tmp32 &= ~(1 << 0);
    SET_REG32(REG_DMA1_CCR5, tmp32);

    // Set size
    SET_REG32(REG_DMA1_CNDTR5, 1); // 1byte

    // Enable DMA
    //  bit 0 EN(Channel enable): 1(enabled)
    tmp32 |= (1 << 0);
    SET_REG32(REG_DMA1_CCR5, tmp32);
  }

  SET_REG32(REG_DMA1_CCR5, ccr);
}


void _start() {
  uint32_t tmp32;

  // Regist callback
  DMA1_Channel5_IRQHandler_callback = MyDMAHandler;

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

  // Enable clock of GPIOA
  tmp32 = GET_REG32(REG_RCC_APB2ENR);
  SET_REG32(REG_RCC_APB2ENR, tmp32 | (1 << 2)); // bit2:GPIOA

  // GPIO A10 is Floating input
  tmp32 = GET_REG32(REG_GPIOA_CRH);
  tmp32 &= ~(0b1111 << (10 - 8) * 4); // Reset only PA10
  tmp32 |= (0b0100 << (10 - 8) * 4); // MODE10=0b00:Înput mode, CNF10=0b01:Floating input
  SET_REG32(REG_GPIOA_CRH, tmp32);

  // Enable clock of DMA1
  tmp32 = GET_REG32(REG_RCC_AHBENR);
  tmp32 |= (1 << 0); // bit 0 DMA1EN: DMA1 clock enable
  SET_REG32(REG_RCC_AHBENR, tmp32);

  // Enable DMA1 ch5 = IRQ15
  tmp32 = GET_REG32(REG_NVIC_ISER_0);
  tmp32 |= (1 << 15); // IRQ15
  SET_REG32(REG_NVIC_ISER_0, tmp32);

  // Init DMA1 ch5
  // From: USART1_DR, To: Memory(Buffer)
  //  bit14 MEM2MEM(Memory to memory mode): 0(disabled)
  //  bit13,12 PL[1:0](Channel priority level): 00(Low)
  //  bit11,10 MSIZE[1:0](Memory size): 00(8-bits)
  //  bit 9,8 PSIZE[1:0](Peripheral size): 00(8-bits)
  //  bit 7 MINC(Memory increment mode): 1(enable)
  //  bit 6 PINC(Peripheral increment mode): 0(disabled)
  //  bit 5 CIRC(Circular mode): 0(disabled)
  //  bit 4 DIR(Data transfer direction): 0(Read from peripheral)
  //  bit 3 TEIE(Transfer error interrupt enable): 0(disabled)
  //  bit 2 HTIE(Half transfer interrupt enable): 0(disabled)
  //  bit 1 TCIE(Transfer complete interrupt enable): 0(disabled)
  //  bit 0 EN(Channel enable): 0(disabled)
  SET_REG32(REG_DMA1_CCR5, (1 << 7));

  SET_REG32(REG_DMA1_IFCR, (0b1111 << (5 - 1) * 4)); // Clear ch5 all

  SET_REG32(REG_DMA1_CNDTR5, 1); // 1byte

  SET_REG32(REG_DMA1_CPAR5, (uint32_t)REG_USART1_DR); // Peripheral address

  SET_REG32(REG_DMA1_CMAR5, (uint32_t)buffer256); // Memory address

#if 0
  // Enable DMA
  //  bit 3 TEIE(Transfer error interrupt enable): 1(enabled)
  //  bit 2 HTIE(Half transfer interrupt enable): 1(enabled)
  //  bit 1 TCIE(Transfer complete interrupt enable): 1(enabled)
  //  bit 0 EN(Channel enable): 1(enabled)
  tmp32 = GET_REG32(REG_DMA1_CCR5);
  tmp32 |= (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
  SET_REG32(REG_DMA1_CCR5, tmp32);
#else
  // Enable DMA
  //  bit 1 TCIE(Transfer complete interrupt enable): 1(enabled)
  //  bit 0 EN(Channel enable): 1(enabled)
  tmp32 = GET_REG32(REG_DMA1_CCR5);
  tmp32 |= (1 << 1) | (1 << 0);
  SET_REG32(REG_DMA1_CCR5, tmp32);
#endif


  // Enable USART1 RX DMA
  tmp32 = GET_REG32(REG_USART1_CR3);
  tmp32 |= (1 << 6); // bit6 DMAR: DMA enable receiver
  SET_REG32(REG_USART1_CR3, tmp32);



  // Enable clock of GPIOC
  uint8_t tmp8 = GET_REG8(REG_RCC_APB2ENR);
  SET_REG8(REG_RCC_APB2ENR, tmp8 | (1 << 4)); // bit4:GPIOC

  // GPIO PC13 is output
  tmp32 = GET_REG32(REG_GPIOC_CRH);
  tmp32 &= ~(0b1111 << (13 - 8) * 4); // Reset only PC13
  tmp32 |= (0b0011 << (13 - 8) * 4); // MODE13=0b11:Output mode, max speed 50MHz, CNF13=0b00:General purpose output push-pull
  SET_REG32(REG_GPIOC_CRH, tmp32);

  SET_REG32(REG_USART1_CR1, (1 << 13) | (1 << 2)); // bit 13 UE: USART enable, bit2 RE: Receiver enable

  tmp32 = GET_REG32(REG_USART1_SR); // dummy read

  uint8_t ch;

  while (1) {
    volatile int32_t counter = 100000;
    while (counter > 0) {
      counter--;
    }
  }
}

