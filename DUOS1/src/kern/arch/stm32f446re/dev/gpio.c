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
#include <gpio.h>

void DRV_GPIO_INIT(GPIO_TypeDef* gpio)
{
  /*
    - There are 8 GPIOs each separated by 0x400
    - We simply calculate the offset from GPIOA
    - Divide by 0x400 to get the position
    - Enable the GPIO in RCC
  */
  uint32_t base = (uint32_t)GPIOA;
  uint32_t offset = (uint32_t)gpio - base;
  uint32_t pos = offset / 0x400;
  RCC->AHB1ENR |= (1 << pos);
  

}
void GPIO_Init(GPIO_TypeDef* gpio,GPIO_InitTypeDef *gpio_init)
{

  /*
    Enable GPIO in RCC
  */
  

  for (uint32_t pos = 0U;pos < 16U;pos++){
    if(gpio_init->Pin & (1 << pos)){
      //set mode
      gpio->MODER &= ~(3U << (pos * 2));
      gpio->MODER |= ((gpio_init->Mode) << (pos * 2));
      //set speed
      gpio->OSPEEDR &= ~(3U << (pos * 2));
      gpio->OSPEEDR |= ((gpio_init->Speed) << (pos * 2));
    }
  }
}


void GPIO_WritePin(GPIO_TypeDef* gpio,uint16_t pin,uint8_t val)
{
  if(val == 0){
    //clear
    gpio->BSRR |= (1 << (pin + 16));
  }
  else{
    //set
    gpio->BSRR |= (1 << pin);
  }
}

uint8_t GPIO_IDR_Status(GPIO_TypeDef* gpio,uint16_t pin)
{
  if(gpio->IDR & (1 << pin)){
    return 1;
  }
  else{
    return 0;
  }
}
