#include <sys.h>
#include <seven_segment.h>
#include <kstdio.h>
/* Functions of NVIC */
void __NVIC_SetPriority(IRQn_TypeDef IRQn, uint32_t priority)
{
      if (IRQn >= 0)
      {
            NVIC->IP[IRQn] = (uint8_t)((priority << 4));
      }
}

uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn)
{
      if (IRQn >= 0)
      {
            return (NVIC->IP[IRQn] >> 4);
      }
}

void __NVIC_EnableIRQn(IRQn_TypeDef IRQn)
{
      if (IRQn >= 0)
      {
            NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
      }
}

void __NVIC_DisableIRQn(IRQn_TypeDef IRQn)
{
      if (IRQn >= 0)
      {
            NVIC->ICER[IRQn / 32] |= (1 << (IRQn % 32));
      }
}

void __disable_irq()
{
      asm("mov r0,#1");
      asm("msr primask,r0;");
}

void __set_BASEPRI(uint32_t value)
{
      asm("mov r0, %0"
          : "=r"(value));
      asm("msr basepri, r0;");
}

void __enable_irq()
{
      asm("mov r0,#0");
      asm("msr primask,r0;");
}

void __unset_BASEPRI(uint32_t value)
{
      asm("mov r0,#0");
      asm("msr basepri,r0;");
}

void __set_PRIMASK(uint32_t priMask)
{
      asm("mov r0, #1");
      asm("msr primask, r0");
}

uint32_t get_PRIMASK(void)
{
      uint32_t value;
      asm("mrs r0,primask");
      asm("mov %0,r0"
          : "=r"(value));
      return value;
}

void __enable_fault_irq(void)
{
      asm("mov r0, #0");
      asm("msr primask, r0");
}

void __set_FAULTMASK(uint32_t faultMask)
{
      asm("mov r0, #1");
      asm("msr primask, r0");
}

void __disable_fault_irq(void)
{
      asm("mov r0, #1");
      asm("msr primask, r0");
}

uint32_t __get_FAULTMASK(void)
{
      uint32_t value;
      asm("mrs r0,faultmask");
      asm("mov %0,r0"
          : "=r"(value));
      return value;
}

void __clear_pending_IRQn(IRQn_TypeDef IRQn)
{
      if (IRQn >= 0)
      {
            NVIC->ICPR[IRQn / 32] |= (1 << (IRQn % 32));
      }
}

uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn)
{
      uint32_t pendingState;
      if (IRQn >= 0)
      {
            int regNumber = IRQn / 32;
            int offset = IRQn % 32;
            pendingState = NVIC->ICPR[regNumber] & (1 << regNumber);
            pendingState = pendingState >> 5;
            return pendingState;
      }
}

uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn)
{
      uint32_t pendingState;
      if (IRQn >= 0)
      {
            int regNumber = IRQn / 32;
            int offset = IRQn % 32;
            pendingState = NVIC->IABR[regNumber] & (1 << regNumber);
            pendingState = pendingState >> 5;
            return pendingState;
      }
}

void EXTI_Init(GPIO_TypeDef *port, uint16_t pin)
{
      // GPIO_InitTypeDef gpiox;
      // RCC->AHB1ENR |= (1 << 2);
      // GPIOC->MODER &= (3 << 6);
      // GPIOC->PUPDR |= GPIO_NOPULL;
      // kprintf("jd\n");
      // RCC->APB2ENR |= (1 << 14);         // Enable SYSCNFG
      // SYSCFG->EXTICR[0] &= ~(0xf << 12); // Bits[7:6:5:4] = (0:0:0:0)  -> reset EXTI1 line for PC3
      // SYSCFG->EXTICR[0] |= (0x2 << 12);  // Bits[7:6:5:4] = (0:0:0:0)  -> configure EXTI1 line for PC3
      // EXTI->IMR &= ~(1 << 3);            // Bit[1] = 1  --> Disable the Mask on EXTI 1
      // EXTI->RTSR |= (1 << 3);            // Enable Rising Edge Trigger for PC3
      // EXTI->FTSR &= ~(1 << 3);           // Disable Falling Edge Trigger for PC3
      // NVIC_SetPriority(EXTI1_IRQn, 0);   // Set Priority
      // NVIC_EnableIRQ(EXTI1_IRQn);        // Enable Interrupt

      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

      // Configure PC3 as input (no need to set mode for input)
      GPIOC->MODER &= ~(GPIO_MODER_MODE3_Msk);
      GPIOC->PUPDR |= GPIO_PULLDOWN;

      // Configure EXTI3 in SYSCFG
      SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3_Msk; // Clear EXTI3 bits
      SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC;   // Set EXTI3 to PC

      // Configure EXTI3 to trigger on rising edge (or other trigger types)
      EXTI->RTSR |= EXTI_RTSR_TR3;
      EXTI->FTSR &= ~EXTI_FTSR_TR3;
      // Enable EXTI3 interrupt
      EXTI->IMR |= EXTI_IMR_MR3;
      EXTI->EMR |= EXTI_EMR_MR3;

      // Set priority for EXTI3 interrupt (if using NVIC)
      NVIC_SetPriority(EXTI3_IRQn, 0);

      // Enable EXTI3 interrupt in NVIC
      NVIC_EnableIRQ(EXTI3_IRQn);
}
void EXTI3_IRQHandler(void)
{
      kprintf("Invoked\n");
      if ((EXTI->PR & (1 << 3)) != 0)
      {
            // EXTI3 interrupt occurred
            // Handle the interrupt

            // Clear the interrupt flag
            EXTI->PR &= ~(1 << 3);
      }
}