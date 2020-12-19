#include "isr.h"

isr_t interrupt_handlers[256];
void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t *regs)
{
   // Send End of Interrupt Signal : Reset
   if (regs->int_no >= 40)
   {
       outb(0xA0, 0x20);  // Reset Slave
   }
   outb(0x20, 0x20);  // Reset Master

   if (interrupt_handlers[regs->int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs->int_no];
       handler(*regs);
   }
}

void isr_handler(registers_t* regs)
{
	printf("interrupt:%d error:%d\n",regs->int_no,regs->err_code);
}

