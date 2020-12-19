#include "isr.h"

void isr_handler(registers_t* regs)
{
	printf("interrupt:%d error:%d\n",regs->int_no,regs->err_code);
}

