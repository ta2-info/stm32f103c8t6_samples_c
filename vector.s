
  .file "vector.s" // For DEBUGGER
  .thumb // T32 instructions.
  .syntax unified // Describe ARM and THUMB instructions in a unified format

  .equ STACK_TOP, 0x20005000 // STACK use from the end of SARM

  .extern _start
  .type _start, function

  .section .rodata
__LinkerDefinedValues__:
  .word _data_copyaddress
  .word _data_start
  .word _data_end
  .word _bss_start
  .word _bss_end

  .section .flash_top,"a",%progbits
  .word STACK_TOP
  .word Reset_Handler
  .word NMI_Handler // IRQ -14 : Non Maskable Interrupt
  .word HardFault_Handler // IRQ -13 : Cortex-M3 Hard Fault Interrupt
  .word MemManage_Handler // IRQ -12 : Cortex-M3 Memory Management Interrupt
  .word BusFault_Handler // IRQ -11 : Cortex-M3 Bus Fault Interrupt
  .word UsageFault_Handler // IRQ -10 : Cortex-M3 Usage Fault Interrupt
  .word 0 // Reserved
  .word 0 // Reserved
  .word 0 // Reserved
  .word 0 // Reserved
  .word SVC_Handler // IRQ -5 : Cortex-M3 SV Call Interrupt
  .word DebugMon_Handler // IRQ -4 : Cortex-M3 Debug Monitor Interrupt
  .word 0 // Reserved
  .word PendSV_Handler // IRQ -2 : Cortex-M3 Pend SV Interrupt
  .word SysTick_Handler // IRQ -1 : Cortex-M3 System Tick Interrupt
  .word WWDG_IRQHandler // IRQ 0 : Window WatchDog Interrupt
  .word PVD_IRQHandler // IRQ 1 : PVD through EXTI Line detection Interrupt
  .word TAMPER_IRQHandler // IRQ 2 : Tamper Interrupt
  .word RTC_IRQHandler // IRQ 3 : RTC global Interrupt
  .word FLASH_IRQHandler // IRQ 4 : FLASH global Interrupt
  .word RCC_IRQHandler // IRQ 5 : RCC global Interrupt
  .word EXTI0_IRQHandler // IRQ 6 : EXTI Line0 Interrupt
  .word EXTI1_IRQHandler // IRQ 7 : EXTI Line1 Interrupt
  .word EXTI2_IRQHandler // IRQ 8 : EXTI Line2 Interrupt
  .word EXTI3_IRQHandler // IRQ 9 : EXTI Line3 Interrupt
  .word EXTI4_IRQHandler // IRQ10 : EXTI Line4 Interrupt
  .word DMA1_Channel1_IRQHandler // IRQ11 : DMA1 Channel 1 global Interrupt
  .word DMA1_Channel2_IRQHandler // IRQ12 : DMA1 Channel 2 global Interrupt
  .word DMA1_Channel3_IRQHandler // IRQ13 : DMA1 Channel 3 global Interrupt
  .word DMA1_Channel4_IRQHandler // IRQ14 : DMA1 Channel 4 global Interrupt
  .word DMA1_Channel5_IRQHandler // IRQ15 : DMA1 Channel 5 global Interrupt
  .word DMA1_Channel6_IRQHandler // IRQ16 : DMA1 Channel 6 global Interrupt
  .word DMA1_Channel7_IRQHandler // IRQ17 : DMA1 Channel 7 global Interrupt
  .word ADC1_2_IRQHandler // IRQ18 : ADC1 and ADC2 global Interrupt
  .word USB_HP_CAN1_TX_IRQHandler // IRQ19 : USB Device High Priority or CAN1 TX Interrupts
  .word USB_LP_CAN1_RX0_IRQHandler // IRQ20 : USB Device Low Priority or CAN1 RX0 Interrupts
  .word CAN1_RX1_IRQHandler // IRQ21 : CAN1 RX1 Interrupt
  .word CAN1_SCE_IRQHandler // IRQ22 : CAN1 SCE Interrupt
  .word EXTI9_5_IRQHandler // IRQ23 : External Line[9:5] Interrupts
  .word TIM1_BRK_IRQHandler // IRQ24 : TIM1 Break Interrupt
  .word TIM1_UP_IRQHandler // IRQ25 : TIM1 Update Interrupt
  .word TIM1_TRG_COM_IRQHandler // IRQ26 : TIM1 Trigger and Commutation Interrupt
  .word TIM1_CC_IRQHandler // IRQ27 : TIM1 Capture Compare Interrupt
  .word TIM2_IRQHandler // IRQ28 : TIM2 global Interrupt
  .word TIM3_IRQHandler // IRQ29 : TIM3 global Interrupt
  .word TIM4_IRQHandler // IRQ30 : TIM4 global Interrupt
  .word I2C1_EV_IRQHandler // IRQ31 : I2C1 Event Interrupt
  .word I2C1_ER_IRQHandler // IRQ32 : I2C1 Error Interrupt
  .word I2C2_EV_IRQHandler // IRQ33 : I2C2 Event Interrupt
  .word I2C2_ER_IRQHandler // IRQ34 : I2C2 Error Interrupt
  .word SPI1_IRQHandler // IRQ35 : SPI1 global Interrupt
  .word SPI2_IRQHandler // IRQ36 : SPI2 global Interrupt
  .word USART1_IRQHandler // IRQ37 : USART1 global Interrupt
  .word USART2_IRQHandler // IRQ38 : USART2 global Interrupt
  .word USART3_IRQHandler // IRQ39 : USART3 global Interrupt
  .word EXTI15_10_IRQHandler // IRQ40 : External Line[15:10] Interrupts
  .word RTCAlarm_IRQHandler // IRQ41 : RTC Alarm through EXTI Line Interrupt
  .word USBWakeUp_IRQHandler // IRQ42 : USB Device WakeUp from suspend through EXTI Line Interrupt
  .word 0 // Padding

  // On RESET Entry
  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  bl CopyDataSection // Copy from FLASH to SRAM (DATA SECTION)
  bl FillZeroBSS

  bl _start // In C Function

  // Endless loop
Loop:
  b Loop
  .size Reset_Handler, .-Reset_Handler

  // Copy from FLASH to SRAM (DATA SECTION)
  .section .text.CopyDataSection
  .weak CopyDataSection
  .type CopyDataSection, %function
CopyDataSection:
  movs r1, 0 // initial offset is 0
  b CopyDataSection_2

CopyDataSection_1:
  ldr r3, =_data_copyaddress // initial COPYFROM address
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, 4 // r1 = r1 + 4

CopyDataSection_2:
  ldr r0, =_data_start // initial COPYTO address
  ldr r3, =_data_end   // final COPYTO address
  adds r2, r0, r1      // r2 = r0 + r1
  cmp r2, r3
  bcc CopyDataSection_1
  bx lr
  .size CopyDataSection, .-CopyDataSection

  // BSS Zero fill
  .section .text.FillZeroBSS
  .weak FillZeroBSS
  .type FillZeroBSS, %function
FillZeroBSS:
  ldr r2, =_bss_start
  b FillZeroBSS_2

FillZeroBSS_1:
  movs r3, 0
  str r3, [r2], 4 // [r2] = r2, r2 = r2 + 4

FillZeroBSS_2:
  ldr r3, =_bss_end
  cmp r2, r3
  bcc FillZeroBSS_1
  bx lr
  .size FillZeroBSS, .-FillZeroBSS


  // Dummy Handler
  .section .text.Default_Handler
Default_Handler:
  b Default_Handler
  .size Default_Handler, .-Default_Handler

  .weak NMI_Handler
  .thumb_set NMI_Handler, Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler, Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler, Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler, Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler, Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler, Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler, Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler, Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler, Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler, Default_Handler

  .weak WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler, Default_Handler

  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler, Default_Handler

  .weak TAMPER_IRQHandler
  .thumb_set TAMPER_IRQHandler, Default_Handler

  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler, Default_Handler

  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler, Default_Handler

  .weak RCC_IRQHandler
  .thumb_set RCC_IRQHandler, Default_Handler

  .weak EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler, Default_Handler

  .weak EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler, Default_Handler

  .weak EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler, Default_Handler

  .weak EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler, Default_Handler

  .weak EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler, Default_Handler

  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler, Default_Handler

  .weak DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler, Default_Handler

  .weak DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler, Default_Handler

  .weak DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler, Default_Handler

  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler, Default_Handler

  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler, Default_Handler

  .weak DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler, Default_Handler

  .weak ADC1_2_IRQHandler
  .thumb_set ADC1_2_IRQHandler, Default_Handler

  .weak USB_HP_CAN1_TX_IRQHandler
  .thumb_set USB_HP_CAN1_TX_IRQHandler, Default_Handler

  .weak USB_LP_CAN1_RX0_IRQHandler
  .thumb_set USB_LP_CAN1_RX0_IRQHandler, Default_Handler

  .weak CAN1_RX1_IRQHandler
  .thumb_set CAN1_RX1_IRQHandler, Default_Handler

  .weak CAN1_SCE_IRQHandler
  .thumb_set CAN1_SCE_IRQHandler, Default_Handler

  .weak EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler, Default_Handler

  .weak TIM1_BRK_IRQHandler
  .thumb_set TIM1_BRK_IRQHandler, Default_Handler

  .weak TIM1_UP_IRQHandler
  .thumb_set TIM1_UP_IRQHandler, Default_Handler

  .weak TIM1_TRG_COM_IRQHandler
  .thumb_set TIM1_TRG_COM_IRQHandler, Default_Handler

  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler, Default_Handler

  .weak TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler, Default_Handler

  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler, Default_Handler

  .weak TIM4_IRQHandler
  .thumb_set TIM4_IRQHandler, Default_Handler

  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler, Default_Handler

  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler, Default_Handler

  .weak I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler, Default_Handler

  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler, Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler, Default_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler, Default_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler, Default_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler, Default_Handler

  .weak USART3_IRQHandler
  .thumb_set USART3_IRQHandler, Default_Handler

  .weak EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler, Default_Handler

  .weak RTCAlarm_IRQHandler
  .thumb_set RTCAlarm_IRQHandler, Default_Handler

  .weak USBWakeUp_IRQHandler
  .thumb_set USBWakeUp_IRQHandler, Default_Handler

  .end

