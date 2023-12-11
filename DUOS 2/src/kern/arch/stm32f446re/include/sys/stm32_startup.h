/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef __STM32_STARTUP_H
#define __STM32_STARTUP_H
#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128*1024) //128KB
#define SRAM_END ((SRAM_START)+(SRAM_SIZE))
#define STACK_START SRAM_END

int kmain(void);

extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;

volatile uint32_t _bss_size=0;
volatile uint32_t _data_size=0;
volatile uint32_t _text_size=0;

void Reset_Handler(void) __attribute__((weak));
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak));
void MemManage_Handler(void) __attribute__((weak));
void BusFault_Handler(void)__attribute__((weak));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVCall_Handler(void) __attribute__((weak));
void DebugMonitor_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak));
void WWDG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FMC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_WKUP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DCMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SAI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SAI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void QuadSPI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HDMI_CEC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPDIF_Rx_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FMPI2C1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FMPI2C1_ERR_Handler(void) __attribute__((weak, alias("Default_Handler")));
uint32_t NVIC_VECTOR[] __attribute__((section (".isr_vector")))={
	STACK_START,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &HardFault_Handler,
	(uint32_t) &MemManage_Handler,
	(uint32_t) &BusFault_Handler,
	(uint32_t) &UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t) &SVCall_Handler,
	(uint32_t) &DebugMonitor_Handler,
	0,
	(uint32_t) &PendSV_Handler,
	(uint32_t) &SysTick_Handler,
	(uint32_t) &WWDG_Handler,
	(uint32_t) &PVD_Handler,
	(uint32_t) &TAMP_STAMP_Handler,
	(uint32_t) &RTC_WKUP_Handler,
	(uint32_t) &FLASH_Handler,
	(uint32_t) &RCC_Handler,
	(uint32_t) &EXTI0_Handler,
	(uint32_t) &EXTI1_Handler,
	(uint32_t) &EXTI2_Handler,
	(uint32_t) &EXTI3_Handler,
	(uint32_t) &EXTI4_Handler,
	(uint32_t) &DMA1_Stream0_Handler,
	(uint32_t) &DMA1_Stream1_Handler,
	(uint32_t) &DMA1_Stream2_Handler,
	(uint32_t) &DMA1_Stream3_Handler,
	(uint32_t) &DMA1_Stream4_Handler,
	(uint32_t) &DMA1_Stream5_Handler,
	(uint32_t) &DMA1_Stream6_Handler,
	(uint32_t) &ADC_Handler,
	(uint32_t) &CAN1_TX_Handler,
	(uint32_t) &CAN1_RX0_Handler,
	(uint32_t) &CAN1_RX1_Handler,
	(uint32_t) &CAN1_SCE_Handler,
	(uint32_t) &EXTI9_5_Handler,
	(uint32_t) &TIM1_BRK_TIM9_Handler,
	(uint32_t) &TIM1_UP_TIM10_Handler,
	(uint32_t) &TIM1_TRG_COM_TIM11_Handler,
	(uint32_t) &TIM1_CC_Handler,
	(uint32_t) &TIM2_Handler,
	(uint32_t) &TIM3_Handler,
	(uint32_t) &TIM4_Handler,
	(uint32_t) &I2C1_EV_Handler,
	(uint32_t) &I2C1_ER_Handler,
	(uint32_t) &I2C2_EV_Handler,
	(uint32_t) &I2C2_ER_Handler,
	(uint32_t) &SPI1_Handler,
	(uint32_t) &SPI2_Handler,
	(uint32_t) &USART1_Handler,
	(uint32_t) &USART2_Handler,
	(uint32_t) &USART3_Handler,
	(uint32_t) &EXTI15_10_Handler,
	(uint32_t) &RTC_Alarm_Handler,
	(uint32_t) &OTG_FS_WKUP_Handler,
	(uint32_t) &TIM8_BRK_TIM12_Handler,
	(uint32_t) &TIM8_UP_TIM13_Handler,
	(uint32_t) &TIM8_TRG_COM_TIM14_Handler,
	(uint32_t) &TIM8_CC_Handler,
	(uint32_t) &DMA1_Stream7_Handler,
	(uint32_t) &FMC_Handler,
	(uint32_t) &SDIO_Handler,
	(uint32_t) &TIM5_Handler,
	(uint32_t) &SPI3_Handler,
	(uint32_t) &UART4_Handler,
	(uint32_t) &UART5_Handler,
	(uint32_t) &TIM6_DAC_Handler,
	(uint32_t) &TIM7_Handler,
	(uint32_t) &DMA2_Stream0_Handler,
	(uint32_t) &DMA2_Stream1_Handler,
	(uint32_t) &DMA2_Stream2_Handler,
	(uint32_t) &DMA2_Stream3_Handler,
	(uint32_t) &DMA2_Stream4_Handler,
	0,
	0,
	(uint32_t) &CAN2_TX_Handler,
	(uint32_t) &CAN2_RX0_Handler,
	(uint32_t) &CAN2_RX1_Handler,
	(uint32_t) &CAN2_SCE_Handler,
	(uint32_t) &OTG_FS_Handler,
	(uint32_t) &DMA2_Stream5_Handler,
	(uint32_t) &DMA2_Stream6_Handler,
	(uint32_t) &DMA2_Stream7_Handler,
	(uint32_t) &USART6_Handler,
	(uint32_t) &I2C3_EV_Handler,
	(uint32_t) &I2C3_ER_Handler,
	(uint32_t) &OTG_HS_EP1_OUT_Handler,
	(uint32_t) &OTG_HS_EP1_IN_Handler,
	(uint32_t) &OTG_HS_WKUP_Handler,
	(uint32_t) &OTG_HS_Handler,
	(uint32_t) &DCMI_Handler,
	0,
	0,
	(uint32_t) &FPU_Handler,
	0,
	0,
	(uint32_t) &SPI4_Handler,
	0,
	0,
	(uint32_t) &SAI1_Handler,
	0,
	0,
	0,
	(uint32_t) &SAI2_Handler,
	(uint32_t) &QuadSPI_Handler,
	(uint32_t) &HDMI_CEC_Handler,
	(uint32_t) &SPDIF_Rx_Handler,
	(uint32_t) &FMPI2C1_Handler,
	(uint32_t) &FMPI2C1_ERR_Handler
};
void update_global_tick_count(void);
#endif


